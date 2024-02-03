package models.values;

import models.types.BoolType;
import models.types.Type;

public class BoolValue implements IValue {
    private final boolean value;

    public BoolValue(boolean value) {
        this.value = value;
    }

    public boolean getValue() {
        return this.value;
    }

    @Override
    public Type getType() {
        return new BoolType();
    }

    @Override
    public String toString() {
        return String.valueOf(value);
    }

}
