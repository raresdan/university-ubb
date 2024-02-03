package source.models.statements;


import source.exceptions.ExpressionEvaluationException;
import source.exceptions.InterpreterException;
import source.models.PrgState;
import source.models.types.Type;
import source.models.utils.MyIDictionary;
import source.models.utils.MyIStack;

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
        return firstStatement.toString() + "; " + secondStatement.toString();
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
