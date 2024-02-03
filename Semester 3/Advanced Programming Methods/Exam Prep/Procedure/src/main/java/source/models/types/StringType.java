package source.models.types;


import source.models.values.IValue;
import source.models.values.StringValue;

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
