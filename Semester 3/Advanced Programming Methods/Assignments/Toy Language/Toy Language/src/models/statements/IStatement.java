package models.statements;

import exceptions.ExpressionEvaluationException;
import exceptions.InterpreterException;
import exceptions.StatementException;
import models.PrgState;
import models.types.Type;
import models.utils.MyIDictionary;

public interface IStatement {
    PrgState execute(PrgState currentState) throws StatementException, ExpressionEvaluationException, InterpreterException;
    MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException;
}
