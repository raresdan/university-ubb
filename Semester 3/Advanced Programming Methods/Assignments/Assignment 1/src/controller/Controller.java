package controller;


import exceptions.AnimalNotFoundException;
import model.Animal;
import repository.IRepository;

import java.util.ArrayList;
import java.util.List;

public class Controller {
    IRepository repository;
    public Controller(IRepository repo) {
        this.repository = repo;
    }

    public void addAnimal(Animal newAnimal) {
        this.repository.addAnimal(newAnimal);
    }

    public void removeAnimal(Animal animalToRemove) throws AnimalNotFoundException {
        this.repository.removeItem(animalToRemove);
    }

    public List<Animal> filter() {
        List<Animal> filteredAnimals= new ArrayList<>();
        for (Animal animal : getAll()) {
            if (animal.getWeight() > 3) {
                filteredAnimals.add(animal);
            }
        }
        return filteredAnimals;
    }

    public List<Animal> getAll() {
        List<Animal> animals = new ArrayList<>();
        for (int i = 0; i < this.repository.getSize(); i++) {
            animals.add(this.repository.getAll()[i]);
        }
        return animals;
    }
}
