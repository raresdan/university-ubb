package source.models.utils;

import javafx.util.Pair;
import source.exceptions.InterpreterException;

import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class CountSemaphoreTable implements MyICountSemaphoreTable {
    Map<Integer, javafx.util.Pair<Integer, List<Integer>>> semaphoreTable;
    int freeLocation;

    public CountSemaphoreTable() {
        this.semaphoreTable = new ConcurrentHashMap<>();
        this.freeLocation = 0;
    }

    @Override
    public synchronized javafx.util.Pair<Integer, List<Integer>> get(int key) throws InterpreterException {
        if(!isDefined(key)) {
            throw new InterpreterException("Semaphore table doesn't contain that key!");
        }
        return semaphoreTable.get(key);
    }

    @Override
    public boolean isDefined(int key) {
        return semaphoreTable.containsKey(key);
    }

    @Override
    public int getFreeLocation() {
        synchronized (this){
            freeLocation++;
            return freeLocation;
        }
    }

    @Override
    public void update(int key, javafx.util.Pair<Integer, List<Integer>> value) throws InterpreterException {
        synchronized (this){
            semaphoreTable.put(key, value);
        }
    }

    @Override
    public void setFreeLocation(int freeAddress) {
        synchronized (this){
            this.freeLocation = freeAddress;
        }
    }

    @Override
    public Map<Integer, javafx.util.Pair<Integer, List<Integer>>> getContent() {
        synchronized (this){
            return semaphoreTable;
        }
    }

    @Override
    public void setContent(Map<Integer, javafx.util.Pair<Integer, List<Integer>>> newSemaphoreTable) {
        synchronized (this){
            this.semaphoreTable = newSemaphoreTable;
        }
    }

    public String toString(){
        String string = "";
        for (Map.Entry<Integer, Pair<Integer, List<Integer>>> s : semaphoreTable.entrySet()) {
            string += (s.getKey() + " --> " + s.getValue().getKey() + ", " + s.getValue().getValue() + "\n" );
        }
        return string;
    }
}
