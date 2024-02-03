package models.expressions;

import exceptions.ExpressionEvaluationException;
import exceptions.InterpreterException;
import models.types.Type;
import models.utils.MyIHeap;
import models.values.IValue;
import models.utils.MyIDictionary;

public interface IExpression {
    IValue evaluate(MyIDictionary<String, IValue> symbolTable, MyIHeap heapTable) throws ExpressionEvaluationException;

    Type typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException;
}
