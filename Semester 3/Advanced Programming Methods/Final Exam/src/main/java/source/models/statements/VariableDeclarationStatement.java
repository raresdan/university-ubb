package source.models.statements;


import source.exceptions.InterpreterException;
import source.exceptions.StatementException;
import source.models.PrgState;
import source.models.types.Type;
import source.models.utils.MyIDictionary;
import source.models.values.IValue;

public class VariableDeclarationStatement implements IStatement {
    private final String variableId;
    private final Type variableType;

    public VariableDeclarationStatement(String variableId, Type variableType) {
        this.variableId = variableId;
        this.variableType = variableType;
    }

    @Override
    public PrgState execute(PrgState currentState) throws StatementException {
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable();

        if (symbolTable.isDefined(variableId))
            throw new StatementException("Variable already defined!");

        symbolTable.put(variableId, variableType.defaultValue());

        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException {
        typeTable.put(variableId, variableType);
        return typeTable;
    }

    @Override
    public String toString() {
        return variableType + " " + variableId;
    }
}
