package source.models.statements;

import source.exceptions.ExpressionEvaluationException;
import source.exceptions.InterpreterException;
import source.exceptions.StatementException;
import source.models.PrgState;
import source.models.expressions.IExpression;
import source.models.expressions.RelationalExpression;
import source.models.expressions.VariableExpression;
import source.models.types.IntType;
import source.models.types.Type;
import source.models.utils.MyIDictionary;

public class ForStatement implements IStatement{
    private final String variableId;
    private final IExpression firstExpression, secondExpression, thirdExpression;
    IStatement innerStatement;

    public ForStatement(String variableId, IExpression firstExpression, IExpression secondExpression, IExpression thirdExpression, IStatement innerStatement) {
        this.variableId = variableId;
        this.firstExpression = firstExpression;
        this.secondExpression = secondExpression;
        this.thirdExpression = thirdExpression;
        this.innerStatement = innerStatement;
    }

    @Override
    public String toString() {
        return "for(" + variableId + "=" + firstExpression + "; " + variableId + "<" + secondExpression + "; " +
                variableId + "=" + thirdExpression + ") {" + innerStatement + "}";
    }

    @Override
    public PrgState execute(PrgState currentState) throws StatementException, ExpressionEvaluationException, InterpreterException {
        IStatement newStatement = new CompoundStatement(new VariableDeclarationStatement(variableId, new IntType()),
                new CompoundStatement(new AssignStatement(variableId, firstExpression),
                        new WhileStatement(new RelationalExpression(new VariableExpression(variableId), secondExpression, "<"),
                                new CompoundStatement(innerStatement, new AssignStatement(variableId, thirdExpression))
                        )));
        currentState.getStack().push(newStatement);
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException {
        typeTable.update(variableId, new IntType());
        Type type1 = firstExpression.typeCheck(typeTable);
        Type type2 = secondExpression.typeCheck(typeTable);
        Type type3 = thirdExpression.typeCheck(typeTable);
        if (!(type1.equals(new IntType()) && type2.equals(new IntType()) && type3.equals(new IntType()))) {
            throw new InterpreterException("The expression isn't of INT type");
        }
        return typeTable;
    }
}
