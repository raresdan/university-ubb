package view;

import controller.Controller;
import exceptions.AnimalNotFoundException;
import model.*;

import java.util.List;
import java.util.Scanner;

public class View {
    Controller controller;

    public View(Controller controller) {
        this.controller = controller;
    }

    public void printMenu() {
        System.out.println("MENU");
        System.out.println("0 - Exit app");
        System.out.println("1 - Display all animals");
        System.out.println("2 - Add an animal");
        System.out.println("3 - Remove an animal");
        System.out.println("4 - Filter by weight");
    }

    public void run() {
        controller.addAnimal(new Bird(2));
        controller.addAnimal(new Cow(50));
        controller.addAnimal(new Cow(30));
        controller.addAnimal(new Bird(5));
        controller.addAnimal(new Pig(3));
        do {
            printMenu();
            Scanner scanner = new Scanner(System.in);
            System.out.println("Option: ");
            String option = scanner.nextLine();
            try {
                switch (option) {
                    case "0":
                        return;
                    case "1":
                        System.out.println("Animals are: ");
                        for (Animal animal : controller.getAll()) {
                            System.out.println(animal.toString());
                        }
                        break;
                    case "2":

                        System.out.println("Enter the type of animal (Bird, Cow, or Pig): ");
                        String animalType = scanner.nextLine();
                        System.out.println("Enter the weight of the animal: ");
                        int weight = Integer.parseInt(scanner.nextLine());
                        Animal newAnimal = null;
                        switch (animalType) {
                            case "Bird":
                                newAnimal = new Bird(weight);
                                break;
                            case "Cow":
                                newAnimal = new Cow(weight);
                                break;
                            case "Pig":
                                newAnimal = new Pig(weight);
                                break;
                            default:
                                System.out.println("Invalid animal type.");
                                break;
                        }
                        controller.addAnimal(newAnimal);
                        System.out.println("Animal added successfully.");
                        break;
                    case "3":
                        System.out.println("Enter the type of animal (Bird, Cow, or Pig) to remove: ");
                        String animalTypeToRemove = scanner.nextLine();
                        System.out.println("Enter the weight of the animal to remove: ");
                        int weightToRemove = Integer.parseInt(scanner.nextLine());
                        Animal animalToRemove = null;
                        for (Animal animal : controller.getAll()) {
                            if (animal.getClass().getSimpleName().equals(animalTypeToRemove) && animal.getWeight() == weightToRemove) {
                                animalToRemove = animal;
                                break;
                            }
                        }

                        controller.removeAnimal(animalToRemove);
                        System.out.println("Animal removed successfully.");
                        break;
                    case "4":
                        System.out.println("Animals heavier than 3kg: ");
                        List<Animal> filtered = this.controller.filter();
                        for (Animal item : filtered) {
                            System.out.println(item.toString());
                        }
                        break;
                    default:
                        break;
                }
            } catch (NumberFormatException | AnimalNotFoundException ex) {

                System.out.println("Invalid animal!");
            }
        } while (true);
    }
}
