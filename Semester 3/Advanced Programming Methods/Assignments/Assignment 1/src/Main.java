import controller.Controller;
import repository.IRepository;
import repository.MemoryRepository;
import view.View;

// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Main {
    public static void main(String[] args) {
        IRepository repository = new MemoryRepository();
        Controller controller = new Controller(repository);
        View view = new View(controller);

        view.run();
    }
}