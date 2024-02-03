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
import java.io.FileReader;
import java.io.IOException;

public class OpenReadFileStatement implements IStatement {

    private final IExpression fileNameExpression;

    public OpenReadFileStatement(IExpression fileNameExpression) {
        this.fileNameExpression = fileNameExpression;
    }

    @Override
    public PrgState execute(PrgState currentState) throws StatementException, ExpressionEvaluationException, InterpreterException {
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable();
        MyIHeap heapTable = currentState.getHeapTable();
        MyIDictionary<String, BufferedReader> fileTable = currentState.getFileTable();
        IValue fileNameValue = fileNameExpression.evaluate(symbolTable, heapTable);
        if (!fileNameValue.getType().equals(new StringType()))
            throw new ExpressionEvaluationException(fileNameValue + "does not evaluate to a string");
        StringValue filename = (StringValue) fileNameValue;
        if (fileTable.isDefined(filename.getValue()))
            throw new InterpreterException(filename.getValue() + "is already opened!");
        try {
            BufferedReader openedFile = new BufferedReader(new FileReader(filename.getValue()));
            fileTable.put(filename.getValue(), openedFile);
        } catch (IOException e) {
            throw new InterpreterException("Failed to open file " + filename.getValue());
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
        return "fopen(" + fileNameExpression + ")";
    }
}
