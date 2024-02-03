package repository;

import exceptions.AnimalNotFoundException;
import model.Animal;

public interface IRepository {

    void addAnimal(Animal newAnimal);
    void removeItem(Animal animalToRemove) throws AnimalNotFoundException;
    Animal[] getAll();
    int getSize();
}
