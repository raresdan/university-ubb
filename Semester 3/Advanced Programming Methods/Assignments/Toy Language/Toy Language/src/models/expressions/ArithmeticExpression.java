package models.expressions;

import exceptions.ExpressionEvaluationException;
import exceptions.InterpreterException;
import models.types.Type;
import models.utils.MyIHeap;
import models.values.IValue;
import models.types.IntType;
import models.values.IntValue;
import models.utils.MyIDictionary;

public class ArithmeticExpression implements IExpression {

    private final IExpression firstExpression, secondExpression;
    private final char operation;

    public ArithmeticExpression(char operation, IExpression firstExpression, IExpression secondExpression) {
        this.firstExpression = firstExpression;
        this.secondExpression = secondExpression;
        this.operation = operation;
    }

    @Override
    public IValue evaluate(MyIDictionary<String, IValue> symbolTable, MyIHeap heapTable) throws ExpressionEvaluationException {
        IValue firstValue, secondValue;
        firstValue = this.firstExpression.evaluate(symbolTable, heapTable);
        secondValue = this.secondExpression.evaluate(symbolTable, heapTable);
        if (!firstValue.getType().equals(new IntType()))
            throw new ExpressionEvaluationException("First operand is not integer!");
        if (!secondValue.getType().equals(new IntType()))
            throw new ExpressionEvaluationException("Second operand is not integer!");
        IntValue firstOperand = (IntValue) firstValue;
        IntValue secondOperand = (IntValue) secondValue;
        int firstNumber = firstOperand.getValue();
        int secondNumber = secondOperand.getValue();
        return switch (operation) {
            case '+' -> new IntValue(firstNumber + secondNumber);
            case '-' -> new IntValue(firstNumber - secondNumber);
            case '*' -> new IntValue(firstNumber * secondNumber);
            case '/' -> {
                if (secondNumber == 0)
                    throw new ExpressionEvaluationException("Division by 0!");
                yield new IntValue(firstNumber / secondNumber);
            }
            default -> throw new ExpressionEvaluationException("Undefined operation!");
        };
    }

    @Override
    public Type typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException {
        Type firstExpressionType = firstExpression.typeCheck(typeTable);
        Type secondExpressionType = secondExpression.typeCheck(typeTable);
        if (!firstExpressionType.equals(new IntType()))
            throw new InterpreterException("First operand is not integer!");
        if (!secondExpressionType.equals(new IntType()))
            throw new InterpreterException("Second operand is not integer!");

        return new IntType();
    }

    @Override
    public String toString() {

        return switch (operation) {
            case '+' -> "(" + firstExpression.toString() + " + " + secondExpression.toString() + ")";
            case '-' -> "(" + firstExpression.toString() + " - " + secondExpression.toString() + ")";
            case '*' -> "(" + firstExpression.toString() + " * " + secondExpression.toString() + ")";
            case '/' -> "(" + firstExpression.toString() + " / " + secondExpression.toString() + ")";
            default -> "";
        };
    }
}
