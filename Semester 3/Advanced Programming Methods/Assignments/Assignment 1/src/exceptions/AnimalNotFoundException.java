package exceptions;

public class AnimalNotFoundException extends Exception{
    public AnimalNotFoundException() {
        super("Animal not found in the repository.");
    }

    public AnimalNotFoundException(String message) {
        super(message);
    }
}
