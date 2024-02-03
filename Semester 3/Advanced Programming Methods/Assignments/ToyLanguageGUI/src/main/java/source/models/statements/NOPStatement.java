package source.models.statements;


import source.exceptions.InterpreterException;
import source.models.PrgState;
import source.models.types.Type;
import source.models.utils.MyIDictionary;

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
