package source.models.statements;

import source.exceptions.ExpressionEvaluationException;
import source.exceptions.InterpreterException;
import source.exceptions.StatementException;
import source.models.PrgState;
import source.models.expressions.ValueExpression;
import source.models.types.Type;
import source.models.utils.MyIDictionary;
import source.models.values.IntValue;

public class WaitStatement implements IStatement{
    private final int number;

    public WaitStatement(int number) {
        this.number = number;
    }

    @Override
    public String toString() {
        return "wait(" + number + ')';
    }

    @Override
    public PrgState execute(PrgState currentState) throws StatementException, ExpressionEvaluationException, InterpreterException {
        if (number > 0) {
            currentState.getStack().push(new CompoundStatement(new PrintStatement(new ValueExpression(new IntValue(number))),
                    new WaitStatement(number-1)));
        }
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException {
        return typeTable;
    }

}
