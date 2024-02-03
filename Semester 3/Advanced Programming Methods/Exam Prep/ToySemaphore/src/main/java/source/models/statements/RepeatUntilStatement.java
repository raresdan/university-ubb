package source.models.statements;

import source.exceptions.ExpressionEvaluationException;
import source.exceptions.InterpreterException;
import source.exceptions.StatementException;
import source.models.PrgState;
import source.models.expressions.IExpression;
import source.models.expressions.NotExpression;
import source.models.types.BoolType;
import source.models.types.Type;
import source.models.utils.MyIDictionary;

public class RepeatUntilStatement implements IStatement{
    private final IExpression expression;
    private final IStatement statement;

    public RepeatUntilStatement(IStatement statement, IExpression expression) {
        this.statement = statement;
        this.expression = expression;
    }

    @Override
    public String toString() {
        return "repeat{" + statement + "} until (" + expression + ")";
    }

    @Override
    public PrgState execute(PrgState currentState) throws StatementException, ExpressionEvaluationException, InterpreterException {
        IStatement newStatement = new CompoundStatement(statement, new WhileStatement(new NotExpression(expression), statement));
        currentState.getStack().push(newStatement);
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException {
        Type type = expression.typeCheck(typeTable);
        if (!(type.equals(new BoolType()))){
            throw new InterpreterException("Expression is not boolean");
        }
        statement.typeCheck(typeTable);
        return typeTable;
    }
}
