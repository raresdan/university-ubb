package source.models.utils;

import javafx.util.Pair;
import source.exceptions.InterpreterException;
import source.models.statements.IStatement;

import java.util.Collection;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class ProcedureTable implements MyIProcedureTable{
    Map<String, javafx.util.Pair<List<String>, IStatement>> procedureTable;

    public ProcedureTable() {
        this.procedureTable = new ConcurrentHashMap<>();
    }

    @Override
    public boolean isDefined(String key) {
        return procedureTable.containsKey(key);
    }


    @Override
    public javafx.util.Pair<List<String>, IStatement> get(String key) throws InterpreterException {
        if(!isDefined(key)) {
            throw new InterpreterException("Key undefined!");
        }
        return procedureTable.get(key);
    }

    @Override
    public void update(String key, javafx.util.Pair<List<String>, IStatement> value) {
        procedureTable.put(key, value);
    }

    @Override
    public Collection<javafx.util.Pair<List<String>, IStatement>> values() {
        return procedureTable.values();
    }

    @Override
    public void remove(String key) throws InterpreterException {
        if(!isDefined(key)) {
            throw new InterpreterException("Key undefined!");
        }
        procedureTable.remove(key);
    }

    @Override
    public Map<String, Pair<List<String>, IStatement>> getContent() {
        return procedureTable;
    }

    @Override
    public MyIProcedureTable deepCopy() throws InterpreterException {
        MyIProcedureTable newProcTable = new ProcedureTable();

        for(String key : procedureTable.keySet())
            newProcTable.update(key, procedureTable.get(key));

        return newProcTable;
    }
}
