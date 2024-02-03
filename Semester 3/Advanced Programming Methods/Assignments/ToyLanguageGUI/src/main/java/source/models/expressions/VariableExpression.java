package source.models.expressions;


import source.exceptions.ExpressionEvaluationException;
import source.exceptions.InterpreterException;
import source.models.types.Type;
import source.models.utils.MyIDictionary;
import source.models.utils.MyIHeap;
import source.models.values.IValue;

public class VariableExpression implements IExpression {
    private final String id;

    public VariableExpression(String id) {
        this.id = id;
    }

    @Override
    public IValue evaluate(MyIDictionary<String, IValue> symbolTable, MyIHeap heapTable) throws ExpressionEvaluationException {
        return symbolTable.get(id);
    }

    @Override
    public Type typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException {
        if (!typeTable.isDefined(id))
            throw new InterpreterException(String.format("Variable %s is not defined!", id));
        return typeTable.get(id);
    }

    @Override
    public String toString() {
        return  id;
    }
}
