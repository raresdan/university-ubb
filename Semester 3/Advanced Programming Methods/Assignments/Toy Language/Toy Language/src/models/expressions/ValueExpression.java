package models.expressions;

import exceptions.InterpreterException;
import models.types.Type;
import models.utils.MyIHeap;
import models.values.IValue;
import models.utils.MyIDictionary;

public class ValueExpression implements IExpression {
    private final IValue value;

    public ValueExpression(IValue value) {
        this.value = value;
    }

    @Override
    public IValue evaluate(MyIDictionary<String, IValue> symbolTable, MyIHeap heapTable) {
        return value;
    }

    @Override
    public Type typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException {
        return value.getType();
    }

    @Override
    public String toString() {
        return value.toString();
    }
}
