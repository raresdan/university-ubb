package source.models.statements;

import source.exceptions.ExpressionEvaluationException;
import source.exceptions.InterpreterException;
import source.exceptions.StatementException;
import source.models.PrgState;
import source.models.types.IntType;
import source.models.types.Type;
import source.models.utils.MyIDictionary;
import source.models.utils.CountSemaphoreTable;
import source.models.values.IValue;
import source.models.values.IntValue;

import java.util.List;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class AcquireStatement implements IStatement{
    private final String variableName;

    private static final Lock lock = new ReentrantLock();

    public AcquireStatement(String variableName) {
        this.variableName = variableName;
    }

    @Override
    public String toString() {
        return "acquire(" + variableName + ")";
    }

    @Override
    public PrgState execute(PrgState currentState) throws StatementException, ExpressionEvaluationException, InterpreterException {
        lock.lock();
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable();
        CountSemaphoreTable semaphoreTable = currentState.getSemaphoreTable();
        if(!symbolTable.isDefined(variableName)) {
            throw new ExpressionEvaluationException("Variable " + variableName + " is not defined!");
        }
        if (!symbolTable.get(variableName).getType().equals(new IntType())) {
            throw new ExpressionEvaluationException("Variable " + variableName + " is not of type int!");
        }
        int foundIndex = ((IntValue) symbolTable.get(variableName)).getValue();
        if (!semaphoreTable.isDefined(foundIndex)) {
            throw new StatementException("Index " + foundIndex + " is not defined in the semaphore table!");
        }
        int n1 = semaphoreTable.get(foundIndex).getKey();
        List<Integer> list = semaphoreTable.get(foundIndex).getValue();
        int nL = list.size();
        if (n1 > nL) {
            if (!(list.contains(currentState.getId()))) {
                list.add(currentState.getId());
            }
        } else {
            currentState.getStack().push(this);
        }
        lock.unlock();
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException {
        if(!(typeTable.get(variableName).equals(new IntType()))) {
            throw new InterpreterException("AcquireStmt: invalid type!");
        }
        return typeTable;
    }
}
