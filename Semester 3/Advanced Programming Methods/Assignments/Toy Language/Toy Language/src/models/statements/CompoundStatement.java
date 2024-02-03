package models.statements;

import exceptions.ExpressionEvaluationException;
import exceptions.InterpreterException;
import models.PrgState;
import models.types.Type;
import models.utils.MyIDictionary;
import models.utils.MyIStack;

public class CompoundStatement implements IStatement {
    private final IStatement firstStatement, secondStatement;

    public CompoundStatement(IStatement firstStatement, IStatement secondStatement) {
        this.firstStatement = firstStatement;
        this.secondStatement = secondStatement;
    }

    public IStatement getFirstStatement() {
        return this.firstStatement;
    }

    public IStatement getSecondStatement() {
        return this.secondStatement;
    }

    @Override
    public String toString() {
        return firstStatement.toString() + ";" + secondStatement.toString();
    }

    @Override
    public PrgState execute(PrgState currentState) throws ExpressionEvaluationException {
        MyIStack<IStatement> exeStack = currentState.getStack();
        exeStack.push(secondStatement);
        exeStack.push(firstStatement);
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException {
        return secondStatement.typeCheck(firstStatement.typeCheck(typeTable));
    }
}
