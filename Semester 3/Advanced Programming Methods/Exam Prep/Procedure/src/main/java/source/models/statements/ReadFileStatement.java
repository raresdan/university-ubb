package source.models.statements;



import source.exceptions.ExpressionEvaluationException;
import source.exceptions.InterpreterException;
import source.exceptions.StatementException;
import source.models.PrgState;
import source.models.expressions.IExpression;
import source.models.types.IntType;
import source.models.types.StringType;
import source.models.types.Type;
import source.models.utils.MyIDictionary;
import source.models.utils.MyIHeap;
import source.models.values.IValue;
import source.models.values.IntValue;
import source.models.values.StringValue;

import java.io.BufferedReader;
import java.io.IOException;

public class ReadFileStatement implements IStatement {

    private final IExpression fileNameExpression;
    private final String variableId;

    public ReadFileStatement(IExpression fileNameExpression, String variableId) {
        this.fileNameExpression = fileNameExpression;
        this.variableId = variableId;
    }

    @Override
    public PrgState execute(PrgState currentState) throws StatementException, ExpressionEvaluationException, InterpreterException {
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable().peek();
        MyIDictionary<String, BufferedReader> fileTable = currentState.getFileTable();
        MyIHeap heapTable = currentState.getHeapTable();
        if (!symbolTable.isDefined(variableId))
            throw new ExpressionEvaluationException(String.format("Variable %s is not defined!", variableId));
        IValue variableValue = symbolTable.get(variableId);
        if (!variableValue.getType().equals(new IntType()))
            throw new InterpreterException(String.format("Variable %s does not evaluate to integer", variableId));
        IValue fileNameValue = fileNameExpression.evaluate(symbolTable, heapTable);
        if (!fileNameValue.getType().equals(new StringType()))
            throw new InterpreterException(String.format("File %s is not opened!", fileNameValue));
        StringValue filename = (StringValue) fileNameValue;
        BufferedReader openedFile = fileTable.get(filename.getValue());
        try {
            String newValue = openedFile.readLine().strip();
            int valueToAssign;
            if (newValue.isEmpty()) {
                valueToAssign = 0;
            } else {
                valueToAssign = Integer.parseInt(newValue);
            }
            symbolTable.update(variableId, new IntValue(valueToAssign));
        } catch (IOException e) {
            throw new InterpreterException("Failed to read from file " + filename.getValue());
        }
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException {
        if (!fileNameExpression.typeCheck(typeTable).equals(new StringType()))
            throw new InterpreterException("File name is not of type string!");
        if (!typeTable.get(variableId).equals(new IntType()))
            throw  new InterpreterException("Error: Read file requires an int variable as argument!");
        return typeTable;
    }

    @Override
    public String toString() {
        return "fread(" + this.fileNameExpression + ", " + this.variableId + ")";
    }

}
