package source.models.statements;

import source.exceptions.ExpressionEvaluationException;
import source.exceptions.InterpreterException;
import source.exceptions.StatementException;
import source.models.PrgState;
import source.models.expressions.IExpression;
import source.models.expressions.RelationalExpression;
import source.models.types.Type;
import source.models.utils.MyIDictionary;

public class SwitchStatement implements IStatement{
    private final IExpression mainExpression, firstExpression, secondExpression;
    private final IStatement firstStatement, secondStatement, defaultStatement;

    public SwitchStatement(IExpression mainExpression, IExpression firstExpression, IStatement firstStatement, IExpression secondExpression, IStatement secondStatement, IStatement defaultStatement) {
        this.mainExpression = mainExpression;
        this.firstExpression = firstExpression;
        this.secondExpression = secondExpression;
        this.firstStatement = firstStatement;
        this.secondStatement = secondStatement;
        this.defaultStatement = defaultStatement;
    }

    @Override
    public String toString() {
        return "switch(" + mainExpression + ") (case (" + firstExpression + ") : {" + firstStatement + "}) (case (" +
                secondExpression + ") : {" + secondStatement + "}) (default : {" + defaultStatement + "})";

    }

    @Override
    public PrgState execute(PrgState currentState) throws StatementException, ExpressionEvaluationException, InterpreterException {
        IStatement newStatement = new IfStatement(new RelationalExpression(mainExpression, firstExpression, "=="), firstStatement,
                new IfStatement(new RelationalExpression(mainExpression, secondExpression, "=="), secondStatement, defaultStatement));
        currentState.getStack().push(newStatement);
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException {
        Type type1 = firstExpression.typeCheck(typeTable);
        Type type2 = secondExpression.typeCheck(typeTable);
        Type typeMain = mainExpression.typeCheck(typeTable);
        if (!(type1.equals(type2) && type1.equals(typeMain))) {
            throw new InterpreterException("Expressions don't have the same types");
        }
        firstStatement.typeCheck(typeTable);
        secondStatement.typeCheck(typeTable);
        defaultStatement.typeCheck(typeTable);
        return typeTable;
    }
}
