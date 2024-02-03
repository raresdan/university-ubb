package models.expressions;

import exceptions.ExpressionEvaluationException;
import exceptions.InterpreterException;
import models.types.BoolType;
import models.types.Type;
import models.utils.MyIHeap;
import models.values.BoolValue;
import models.values.IValue;
import models.utils.MyIDictionary;

public class LogicExpression implements IExpression {
    private final IExpression firstExpression, secondExpression;
    private final String operation;

    public LogicExpression(IExpression firstExpression, IExpression secondExpression, String operation) {
        this.firstExpression = firstExpression;
        this.secondExpression = secondExpression;
        this.operation = operation;
    }

    @Override
    public IValue evaluate(MyIDictionary<String, IValue> symbolTable, MyIHeap heapTable) throws ExpressionEvaluationException {
        IValue firstValue = firstExpression.evaluate(symbolTable, heapTable);
        IValue secondValue = secondExpression.evaluate(symbolTable, heapTable);
        if (!firstValue.getType().equals(new BoolType()))
            throw new ExpressionEvaluationException("First operand is not bool!");
        if (!secondValue.getType().equals(new BoolType()))
            throw new ExpressionEvaluationException("Second operand is not bool!");
        BoolValue firstOperand = (BoolValue) firstValue;
        BoolValue secondOperand = (BoolValue) secondValue;
        return switch (operation) {
            case "&&" -> new BoolValue(firstOperand.getValue() && secondOperand.getValue());
            case "||" -> new BoolValue(firstOperand.getValue() || secondOperand.getValue());
            default -> null;
        };
    }

    @Override
    public Type typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException {
        Type firstExpressionType = firstExpression.typeCheck(typeTable);
        Type secondExpressionType = secondExpression.typeCheck(typeTable);
        if (!firstExpressionType.equals(new BoolType()))
            throw new InterpreterException("First operand is not bool!");
        if (!secondExpressionType.equals(new BoolType()))
            throw new InterpreterException("Second operand is not bool");
        return new BoolType();
    }

    @Override
    public String toString() {
        return switch (operation) {
            case "&&" -> "(" + firstExpression + " && " + secondExpression + ")";
            case "||" -> "(" + firstExpression + " || " + secondExpression + ")";

            default -> "";
        };
    }
}
