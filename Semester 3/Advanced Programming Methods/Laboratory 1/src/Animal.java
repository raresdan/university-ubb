public class Animal {
    String type;
    int weight;

    public Animal(String type, int weight) {
        this.type = type;
        this.weight = weight;
    }

    public String talk() {
        return "";
    }
}


class Dog extends Animal {
    public Dog(String type, int weight) {
        super(type, weight);
    }

    @Override
    public String talk() {
        return "Bark";
    }
}

class Fox extends Animal {

    public Fox(String type, int weight) {
        super(type, weight);
    }

    public String talk(String sound) {
        return sound;
    }
}
