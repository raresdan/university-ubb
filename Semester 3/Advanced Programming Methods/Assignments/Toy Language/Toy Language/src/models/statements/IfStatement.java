package models.statements;

import exceptions.ExpressionEvaluationException;
import exceptions.InterpreterException;
import models.PrgState;
import models.expressions.IExpression;
import models.types.BoolType;
import models.types.Type;
import models.utils.MyIDictionary;
import models.utils.MyIHeap;
import models.values.BoolValue;
import models.values.IValue;
import models.utils.MyIStack;

public class IfStatement implements IStatement{
    private final IExpression expressionToEvaluate;
    private final IStatement firstStatement, secondStatement;

    public IfStatement(IExpression expressionToEvaluate, IStatement firstStatement, IStatement secondStatement)
    {
        this.expressionToEvaluate = expressionToEvaluate;
        this.firstStatement = firstStatement;
        this.secondStatement = secondStatement;
    }

    @Override
    public PrgState execute(PrgState currentState) throws ExpressionEvaluationException {
        MyIStack<IStatement> exeStack = currentState.getStack();
        MyIHeap heapTable = currentState.getHeapTable();
        IValue conditionToEvaluate = expressionToEvaluate.evaluate(currentState.getSymbolTable(), heapTable);
        if (!conditionToEvaluate.getType().equals(new BoolType()))
            throw new ExpressionEvaluationException("Conditional expression is not boolean!");
        BoolValue conditionValue = (BoolValue) conditionToEvaluate;
        if (conditionValue.getValue())
            exeStack.push(firstStatement);
        else
            exeStack.push(secondStatement);
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException {
        Type expressionType = expressionToEvaluate.typeCheck(typeTable);
        if (!expressionType.equals(new BoolType()))
            throw new InterpreterException("If expression is not of type boolean!");
        firstStatement.typeCheck(typeTable.copy());
        secondStatement.typeCheck(typeTable.copy());
        return typeTable;
    }

    @Override
    public String toString() {
        return "if " + expressionToEvaluate + " then " + firstStatement
                + " else " + secondStatement;
    }
}
