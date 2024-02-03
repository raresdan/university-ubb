package models.statements;

import exceptions.ExpressionEvaluationException;
import exceptions.InterpreterException;
import exceptions.StatementException;
import models.PrgState;
import models.expressions.IExpression;
import models.types.Type;
import models.utils.MyIHeap;
import models.values.IValue;
import models.types.StringType;
import models.values.StringValue;
import models.utils.MyIDictionary;

import java.io.BufferedReader;
import java.io.IOException;

public class CloseReadFileStatement implements IStatement{
    private final IExpression fileNameExpression;

    public CloseReadFileStatement(IExpression fileNameExpression){
        this.fileNameExpression = fileNameExpression;
    }
    @Override
    public PrgState execute(PrgState currentState) throws StatementException, ExpressionEvaluationException, InterpreterException {
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable();
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
