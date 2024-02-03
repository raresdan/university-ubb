package models.expressions;

import exceptions.ExpressionEvaluationException;
import exceptions.InterpreterException;
import models.types.RefType;
import models.types.Type;
import models.utils.MyIHeap;
import models.values.IValue;
import models.utils.MyIDictionary;
import models.values.RefValue;

public class ReadHeapExpression implements IExpression{
    private final IExpression expression;

    public ReadHeapExpression(IExpression expressionToEvaluate)
    {
        this.expression = expressionToEvaluate;
    }

    @Override
    public IValue evaluate(MyIDictionary<String, IValue> symbolTable, MyIHeap heapTable) throws ExpressionEvaluationException {
        IValue innerExpressionValue = expression.evaluate(symbolTable, heapTable);

        if (! (innerExpressionValue instanceof RefValue expressionValue))
            throw new ExpressionEvaluationException ("Expression is not of type reference!");
        int addressToRead = expressionValue.getAddress();
        IValue valueFound = heapTable.getValueAtAddress(addressToRead);
        if (valueFound == null)
            throw new ExpressionEvaluationException("The address is not allocated in heap table!");
        return valueFound;
    }

    @Override
    public Type typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException {
        Type expressionType = expression.typeCheck(typeTable);
        if (!(expressionType instanceof RefType))
            throw new InterpreterException("Read Heap expression is not of type reference!");
        return ((RefType) expressionType).getInner();
    }

    @Override
    public String toString() {
        return "readHeap(" + expression + ")";
    }
}
