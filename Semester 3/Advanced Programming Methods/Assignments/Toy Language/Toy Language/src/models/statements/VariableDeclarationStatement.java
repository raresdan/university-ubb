package models.statements;

import exceptions.InterpreterException;
import exceptions.StatementException;
import models.PrgState;
import models.types.*;
import models.utils.MyIDictionary;
import models.values.IValue;

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
