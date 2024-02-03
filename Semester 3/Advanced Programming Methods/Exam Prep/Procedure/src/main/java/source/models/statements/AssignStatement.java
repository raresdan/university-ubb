package source.models.statements;


import source.exceptions.ExpressionEvaluationException;
import source.exceptions.InterpreterException;
import source.models.PrgState;
import source.models.expressions.IExpression;
import source.models.types.Type;
import source.models.utils.MyIDictionary;
import source.models.utils.MyIHeap;
import source.models.values.IValue;

public class AssignStatement implements IStatement {
    private final String variableId;
    private final IExpression expressionToAssign;

    public AssignStatement(String variableId, IExpression expressionToAssign) {
        this.variableId = variableId;
        this.expressionToAssign = expressionToAssign;
    }

    @Override
    public PrgState execute(PrgState currentState) throws ExpressionEvaluationException {
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable().peek();
        MyIHeap heapTable = currentState.getHeapTable();
        if (!symbolTable.isDefined(variableId))
            throw new ExpressionEvaluationException("Assignment: Variable " + variableId + " is not defined!");
        IValue valueToAssign = expressionToAssign.evaluate(symbolTable, heapTable);
        IValue variableValue = symbolTable.get(variableId);
        if (!valueToAssign.getType().equals(variableValue.getType()))
            throw new ExpressionEvaluationException("Assignment: Type of variable do not match type of expression!");
        symbolTable.update(variableId, valueToAssign);
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException {
        Type expressionType = expressionToAssign.typeCheck(typeTable);
        if (!typeTable.isDefined(variableId))
            throw new InterpreterException(String.format("Assignment: Variable %s is not defined!", variableId));
        Type variableType = typeTable.get(variableId);
        if (!variableType.equals(expressionType))
            throw new InterpreterException("Assignment: Left hand side and right hand side have different types!");
        return typeTable;
    }

    @Override
    public String toString() {
        return variableId + " = " + expressionToAssign;
    }
}
