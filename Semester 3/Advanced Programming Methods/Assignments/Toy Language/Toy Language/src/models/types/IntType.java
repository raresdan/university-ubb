package models.types;

import models.values.IValue;
import models.values.IntValue;

public class IntType implements Type {
    @Override
    public boolean equals(Object object) {
        return object instanceof IntType;
    }

    @Override
    public String toString() {
        return "int";
    }

    @Override
    public IValue defaultValue() {
        return new IntValue(0);
    }
}
