package view;

import models.utils.MyDictionary;
import models.utils.MyIDictionary;
import view.command.Command;

import java.util.ArrayList;
import java.util.Scanner;

public class TextMenu {
    private final MyIDictionary<String, Command> commands;

    public TextMenu() {
        this.commands = new MyDictionary<>();
    }

    public void addCommand(Command commandToAdd) {
        this.commands.put(commandToAdd.getKey(), commandToAdd);
    }

    private void printMenu() {
        for (String commandKey : this.commands.getKeySet())
            System.out.println(commandKey + " - " + commands.get(commandKey).getDescription());
    }

    public void show() {
        Scanner consoleReader = new Scanner(System.in);
        while (true) {
            this.printMenu();
            System.out.print("Choose an option: ");
            String option = consoleReader.nextLine();
            Command command = commands.get(option);
            if (command == null) {
                System.out.println("Invalid option!");
                continue;
            }
            command.execute();
        }
    }
}
