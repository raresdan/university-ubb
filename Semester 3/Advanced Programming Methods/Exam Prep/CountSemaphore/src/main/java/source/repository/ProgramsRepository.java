package source.repository;



import source.exceptions.InterpreterException;
import source.models.PrgState;
import source.models.statements.IStatement;
import source.models.utils.MyICountSemaphoreTable;
import source.models.utils.MyIDictionary;
import source.models.utils.MyIHeap;
import source.models.values.IValue;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class ProgramsRepository implements IRepository {
    private List<PrgState> programs;
    private final String logFilePath;

    public ProgramsRepository(String logFilePath) {
        programs = new ArrayList<PrgState>();
        this.logFilePath = logFilePath;
        try {
            PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(logFilePath)));
            logFile.close();
        } catch (IOException ignored) {
        }
    }

    public ProgramsRepository(PrgState program, String logFilePath) {
        this.programs.add(program);
        this.logFilePath = logFilePath;
    }

    @Override
    public void addProgram(PrgState programToAdd) {
        this.programs.add(programToAdd);
    }

    @Override
    public List<PrgState> getAllPrograms() {
        return this.programs;
    }

    @Override
    public void setProgramsList(List<PrgState> newPrograms) {
        this.programs = newPrograms;
    }

    private void logExecutionStack(PrintWriter logFile, PrgState currentProgram) {
        logFile.println("ExeStack:");
        ArrayList<IStatement> stackStatements = (ArrayList<IStatement>) currentProgram.getStackStatements();
        for (IStatement currentStatement : stackStatements)
            logFile.println(currentStatement.toString());
        logFile.println();
    }

    private void logSymbolTable(PrintWriter logFile, PrgState currentProgram) {
        logFile.println("SymTable:");
        MyIDictionary<String, IValue> symbolTable = currentProgram.getSymbolTable();
        for (String key : symbolTable.getKeySet())
            logFile.println(key + " = " + symbolTable.get(key));
        logFile.println();
    }

    private void logOutput(PrintWriter logFile, PrgState currentProgram) {
        logFile.println("Output:");
        List<IValue> outputList = currentProgram.getOutputList().getOutput();
        for (IValue currentValue : outputList)
            logFile.println(currentValue);
        logFile.println();
    }

    private void logFileTable(PrintWriter logFile, PrgState currentProgram) {
        logFile.println("File Table:");
        MyIDictionary<String, BufferedReader> fileTable = currentProgram.getFileTable();
        for (String filename : fileTable.getKeySet())
            logFile.println(filename);
        logFile.println();
    }

    private void logHeapTable(PrintWriter logFile, PrgState currentProgram) {
        logFile.println("Heap Table:");
        MyIHeap heapTable = currentProgram.getHeapTable();
        for (Integer address : heapTable.getContent().keySet())
            logFile.println(address + " -> " + heapTable.getValueAtAddress(address));
        logFile.println();
    }

    @Override
    public void logProgramState(PrgState currentProgram) throws InterpreterException{
        try {
            PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(this.logFilePath, true)));
            logFile.println("Id=" + currentProgram.getId());
            this.logExecutionStack(logFile, currentProgram);
            this.logSymbolTable(logFile, currentProgram);
            this.logOutput(logFile, currentProgram);
            this.logFileTable(logFile, currentProgram);
            this.logHeapTable(logFile, currentProgram);
            this.logSemaphore(logFile, currentProgram);
            logFile.println("\n");
            logFile.close();
        }
        catch (IOException ignored) {}
    }

    private void logSemaphore(PrintWriter logFile, PrgState currentProgram) throws InterpreterException {
        logFile.println("Semaphore Table:");
        MyICountSemaphoreTable countSemaphoreTable = currentProgram.getSemaphoreTable();
        for (Integer address : countSemaphoreTable.getContent().keySet())
            logFile.println(address + " -> (" + countSemaphoreTable.get(address) + countSemaphoreTable.get(address).getValue() + ")");
        logFile.println();
    }
}
