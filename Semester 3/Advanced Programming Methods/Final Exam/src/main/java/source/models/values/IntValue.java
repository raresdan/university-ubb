package source.models.values;

import source.models.types.IntType;
import source.models.types.Type;

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
