package source.models.utils;

public class Tuple <T1, T2, T3> {
    final T1 first;
    final T2 second;
    final T3 third;

    public Tuple(T1 first, T2 second, T3 third) {
        this.first = first;
        this.second = second;
        this.third = third;
    }

    public T1 first() {
        return first;
    }

    public T2 second() {
        return second;
    }

    public T3 third() {
        return third;
    }
}
