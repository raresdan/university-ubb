package source.models.expressions;


import source.exceptions.ExpressionEvaluationException;
import source.exceptions.InterpreterException;
import source.models.types.RefType;
import source.models.types.Type;
import source.models.utils.MyIDictionary;
import source.models.utils.MyIHeap;
import source.models.values.IValue;
import source.models.values.RefValue;

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
