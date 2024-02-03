package repository;

import exceptions.AnimalNotFoundException;
import model.Animal;

public class MemoryRepository implements IRepository{

    Animal[] animals;
    int length;

    public MemoryRepository(){
        this.animals = new Animal[100];
        this.length = 0;
    }
    @Override
    public void addAnimal(Animal newAnimal) {
        if (length >= animals.length) {
            throw new IndexOutOfBoundsException("Repository is full, cannot add more animals.");
        }
        this.animals[length++] = newAnimal;
    }

    @Override
    public void removeItem(Animal animalToRemove) throws AnimalNotFoundException {
        int indexToRemove = -1;
        for(int i=0; i < length; i++){
            if(animals[i].equals(animalToRemove)){
                indexToRemove = i;
                break;
            }
        }
        if (indexToRemove == -1){
            throw new AnimalNotFoundException("Animal not found in the repository.");
        }
        for(int i=indexToRemove; i < length; i++){
            animals[i] = animals[i+1];
        }
        animals[length-1] = null;
        length--;
    }

    @Override
    public Animal[] getAll() {
        return this.animals;
    }

    @Override
    public int getSize() {
        return this.length;
    }
}
