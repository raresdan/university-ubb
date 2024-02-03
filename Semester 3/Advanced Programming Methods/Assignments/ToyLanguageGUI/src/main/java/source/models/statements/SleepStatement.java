package source.models.statements;

import source.exceptions.ExpressionEvaluationException;
import source.exceptions.InterpreterException;
import source.exceptions.StatementException;
import source.models.PrgState;
import source.models.types.Type;
import source.models.utils.MyIDictionary;

public class SleepStatement implements IStatement{
    private final int number;

    public SleepStatement(int number) {
        this.number = number;
    }

    @Override
    public String toString() {
        return "sleep(" + number + ')';
    }

    @Override
    public PrgState execute(PrgState currentState) throws StatementException, ExpressionEvaluationException, InterpreterException {
        if (number > 0) {
            currentState.getStack().push(new SleepStatement(number - 1));
        }
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException {
        return typeTable;
    }
}
