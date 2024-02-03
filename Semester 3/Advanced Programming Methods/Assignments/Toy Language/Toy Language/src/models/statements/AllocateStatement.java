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

public class AllocateStatement implements  IStatement{
    private final String variableName;
    private final IExpression expression;

    public AllocateStatement(String variableName, IExpression expression)
    {
        this.variableName = variableName;
        this.expression = expression;
    }

    @Override
    public PrgState execute(PrgState currentState) throws StatementException, ExpressionEvaluationException {
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable();
        MyIHeap heapTable = currentState.getHeapTable();
        if (!symbolTable.isDefined(variableName))
            throw new StatementException("Variable " + variableName + " is not defined in symbol table!");
        if (!(symbolTable.get(variableName).getType() instanceof RefType))
            throw new StatementException("Variable " + variableName + " is not of reference type!");
        RefValue variableToAllocate = (RefValue) symbolTable.get(variableName);
        IValue expressionValue = expression.evaluate(symbolTable, heapTable);
        RefType variableType = (RefType) variableToAllocate.getType();
        if (!expressionValue.getType().equals(variableType.getInner()))
            throw new StatementException("Expression does not match location type!");
        int addressOfVariable = heapTable.allocate(expressionValue);
        symbolTable.update(variableName, new RefValue(addressOfVariable, variableType.getInner()));
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException {
        Type variableType = typeTable.get(variableName);
        Type expressionType = expression.typeCheck(typeTable);
        if (!variableType.equals(new RefType(expressionType)))
            throw new InterpreterException("Allocate: left hand side and right hand side have different types!");
        return typeTable;
    }

    @Override
    public String toString() {
        return "new(" + variableName + ", " + expression.toString() + ")";
    }
}
