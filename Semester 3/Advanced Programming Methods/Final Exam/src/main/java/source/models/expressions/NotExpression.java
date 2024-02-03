package source.models.expressions;

import source.exceptions.ExpressionEvaluationException;
import source.exceptions.InterpreterException;
import source.models.types.BoolType;
import source.models.types.Type;
import source.models.utils.MyIDictionary;
import source.models.utils.MyIHeap;
import source.models.values.BoolValue;
import source.models.values.IValue;

public class NotExpression implements IExpression{
    private final IExpression expression;

    public NotExpression(IExpression expression) {
        this.expression = expression;
    }

    @Override
    public String toString() {
        return "!(" + expression + ")";
    }

    @Override
    public IValue evaluate(MyIDictionary<String, IValue> symbolTable, MyIHeap heapTable) throws ExpressionEvaluationException {
        if (!(expression.evaluate(symbolTable, heapTable).getType().equals(new BoolType()))) {
            throw new ExpressionEvaluationException("Expression not boolean!");
        }
        BoolValue value = (BoolValue) expression.evaluate(symbolTable, heapTable);
        if (value.getValue()){
            return new BoolValue(false);
        }
        return new BoolValue(true);
    }

    @Override
    public Type typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException {
        return expression.typeCheck(typeTable);
    }
}
