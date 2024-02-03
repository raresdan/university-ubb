package models.statements;

import exceptions.ExpressionEvaluationException;
import exceptions.InterpreterException;
import models.PrgState;
import models.expressions.IExpression;
import models.types.Type;
import models.utils.MyIDictionary;
import models.values.IValue;
import models.utils.MyIList;

public class PrintStatement implements IStatement {
    private final IExpression expression;

    public PrintStatement(IExpression expression) {
        this.expression = expression;
    }

    @Override
    public PrgState execute(PrgState currentState) throws ExpressionEvaluationException {
        MyIList<IValue> outputList = currentState.getOutputList();

        outputList.add(expression.evaluate(currentState.getSymbolTable(), currentState.getHeapTable()));

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
