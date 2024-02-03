package source.models.statements;


import source.exceptions.ExpressionEvaluationException;
import source.exceptions.InterpreterException;
import source.exceptions.StatementException;
import source.models.PrgState;
import source.models.expressions.IExpression;
import source.models.types.RefType;
import source.models.types.Type;
import source.models.utils.MyIDictionary;
import source.models.utils.MyIHeap;
import source.models.values.IValue;
import source.models.values.RefValue;

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
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable().peek();
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
