package source.models.statements;


import source.exceptions.ExpressionEvaluationException;
import source.exceptions.InterpreterException;
import source.models.PrgState;
import source.models.expressions.IExpression;
import source.models.types.Type;
import source.models.utils.MyIDictionary;
import source.models.utils.MyIList;
import source.models.values.IValue;

public class PrintStatement implements IStatement {
    private final IExpression expression;

    public PrintStatement(IExpression expression) {
        this.expression = expression;
    }

    @Override
    public PrgState execute(PrgState currentState) throws ExpressionEvaluationException {
        MyIList<IValue> outputList = currentState.getOutputList();

        outputList.add(expression.evaluate(currentState.getSymbolTable().peek(), currentState.getHeapTable()));

        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException {
        expression.typeCheck(typeTable);
        return typeTable;
    }

    @Override
    public String toString() {
        return "print(" + expression + ")";
    }
}
