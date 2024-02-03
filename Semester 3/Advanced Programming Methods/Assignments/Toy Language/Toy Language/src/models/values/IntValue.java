package models.values;

import models.types.IntType;
import models.types.Type;

public class IntValue implements IValue {
    private final int value;

    public IntValue(int value) {
        this.value = value;
    }

    public int getValue() {
        return this.value;
    }

    @Override
    public String toString() {
        return Integer.toString(value);
    }

    @Override
    public Type getType() {
        return new IntType();
    }
}
