package source.models.utils;

import javafx.util.Pair;
import source.exceptions.InterpreterException;

import java.util.List;
import java.util.Map;

public interface MyICountSemaphoreTable {
    Pair<Integer, List<Integer>> get(int key) throws InterpreterException;
    boolean isDefined(int key);
    int getFreeLocation();
    void update(int key,  Pair<Integer, List<Integer>> value) throws InterpreterException;
    void setFreeLocation(int freeAddress);
    Map<Integer,  Pair<Integer, List<Integer>>> getContent();
    void setContent(Map<Integer,  Pair<Integer, List<Integer>>> newSemaphoreTable);
}
