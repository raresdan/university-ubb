package source.models.values;

import source.models.types.RefType;
import source.models.types.Type;

public class RefValue implements IValue {
    private final int address;
    private final Type locationType;

    public RefValue(int address, Type locationType) {
        this.address = address;
        this.locationType = locationType;
    }

    @Override
    public Type getType() {
        return new RefType(locationType);
    }

    public int getAddress() {
        return this.address;
    }

    @Override
    public String toString() {
        return "Ref(" + this.address + ", " + this.locationType.toString() + ")";
    }
}
