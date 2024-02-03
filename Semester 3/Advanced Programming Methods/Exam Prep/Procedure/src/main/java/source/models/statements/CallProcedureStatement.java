package source.models.statements;

import source.exceptions.ExpressionEvaluationException;
import source.exceptions.InterpreterException;
import source.exceptions.StatementException;
import source.models.PrgState;
import source.models.expressions.IExpression;
import source.models.types.Type;
import source.models.utils.MyDictionary;
import source.models.utils.MyIDictionary;
import source.models.utils.MyIHeap;
import source.models.utils.MyIProcedureTable;
import source.models.values.IValue;

import java.util.List;

public class CallProcedureStatement implements IStatement{
    private final String procedureName;
    private final List<IExpression> parameters;

    public CallProcedureStatement(String procedureName, List<IExpression> parameters) {
        this.procedureName = procedureName;
        this.parameters = parameters;
    }

    @Override
    public String toString() {
        return "call " + procedureName + "(" + parameters.toString() + ")";
    }

    @Override
    public PrgState execute(PrgState currentState) throws StatementException, ExpressionEvaluationException, InterpreterException {
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable().peek();
        MyIHeap heap = currentState.getHeapTable();
        MyIProcedureTable procTable = currentState.getProcedureTable();
        if(!procTable.isDefined(procedureName)) {
            throw new StatementException("Call: Procedure not defined!");
        }
        List<String> procedureParameters = procTable.get(procedureName).getKey();
        IStatement procedureBody = procTable.get(procedureName).getValue();
        MyIDictionary<String, IValue> newSymbolTable = new MyDictionary<>();
        for (String parameter : procedureParameters) {
            int index = procedureParameters.indexOf(parameter);
            newSymbolTable.update(parameter, parameters.get(index).evaluate(symbolTable, heap));
        }
        currentState.getSymbolTable().push(newSymbolTable);
        currentState.getStack().push(new ReturnStatement());
        currentState.getStack().push(procedureBody);
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typeCheck(MyIDictionary<String, Type> typeTable) throws InterpreterException {
        return typeTable;
    }
}
