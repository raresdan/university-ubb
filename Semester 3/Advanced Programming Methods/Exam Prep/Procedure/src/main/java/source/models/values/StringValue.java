package source.models.values;


import source.models.types.StringType;
import source.models.types.Type;

public class StringValue implements IValue {
    private final String value;

    public StringValue(String value) {
        this.value = value;
    }

    public String getValue() {
        return this.value;
    }

    @Override
    public boolean equals(Object object) {
        if (!(object instanceof StringValue))
            return false;
        StringValue objectValue = (StringValue) object;
        return this.getValue().equals((objectValue.getValue()));
    }

    @Override
    public Type getType() {
        return new StringType();
    }

    @Override
    public String toString() {
        return value;
    }
}
