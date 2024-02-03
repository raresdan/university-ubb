package source.models.statements;

import source.exceptions.ExpressionEvaluationException;
import source.exceptions.InterpreterException;
import source.exceptions.StackException;
import source.exceptions.StatementException;
import source.models.PrgState;
import source.models.types.Type;
import source.models.utils.MyIDictionary;

public class ReturnStatement implements IStatement{
    @Override
    public PrgState execute(PrgState currentState) throws StatementException, ExpressionEvaluationException, InterpreterException {
        try {
            currentState.getSymbolTable().pop();
        }
        catch (StackException e)
        {
          throw new ExpressionEvaluationException(e.getMessage());
        }
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException {
        return typeTable;
    }

    public String toString() {
        return "return";
    }
}
