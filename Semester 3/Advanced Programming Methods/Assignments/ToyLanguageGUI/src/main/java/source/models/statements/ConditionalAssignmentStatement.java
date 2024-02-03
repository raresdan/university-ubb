package source.models.statements;

import source.exceptions.ExpressionEvaluationException;
import source.exceptions.InterpreterException;
import source.exceptions.StatementException;
import source.models.PrgState;
import source.models.expressions.IExpression;
import source.models.types.BoolType;
import source.models.types.Type;
import source.models.utils.MyIDictionary;

public class ConditionalAssignmentStatement implements IStatement{
    private final String variableId;
    private final IExpression firstExpression, secondExpression, thirdExpression;
    public ConditionalAssignmentStatement(String variableId, IExpression firstExpression, IExpression secondExpression, IExpression thirdExpression) {
        this.variableId = variableId;
        this.firstExpression = firstExpression;
        this.secondExpression = secondExpression;
        this.thirdExpression = thirdExpression;
    }

    @Override
    public String toString()
    {
        return variableId + "=" + firstExpression + "?" + secondExpression + ":" + thirdExpression;
    }

    @Override
    public PrgState execute(PrgState currentState) throws StatementException, ExpressionEvaluationException, InterpreterException {
        IStatement newStatement = new IfStatement(firstExpression, new AssignStatement(variableId, secondExpression),
                new AssignStatement(variableId, thirdExpression));
        currentState.getStack().push(newStatement);
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException {
        Type type1 = firstExpression.typeCheck(typeTable);
        Type type2 = secondExpression.typeCheck(typeTable);
        Type type3 = thirdExpression.typeCheck(typeTable);
        Type varType = typeTable.get(variableId);
        if (!(type1.equals(new BoolType()) && varType.equals(type2) && varType.equals(type3))) {
            throw new InterpreterException("Invalid types of expressions/variable");
        }
        return typeTable;
    }
}
