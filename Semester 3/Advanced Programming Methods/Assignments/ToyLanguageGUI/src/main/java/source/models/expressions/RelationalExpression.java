package source.models.expressions;


import source.exceptions.ExpressionEvaluationException;
import source.exceptions.InterpreterException;
import source.models.types.BoolType;
import source.models.types.IntType;
import source.models.types.Type;
import source.models.utils.MyIDictionary;
import source.models.utils.MyIHeap;
import source.models.values.BoolValue;
import source.models.values.IValue;
import source.models.values.IntValue;

public class RelationalExpression implements IExpression {
    private final IExpression firstExpression, secondExpression;
    private final String operation;

    public RelationalExpression(IExpression firstExpression, IExpression secondExpression, String operation) {
        this.firstExpression = firstExpression;
        this.secondExpression = secondExpression;
        this.operation = operation;
    }

    @Override
    public IValue evaluate(MyIDictionary<String, IValue> symbolTable, MyIHeap heapTable) throws ExpressionEvaluationException {
        IValue firstValue = this.firstExpression.evaluate(symbolTable, heapTable);
        IValue secondValue = this.secondExpression.evaluate(symbolTable, heapTable);
        if (!firstValue.getType().equals(new IntType()))
            throw new ExpressionEvaluationException("First operand does not evaluate to an integer");
        if (!secondValue.getType().equals(new IntType()))
            throw new ExpressionEvaluationException("Second operand does not evaluate to an integer");
        int firstInteger = ((IntValue) firstValue).getValue();
        int secondInteger = ((IntValue) secondValue).getValue();
        return switch (this.operation) {
            case "<" -> new BoolValue(firstInteger < secondInteger);
            case "<=" -> new BoolValue(firstInteger <= secondInteger);
            case "==" -> new BoolValue(firstInteger == secondInteger);
            case "!=" -> new BoolValue(firstInteger != secondInteger);
            case ">" -> new BoolValue(firstInteger > secondInteger);
            case ">=" -> new BoolValue(firstInteger >= secondInteger);
            default -> throw new ExpressionEvaluationException("Invalid comparison between operands!");
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
        return new BoolType();
    }

    @Override
    public String toString() {
        return this.firstExpression + " " + this.operation + " " + this.secondExpression;
    }
}
