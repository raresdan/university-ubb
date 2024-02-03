package models.types;

import models.values.IValue;
import models.values.RefValue;

public class RefType implements Type {
    private final Type inner;

    public RefType(Type inner) {
        this.inner = inner;
    }

    public Type getInner() {
        return this.inner;
    }

    public boolean equals(Object another) {
        if (another instanceof RefType)
            return this.inner.equals(((RefType) another).getInner());
        else
            return false;
    }

    public String toString() {
        return "Ref("+this.inner.toString() + ")";
    }

    @Override
    public IValue defaultValue() {
        return new RefValue(0, this.inner);
    }
}
