package source.controller;


import source.exceptions.ExpressionEvaluationException;

import source.exceptions.InterpreterException;
import source.exceptions.StackException;
import source.exceptions.StatementException;
import source.models.PrgState;
import source.models.utils.Pair;
import source.models.values.IValue;
import source.models.values.RefValue;
import source.repository.IRepository;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.Map;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;

public class Controller {
    private final IRepository repository;
    private ExecutorService threadsExecutor;
    private PrgState copyProgram;

    public Controller(IRepository programs) {
        this.repository = programs;
        this.copyProgram = null;
    }

    public void addProgram(PrgState programToAdd) {
        repository.addProgram(programToAdd);
    }

    public List<PrgState> getAllPrograms()
    {
        return this.repository.getAllPrograms();
    }

    public PrgState getCopyProgram()
    {
        return this.copyProgram;
    }

    private Map<Integer, IValue> safeGarbageCollector(List<Integer> symbolTableAddresses, Map<Integer, IValue> heapTable)
    {
        return heapTable.entrySet().stream()
                .filter(value -> symbolTableAddresses.contains(value.getKey()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }

    public List<Integer> getAddresses(List<Collection<IValue>> symTableValues, Map<Integer, IValue> heapTable) {
        List<Integer> allAddresses = new ArrayList<>();
        symTableValues.forEach(symbolTable -> symbolTable.stream()
                .filter(value -> value instanceof RefValue)
                .forEach( value -> {
                    while (value instanceof RefValue) {
                        allAddresses.add(((RefValue) value).getAddress());
                        value = heapTable.get(((RefValue) value).getAddress());
                    }
                })
        );
        return allAddresses;
    }

    public void allSteps() throws IOException, ExpressionEvaluationException, StatementException, InterpreterException, StackException {
        while (!repository.getAllPrograms().isEmpty())
        {
            this.oneStepAll();
        }
    }

    private List<Callable<PrgState>> createListOfCallables(List<PrgState> allPrograms) {
        return allPrograms.stream()
                .map((PrgState program) -> (Callable<PrgState>) (program::oneStep))
                .collect(Collectors.toList());
    }

    private List<Pair> oneStepForEachProgram(List<Callable<PrgState>> callList) {
        List<Pair> newProgramsList = null;
        try {
            newProgramsList = threadsExecutor.invokeAll(callList).stream()
                    .map(future -> {
                        try {
                            return new Pair(future.get(), null);
                        } catch (InterruptedException | ExecutionException e) {
                            if (e.getCause() instanceof InterpreterException)
                                return new Pair(null, (InterpreterException) e.getCause());

                            System.out.println(e.getMessage());
                            System.exit(1);
                            return null;
                        }
                    })
                    .filter(pair -> pair.program != null || pair.thrownException != null)
                    .collect(Collectors.toList());
        } catch (InterruptedException e) {
            System.exit(1);
        }
        return newProgramsList;
    }

    public void oneStepForAllPrograms(List<PrgState> allPrograms) throws InterpreterException {
        List<Callable<PrgState>> callList = this.createListOfCallables(allPrograms);
        List<Pair> newProgramsList = this.oneStepForEachProgram(callList);
        for (Pair error : newProgramsList)
            if (error.thrownException != null)
                throw error.thrownException;
        allPrograms.addAll(newProgramsList.stream().map(pair -> pair.program).collect(Collectors.toList()));
        this.repository.setProgramsList(allPrograms);
        this.updateHeap();
        for (PrgState allProgram : allPrograms) {
            this.repository.logProgramState(allProgram);
        }
    }

    public void oneStepAll() throws InterpreterException
    {
        threadsExecutor = Executors.newFixedThreadPool(2);
        this.updateHeap();
        this.oneStepForAllPrograms(repository.getAllPrograms());
        repository.setProgramsList(removeCompletedPrograms(repository.getAllPrograms()));
        threadsExecutor.shutdownNow();
    }
    List<PrgState> removeCompletedPrograms(List<PrgState> allPrograms) {
        return allPrograms.stream()
                .filter(PrgState::isNotCompleted)
                .collect(Collectors.toList());
    }

    private void updateHeap()
    {
        PrgState firstProgram = this.repository.getAllPrograms().get(0);

        firstProgram.getHeapTable().setContent(
                this.safeGarbageCollector(
                        this.getAddresses(
                                this.repository.getAllPrograms().stream()
                                        .map(program -> program.getSymbolTable().getContent().values())
                                        .collect(Collectors.toList()),
                                firstProgram.getHeapTable().getContent()
                        ),
                        firstProgram.getHeapTable().getContent()
                ));
    }
}
