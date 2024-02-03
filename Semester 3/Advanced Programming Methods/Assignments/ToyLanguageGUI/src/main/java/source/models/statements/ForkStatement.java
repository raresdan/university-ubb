package source.models.statements;


import source.exceptions.InterpreterException;
import source.models.PrgState;
import source.models.types.Type;
import source.models.utils.MyIDictionary;
import source.models.utils.MyIStack;
import source.models.utils.MyStack;

public class ForkStatement implements IStatement{
    private final IStatement innerStatement;

    public ForkStatement(IStatement innerStatement)
    {
        this.innerStatement = innerStatement;
    }

    @Override
    public PrgState execute(PrgState currentState) throws InterpreterException {
        MyIStack<IStatement> newThreadStack = new MyStack<>();
        newThreadStack.push(innerStatement);
        return new PrgState(newThreadStack, currentState.getSymbolTable().copy(), currentState.getOutputList(),
                currentState.getFileTable(), currentState.getHeapTable());
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException {
        innerStatement.typeCheck(typeTable.copy());
        return typeTable;
    }

    @Override
    public String toString() {
        return "fork(" + innerStatement + ")";
    }
}
