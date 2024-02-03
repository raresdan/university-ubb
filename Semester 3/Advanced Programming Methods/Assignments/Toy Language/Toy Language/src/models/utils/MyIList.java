package models.utils;

import exceptions.ListException;

import java.util.List;

public interface MyIList<T> {
    void add(T entityToAdd);

    void remove(int position) throws ListException;

    boolean remove(T entityToRemove);

    T get(int position) throws ListException;

    void set(int position, T newValue) throws ListException;

    List<T> getOutput();
}
