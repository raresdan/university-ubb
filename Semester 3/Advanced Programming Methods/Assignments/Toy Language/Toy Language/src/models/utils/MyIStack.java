package models.utils;

import exceptions.StackException;

import java.util.List;

public interface MyIStack<T> {
    T pop() throws StackException;

    void push(T entityToPush);

    boolean isEmpty();

    List<T> reverse();

    List<T> getStackAsList();
}
