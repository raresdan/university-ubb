package models.utils;

import exceptions.StackException;

import java.util.*;

public class MyStack<T> implements MyIStack<T> {
    private final Stack<T> stack;

    public MyStack() {
        this.stack = new Stack<T>();
    }

    @Override
    public T pop() throws StackException {
        if (this.stack.empty())
            throw new StackException("Stack is empty!");
        return this.stack.pop();
    }

    @Override
    public void push(T entityToPush) {
        this.stack.push(entityToPush);
    }

    @Override
    public boolean isEmpty() {

        return this.stack.empty();
    }

    @Override
    public List<T> reverse() {
        ArrayList<T> reversedStack = new ArrayList<>(stack);
        Collections.reverse(reversedStack);
        return reversedStack;
    }

    @Override
    public List<T> getStackAsList() {
        return new ArrayList<>(this.stack);
    }

    @Override
    public String toString() {
        return "MyStack{" + "stack=" + this.reverse() + '}';
    }
}
