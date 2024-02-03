package source.models.statements;

import source.exceptions.ExpressionEvaluationException;
import source.exceptions.InterpreterException;
import source.exceptions.StatementException;
import source.models.PrgState;
import source.models.types.IntType;
import source.models.types.Type;
import source.models.utils.MyIDictionary;
import source.models.utils.SemaphoreTable;
import source.models.values.IValue;
import source.models.values.IntValue;

import java.util.List;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class ReleaseStatement implements IStatement{
    private final String variableName;
    private static final Lock lock = new ReentrantLock();
    public ReleaseStatement(String variableName) {
        this.variableName = variableName;
    }

    @Override
    public String toString() {
        return "release(" + variableName + ")";
    }

    @Override
    public PrgState execute(PrgState currentState) throws StatementException, ExpressionEvaluationException, InterpreterException {
        lock.lock();
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable();
        SemaphoreTable semaphoreTable = currentState.getSemaphoreTable();
        if (!symbolTable.isDefined(variableName)) {
            throw new StatementException("Variable " + variableName + " is not defined!");
        }
        if (!symbolTable.get(variableName).getType().equals(new IntType())) {
            throw new StatementException("Variable " + variableName + " is not an integer!");
        }
        int foundIndex = ((IntValue) symbolTable.get(variableName)).getValue();
        if (!semaphoreTable.isDefined(foundIndex)) {
            throw new StatementException("Index " + foundIndex + " is not defined in the semaphore table!");
        }
        List<Integer> list = semaphoreTable.get(foundIndex).second();
        if (list.contains(currentState.getId())) {
            list.remove((Integer) currentState.getId());
        }
        lock.unlock();
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException {
        if(!(typeTable.get(variableName).equals(new IntType()))) {
            throw new InterpreterException("ReleaseStmt: invalid type!");
        }
        return typeTable;
    }
}
