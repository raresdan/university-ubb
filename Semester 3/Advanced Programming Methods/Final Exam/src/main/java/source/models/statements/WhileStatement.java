package source.models.statements;


import source.exceptions.ExpressionEvaluationException;
import source.exceptions.InterpreterException;
import source.exceptions.StatementException;
import source.models.PrgState;
import source.models.expressions.IExpression;
import source.models.types.BoolType;
import source.models.types.Type;
import source.models.utils.MyIDictionary;
import source.models.utils.MyIHeap;
import source.models.utils.MyIStack;
import source.models.values.BoolValue;
import source.models.values.IValue;

public class WhileStatement implements IStatement{
    private final IExpression expression;
    private final IStatement innerStatement;

    public WhileStatement(IExpression expressionToEvaluate, IStatement innerStatement)
    {
        this.expression = expressionToEvaluate;
        this.innerStatement = innerStatement;
    }

    @Override
    public PrgState execute(PrgState currentState) throws StatementException, ExpressionEvaluationException {
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable();
        MyIHeap heapTable = currentState.getHeapTable();
        MyIStack<IStatement> programStack = currentState.getStack();
        IValue evaluatedExpression = expression.evaluate(symbolTable, heapTable);
        if (!evaluatedExpression.getType().equals(new BoolType()))
            throw new StatementException("Expression cannot be evaluated as boolean!");
        BoolValue expressionValue = (BoolValue) evaluatedExpression;
        if (!expressionValue.getValue())
            return currentState;
        programStack.push(this);
        programStack.push(innerStatement);
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException {
        innerStatement.typeCheck(typeTable.copy());
        return typeTable;
    }

    @Override
    public String toString() {
        return "while(" + this.expression + ") { " + this.innerStatement + " }";
    }
}
