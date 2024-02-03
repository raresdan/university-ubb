package models.statements;

import exceptions.ExpressionEvaluationException;
import exceptions.InterpreterException;
import exceptions.StatementException;
import models.PrgState;
import models.expressions.IExpression;
import models.types.RefType;
import models.types.Type;
import models.utils.MyIDictionary;
import models.utils.MyIHeap;
import models.values.IValue;
import models.values.RefValue;

public class WriteHeapStatement implements IStatement{
    private final String variableName;
    private final IExpression expression;

    public WriteHeapStatement(String variableName, IExpression expression) {
        this.variableName = variableName;
        this.expression = expression;
    }

    @Override
    public PrgState execute(PrgState currentState) throws StatementException, ExpressionEvaluationException {
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable();
        MyIHeap heapTable = currentState.getHeapTable();
        if (!symbolTable.isDefined(variableName))
            throw new StatementException(String.format("Variable %s is not defined!", variableName));
        if (!(symbolTable.get(variableName).getType() instanceof RefType))
            throw new StatementException(String.format("Variable %s is not of type reference!", variableName));
        RefValue variableToModify = (RefValue) symbolTable.get(variableName);
        if (!heapTable.isDefined(variableToModify.getAddress()))
            throw new StatementException(String.format("The address referenced by %s is not defined in heap!", variableName));
        IValue newValue = this.expression.evaluate(symbolTable, heapTable);
        RefType variableType = (RefType) variableToModify.getType();
        if (!newValue.getType().equals(variableType.getInner()))
            throw new StatementException(String.format("New value does not have the same type as the one referenced by %s", variableName));
        heapTable.updateAddress(variableToModify.getAddress(), newValue);
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException {
        if (!typeTable.get(variableName).equals(new RefType(expression.typeCheck(typeTable))))
            throw new InterpreterException("Write Heap: left hand side and right hand side have different types!");
        return typeTable;
    }

    @Override
    public String toString() {
        return "writeHeap(" + this.variableName + ", " + this.expression + ")";
    }
}
