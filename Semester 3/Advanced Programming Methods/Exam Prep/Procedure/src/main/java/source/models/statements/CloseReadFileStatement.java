package source.models.statements;



import source.exceptions.ExpressionEvaluationException;
import source.exceptions.InterpreterException;
import source.exceptions.StatementException;
import source.models.PrgState;
import source.models.expressions.IExpression;
import source.models.types.StringType;
import source.models.types.Type;
import source.models.utils.MyIDictionary;
import source.models.utils.MyIHeap;
import source.models.values.IValue;
import source.models.values.StringValue;

import java.io.BufferedReader;
import java.io.IOException;

public class CloseReadFileStatement implements IStatement{
    private final IExpression fileNameExpression;

    public CloseReadFileStatement(IExpression fileNameExpression){
        this.fileNameExpression = fileNameExpression;
    }
    @Override
    public PrgState execute(PrgState currentState) throws StatementException, ExpressionEvaluationException, InterpreterException {
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable().peek();
        MyIDictionary<String, BufferedReader> fileTable = currentState.getFileTable();
        MyIHeap heapTable = currentState.getHeapTable();
        IValue fileNameValue = fileNameExpression.evaluate(symbolTable, heapTable);
        if (!fileNameValue.getType().equals(new StringType()))
            throw new ExpressionEvaluationException(fileNameExpression + "does not evaluate to a string!");
        StringValue filename = (StringValue) fileNameValue;
        if (!fileTable.isDefined(filename.getValue()))
            throw new InterpreterException("File " + filename.getValue() + " is not opened!");
        BufferedReader fileToClose = fileTable.get(filename.getValue());
        try {
            fileToClose.close();
            fileTable.remove(filename.getValue());
        } catch (IOException e) {
            throw new InterpreterException("Failed to close file " + filename.getValue() + " !") ;
        }
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException {
        if (!fileNameExpression.typeCheck(typeTable).equals(new StringType()))
            throw new InterpreterException("File name is not of type string!");
        return typeTable;
    }

    @Override
    public String toString() {
        return "fclose(" + this.fileNameExpression + ")";
    }
}
