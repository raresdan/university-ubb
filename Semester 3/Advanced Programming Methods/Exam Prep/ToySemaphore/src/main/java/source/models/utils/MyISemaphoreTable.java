package source.models.utils;

import source.exceptions.InterpreterException;

import java.util.List;
import java.util.Map;

public interface MyISemaphoreTable {
    Tuple<Integer, List<Integer>, Integer> get(int key) throws InterpreterException;
    boolean isDefined(int key);
    int getFreeLocation();
    void update(int key,  Tuple<Integer, List<Integer>, Integer> value) throws InterpreterException;
    void setFreeLocation(int freeAddress);
    Map<Integer, Tuple<Integer, List<Integer>, Integer>> getContent();
    void setContent(Map<Integer,  Tuple<Integer, List<Integer>, Integer>> newSemaphoreTable);
}
