package source.models.statements;


import source.exceptions.ExpressionEvaluationException;
import source.exceptions.InterpreterException;
import source.exceptions.StatementException;
import source.models.PrgState;
import source.models.types.Type;
import source.models.utils.MyIDictionary;

public interface IStatement {
    PrgState execute(PrgState currentState) throws StatementException, ExpressionEvaluationException, InterpreterException;
    MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException;
}
