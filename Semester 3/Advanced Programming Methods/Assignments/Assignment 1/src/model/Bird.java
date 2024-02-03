package model;

import java.util.Objects;

public class Bird implements Animal {

    private int weight;

    public Bird(int weight) {
        this.weight = weight;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Bird bird = (Bird) o;
        return weight == bird.weight;
    }


    public Bird() {
        this(0);
    }

    @Override
    public int getWeight() {
        return weight;
    }

    public String toString() {
        return "Bird " + this.weight + "kg";
    }
}
