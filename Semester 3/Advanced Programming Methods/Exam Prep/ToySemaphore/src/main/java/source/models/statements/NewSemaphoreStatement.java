package source.models.statements;

import source.exceptions.ExpressionEvaluationException;
import source.exceptions.InterpreterException;
import source.exceptions.StatementException;
import source.models.PrgState;
import source.models.expressions.IExpression;
import source.models.types.IntType;
import source.models.types.Type;
import source.models.utils.MyIDictionary;
import source.models.utils.SemaphoreTable;
import source.models.utils.Tuple;
import source.models.values.IValue;
import source.models.values.IntValue;

import java.util.ArrayList;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class NewSemaphoreStatement implements IStatement{
    private final String variableName;
    private final IExpression firstExpression;
    private final IExpression secondExpression;
    private static final Lock lock = new ReentrantLock();

    public NewSemaphoreStatement(String variableName, IExpression firstExpression, IExpression secondExpression) {
        this.variableName = variableName;
        this.firstExpression = firstExpression;
        this.secondExpression = secondExpression;
    }

    @Override
    public String toString() {
        return "newSemaphore(" + variableName + ", " + firstExpression + ", " + secondExpression + ")";
    }

    @Override
    public PrgState execute(PrgState currentState) throws StatementException, ExpressionEvaluationException, InterpreterException {
        lock.lock();
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable();
        SemaphoreTable semaphoreTable = currentState.getSemaphoreTable();
        int freeLocation = semaphoreTable.getFreeLocation();
        if(!symbolTable.isDefined(variableName)) {
            throw new StatementException("Variable not defined!");
        }
        if(!symbolTable.get(variableName).getType().equals(new IntType())) {
            throw new ExpressionEvaluationException("Invalid type of variable!");
        }
        IValue value1 = firstExpression.evaluate(symbolTable, currentState.getHeapTable());
        int number1 = ((IntValue) value1).getValue();
        IValue value2 = secondExpression.evaluate(symbolTable, currentState.getHeapTable());
        int number2 = ((IntValue) value2).getValue();
        semaphoreTable.update(freeLocation, new Tuple<>(number1, new ArrayList<>(), number2));
        symbolTable.update(variableName, new IntValue(freeLocation));
        lock.unlock();
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException {
        Type expType = firstExpression.typeCheck(typeTable);
        Type varType = typeTable.get(variableName);
        if(!(expType.equals(new IntType()) && varType.equals(new IntType()))) {
            throw new InterpreterException("Invalid type!");
        }
        return typeTable;
    }
}
