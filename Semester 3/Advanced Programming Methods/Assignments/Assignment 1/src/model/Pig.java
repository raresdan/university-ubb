package model;

import java.util.Objects;

public class Pig implements Animal{
    private int weight;

    public Pig(int weight){
        this.weight = weight;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Pig pig = (Pig) o;
        return weight == pig.weight;
    }


    public Pig(){
        this(0);
    }
    @Override
    public int getWeight() {
        return this.weight;
    }

    public String toString() {
        return "Pig " + this.weight + "kg";
    }
}
