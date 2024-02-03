package source.models.utils;

import source.exceptions.InterpreterException;

import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class SemaphoreTable implements MyISemaphoreTable{
    Map<Integer, Tuple<Integer, List<Integer>, Integer>> semaphoreTable;
    int freeLocation;

    public SemaphoreTable() {
        this.semaphoreTable = new ConcurrentHashMap<>();
        this.freeLocation = 0;
    }

    @Override
    public Tuple<Integer, List<Integer>, Integer> get(int key) throws InterpreterException {
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
    public void update(int key, Tuple<Integer, List<Integer>, Integer> value) throws InterpreterException {
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
    public Map<Integer, Tuple<Integer, List<Integer>, Integer>> getContent() {
        synchronized (this){
            return semaphoreTable;
        }
    }

    @Override
    public void setContent(Map<Integer, Tuple<Integer, List<Integer>, Integer>> newSemaphoreTable) {
        synchronized (this){
            this.semaphoreTable = newSemaphoreTable;
        }
    }

    public String toString(){
        String string = "";
        for (Map.Entry<Integer, Tuple<Integer, List<Integer>, Integer>> s : semaphoreTable.entrySet()) {
            string += (s.getKey() + " --> " + s.getValue().first + ", " + s.getValue().second + ", " + s.getValue().third() + "\n" );
        }
        return string;
    }
}
