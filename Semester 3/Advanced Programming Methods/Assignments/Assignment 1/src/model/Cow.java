package model;

import java.util.Objects;

public class Cow implements Animal{
    private int weight;

    public Cow(int weight){
        this.weight = weight;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Cow cow = (Cow) o;
        return weight == cow.weight;
    }

    public Cow(){
        this(0);
    }
    @Override
    public int getWeight() {
        return this.weight;
    }

    public String toString() {
        return "Cow " + this.weight + "kg";
    }
}
