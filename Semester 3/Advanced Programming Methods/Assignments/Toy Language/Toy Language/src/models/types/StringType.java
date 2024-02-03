package models.types;

import models.values.IValue;
import models.values.StringValue;

public class StringType implements Type {
    @Override
    public boolean equals(Object object) {
        return object instanceof StringType;
    }

    @Override
    public String toString() {
        return "str";
    }

    @Override
    public IValue defaultValue() {
        return new StringValue("");
    }
}
