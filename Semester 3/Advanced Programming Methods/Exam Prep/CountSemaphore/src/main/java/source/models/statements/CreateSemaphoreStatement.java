package source.models.statements;

import javafx.util.Pair;
import source.exceptions.ExpressionEvaluationException;
import source.exceptions.InterpreterException;
import source.exceptions.StatementException;
import source.models.PrgState;
import source.models.expressions.IExpression;
import source.models.types.IntType;
import source.models.types.Type;
import source.models.utils.MyIDictionary;
import source.models.utils.CountSemaphoreTable;
import source.models.values.IValue;
import source.models.values.IntValue;

import java.util.ArrayList;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class CreateSemaphoreStatement implements IStatement{
    String variableName;
    IExpression expression;
    static final Lock lock = new ReentrantLock();

    public CreateSemaphoreStatement(String variableName, IExpression expression) {
        this.variableName = variableName;
        this.expression = expression;
    }

    @Override
    public String toString() {
        return "createSemaphore(" + variableName + ", " + expression + ")";
    }


    @Override
    public PrgState execute(PrgState currentState) throws StatementException, ExpressionEvaluationException, InterpreterException {
        lock.lock();
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable();
        CountSemaphoreTable semaphoreTable = currentState.getSemaphoreTable();
        if(!symbolTable.isDefined(variableName)) {
            throw new StatementException("Variable not defined!");
        }
        if(!symbolTable.get(variableName).getType().equals(new IntType())) {
            throw new StatementException("Invalid type of variable!");
        }
        IValue value = expression.evaluate(symbolTable, currentState.getHeapTable());
        if (!value.getType().equals(new IntType()))
        {
            throw new StatementException("Invalid type of value!");
        }
        int number = ((IntValue) value).getValue();
        int freeLocation = semaphoreTable.getFreeLocation();
        semaphoreTable.update(freeLocation, new Pair<>(number, new ArrayList<>()));
        symbolTable.update(variableName, new IntValue(freeLocation));
        lock.unlock();
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException {
        Type expType = expression.typeCheck(typeTable);
        Type varType = typeTable.get(variableName);
        if(!(expType.equals(new IntType()) && varType.equals(new IntType()))) {
            throw new InterpreterException("CreateSemaphoreStmt: invalid type!");
        }
        return typeTable;
    }
}
