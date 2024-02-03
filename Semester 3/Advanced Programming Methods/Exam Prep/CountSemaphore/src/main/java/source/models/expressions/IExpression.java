package source.models.expressions;


import source.exceptions.ExpressionEvaluationException;
import source.exceptions.InterpreterException;
import source.models.types.Type;
import source.models.utils.MyIDictionary;
import source.models.utils.MyIHeap;
import source.models.values.IValue;

public interface IExpression {
    IValue evaluate(MyIDictionary<String, IValue> symbolTable, MyIHeap heapTable) throws ExpressionEvaluationException;

    Type typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException;
}
