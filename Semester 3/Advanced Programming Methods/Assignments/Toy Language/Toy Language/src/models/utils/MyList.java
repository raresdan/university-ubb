package models.utils;

import exceptions.ListException;

import java.util.ArrayList;
import java.util.List;

public class MyList<T> implements MyIList<T> {
    private final List<T> entitiesList;

    public MyList() {
        this.entitiesList = new ArrayList<T>();
    }

    @Override
    public void add(T entityToAdd) {
        this.entitiesList.add(entityToAdd);
    }

    @Override
    public void remove(int position) throws ListException {
        if (position >= this.entitiesList.size())
            throw new ListException("Index out of bounds!");
        this.entitiesList.remove(position);
    }

    @Override
    public boolean remove(T entityToRemove) {
        return this.entitiesList.remove(entityToRemove);
    }

    @Override
    public T get(int position) throws ListException {
        if (position >= this.entitiesList.size())
            throw new ListException("Index out of bounds!");
        return this.entitiesList.get(position);
    }

    @Override
    public void set(int position, T newValue) throws ListException {
        if (position >= this.entitiesList.size())
            throw new ListException("Index out of bounds!");
        this.entitiesList.set(position, newValue);
    }

    @Override
    public List<T> getOutput() {
        return this.entitiesList;
    }

    @Override
    public String toString() {
        return "MyList{" + "entitiesList=" + this.entitiesList + '}';
    }

}
