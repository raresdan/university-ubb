package source.models.utils;

import source.models.values.IValue;
import java.util.HashMap;
import java.util.Map;

public class MyHeap implements MyIHeap {
    private final Map<Integer, IValue> heapTable;
    private int currentAddress;

    public MyHeap() {
        this.heapTable = new HashMap<>();
        this.currentAddress = 0;
    }

    @Override
    public Map<Integer, IValue> getContent() {
        return this.heapTable;
    }

    @Override
    public int getCurrentAddress() {
        return this.currentAddress;
    }

    @Override
    public IValue getValueAtAddress(int addressToLook) {
        return this.heapTable.get(addressToLook);
    }

    @Override
    public void updateAddress(Integer addressToUpdate, IValue newValue) {
        this.heapTable.put(addressToUpdate, newValue);
    }

    private void incrementAddress() {
        this.currentAddress += 1;
    }

    @Override
    public boolean isDefined(Integer addressToLook) {
        return heapTable.containsKey(addressToLook);
    }

    @Override
    public void setContent(Map<Integer, IValue> newHeapValues) {
        this.heapTable.clear();

        for (Integer address : newHeapValues.keySet()) {
            this.heapTable.put(address, newHeapValues.get(address));
        }
    }

    @Override
    public int allocate(IValue valueToAllocate) {
        this.incrementAddress();
        this.heapTable.put(this.getCurrentAddress(), valueToAllocate);
        return this.getCurrentAddress();
    }

    @Override
    public String toString() {
        return "MyHeap{" +
                "heapTable=" + heapTable +
                '}';
    }

}
