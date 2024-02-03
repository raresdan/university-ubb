package controller;

import exceptions.ExpressionEvaluationException;
import exceptions.InterpreterException;
import exceptions.StackException;
import exceptions.StatementException;
import models.PrgState;
import models.values.IValue;
import models.values.RefValue;
import repository.IRepository;

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

    public Controller(IRepository programs) {
        this.repository = programs;
    }

    public void addProgram(PrgState programToAdd) {
        repository.addProgram(programToAdd);
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
        threadsExecutor = Executors.newFixedThreadPool(2);
        List<PrgState> programsList = removeCompletedPrograms(this.repository.getAllPrograms());
        while (!programsList.isEmpty()) {
            this.oneStepForAllPrograms(programsList);
            programsList = removeCompletedPrograms(this.repository.getAllPrograms());
        }
        threadsExecutor.shutdownNow();
        this.repository.setProgramsList(programsList);
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
        allPrograms.forEach(this.repository::logProgramState);
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
