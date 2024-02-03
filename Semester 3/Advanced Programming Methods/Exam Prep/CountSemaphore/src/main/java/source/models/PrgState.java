package source.models;


import source.exceptions.ExpressionEvaluationException;
import source.exceptions.InterpreterException;
import source.exceptions.StackException;
import source.exceptions.StatementException;
import source.models.statements.CompoundStatement;
import source.models.statements.IStatement;
import source.models.utils.*;
import source.models.values.IValue;

import java.io.BufferedReader;
import java.util.*;

public class PrgState {
    private MyIStack<IStatement> exeStack;
    private MyIDictionary<String, IValue> symbolTable;
    private MyIList<IValue> outputList;
    private final MyIDictionary<String, BufferedReader> fileTable;
    private final MyIHeap heapTable;
    private final int id;
    private static int currentID = 0;
    private static final Set<Integer> idSet = new TreeSet<>();
    private final CountSemaphoreTable semaphoreTable;

    public PrgState(IStatement program) {
        this.exeStack = new MyStack<>();
        this.symbolTable = new MyDictionary<>();
        this.outputList = new MyList<>();
        this.fileTable = new MyDictionary<>();
        this.heapTable = new MyHeap();
        this.exeStack.push(program);
        semaphoreTable = new CountSemaphoreTable();
        this.id = PrgState.getAvailableId();
    }

    public PrgState(MyIStack<IStatement> exeStack, MyIDictionary<String, IValue> symbolTable,
                    MyIList<IValue> outputList, MyIDictionary<String, BufferedReader> fileTable, MyIHeap heapTable,  CountSemaphoreTable semaphoreTable) {
        this.exeStack = exeStack;
        this.symbolTable = symbolTable;
        this.outputList = outputList;
        this.fileTable = fileTable;
        this.heapTable = heapTable;
        this.semaphoreTable = semaphoreTable;
        this.id = PrgState.getAvailableId();
    }

    public int getId() {
        return this.id;
    }

    private static int getAvailableId() {
        synchronized (idSet) {
            PrgState.currentID += 1;
            idSet.add(currentID);
            return PrgState.currentID;
        }
    }

    public Boolean isNotCompleted() {
        return !this.exeStack.isEmpty();
    }

    public PrgState oneStep() throws ExpressionEvaluationException, StatementException, InterpreterException {
        try {
            IStatement currentStatement = exeStack.pop();
            return currentStatement.execute(this);
        } catch (StackException e) {
            throw new InterpreterException("Statements stack is empty!");
        }
    }

    public MyIStack<IStatement> getStack() {
        return this.exeStack;
    }

    public void setExeStack(MyIStack<IStatement> newStack) {
        this.exeStack = newStack;
    }

    public MyIDictionary<String, IValue> getSymbolTable() {
        return this.symbolTable;
    }

    public void setSymbolTable(MyIDictionary<String, IValue> newSymbolTable) {
        this.symbolTable = newSymbolTable;
    }

    public MyIList<IValue> getOutputList() {
        return this.outputList;
    }
    public CountSemaphoreTable getSemaphoreTable() {return semaphoreTable;}
    public void setOutputList(MyList<IValue> newOutputList) {
        this.outputList = newOutputList;
    }

    public MyIDictionary<String, BufferedReader> getFileTable() {
        return this.fileTable;
    }

    public MyIHeap getHeapTable() {
        return this.heapTable;
    }

    public List<IStatement> getStackStatements() {
        ArrayList<IStatement> stackStatements = new ArrayList<>();

        if (this.exeStack.isEmpty())
            return stackStatements;

        Stack<IStatement> statements = new Stack<>();
        for (IStatement currentStatement : this.exeStack.getStackAsList())
            statements.push(currentStatement);

        while (!statements.isEmpty()) {
            IStatement topStatement = statements.pop();
            if (topStatement instanceof CompoundStatement currentStatement) {
                statements.push(currentStatement.getSecondStatement());
                statements.push(currentStatement.getFirstStatement());
            } else
                stackStatements.add(topStatement);
        }
        return stackStatements;
    }

    @Override
    public String toString() {
        return "PrgState{" +
                "exeStack=" + exeStack +
                ", symbolTable=" + symbolTable +
                ", outputList=" + outputList +
                ", FileTable=" + fileTable +
                ", SemaphoreTable=" + semaphoreTable+
                '}';
    }
}
