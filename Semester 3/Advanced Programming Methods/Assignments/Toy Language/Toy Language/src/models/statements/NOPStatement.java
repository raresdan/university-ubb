package models.statements;

import exceptions.InterpreterException;
import models.PrgState;
import models.types.Type;
import models.utils.MyIDictionary;

public class NOPStatement implements IStatement{
    @Override
    public PrgState execute(PrgState currentState) {
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException {
        return typeTable;
    }

    @Override
    public String toString() {
        return "NOP";
    }
}
