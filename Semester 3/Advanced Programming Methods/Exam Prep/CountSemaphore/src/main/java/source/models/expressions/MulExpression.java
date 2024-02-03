package source.models.expressions;

import source.exceptions.ExpressionEvaluationException;
import source.exceptions.InterpreterException;
import source.models.types.IntType;
import source.models.types.Type;
import source.models.utils.MyIDictionary;
import source.models.utils.MyIHeap;
import source.models.values.IValue;

public class MulExpression implements IExpression{
    private final IExpression firstExpression, secondExpression;

    public MulExpression(IExpression firstExpression, IExpression secondExpression) {
        this.firstExpression = firstExpression;
        this.secondExpression = secondExpression;
    }

    @Override
    public String toString() {
        return "Mul(" + firstExpression + ", " + secondExpression + ")";
    }

    @Override
    public IValue evaluate(MyIDictionary<String, IValue> symbolTable, MyIHeap heapTable) throws ExpressionEvaluationException {
        IExpression e = new ArithmeticExpression('-',
                new ArithmeticExpression('*', firstExpression, secondExpression),
                new ArithmeticExpression('+', firstExpression, secondExpression)
        );

        return e.evaluate(symbolTable, heapTable);
    }

    @Override
    public Type typeCheck(MyIDictionary<String, Type> typeEnv) throws InterpreterException {
        Type type1 = firstExpression.typeCheck(typeEnv);
        Type type2 = secondExpression.typeCheck(typeEnv);

        if (! (type1.equals(new IntType()) && type2.equals(new IntType()))) {
            throw new InterpreterException("Expression not integer");
        }
        return new IntType();
    }
}
