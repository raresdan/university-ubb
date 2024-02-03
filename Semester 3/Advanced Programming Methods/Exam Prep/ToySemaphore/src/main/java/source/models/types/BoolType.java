package source.models.types;


import source.models.values.BoolValue;
import source.models.values.IValue;

public class BoolType implements Type {
    @Override
    public boolean equals(Object object) {
        return object instanceof BoolType;
    }

    @Override
    public String toString() {
        return "bool";
    }

    @Override
    public IValue defaultValue() {
        return new BoolValue(false);
    }
}
