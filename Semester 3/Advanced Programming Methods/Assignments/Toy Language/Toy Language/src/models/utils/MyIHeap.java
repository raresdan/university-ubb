package models.utils;

import models.values.IValue;

import java.util.Map;

public interface MyIHeap {
    int getCurrentAddress();
    int allocate(IValue valueToAllocate);
    Map<Integer, IValue> getContent();
    IValue getValueAtAddress(int addressToGet);
    void updateAddress(Integer addressToUpdate, IValue newValue);
    boolean isDefined(Integer addressToLook);
    void setContent(Map<Integer, IValue> newHeapValues);
}
