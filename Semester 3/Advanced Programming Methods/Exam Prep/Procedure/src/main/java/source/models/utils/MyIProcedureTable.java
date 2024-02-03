package source.models.utils;

import javafx.util.Pair;
import source.exceptions.InterpreterException;
import source.models.statements.IStatement;

import java.util.Collection;
import java.util.List;
import java.util.Map;

public interface MyIProcedureTable {
    boolean isDefined(String key);

    javafx.util.Pair<List<String>, IStatement> get(String key) throws InterpreterException;

    void update(String key, javafx.util.Pair<List<String>, IStatement> value);

    Collection<javafx.util.Pair<List<String>, IStatement>> values();

    void remove(String key) throws InterpreterException;

    Map<String, Pair<List<String>, IStatement>> getContent();

    MyIProcedureTable deepCopy() throws InterpreterException;
}
