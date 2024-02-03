package view.command;

import controller.Controller;
import exceptions.ExpressionEvaluationException;
import exceptions.InterpreterException;
import exceptions.StackException;
import exceptions.StatementException;
import models.PrgState;
import models.statements.IStatement;
import models.utils.MyDictionary;
import repository.IRepository;
import repository.ProgramsRepository;

import java.io.IOException;

public class RunCommand extends Command {
    private final IStatement programStatement;

    public RunCommand(String key, String description, IStatement programStatement) {
        super(key, description);
        this.programStatement = programStatement;
    }

    @Override
    public void execute() {
        try {
            programStatement.typeCheck(new MyDictionary<>());
        }
        catch (InterpreterException e)
        {
            System.out.println(e.getMessage());
            return;
        }
        String logFilePath = "log" + this.getKey() + ".txt";
        PrgState currentProgram = new PrgState(programStatement);
        IRepository repository = new ProgramsRepository(logFilePath);
        Controller interpreterController = new Controller(repository);
        interpreterController.addProgram(currentProgram);

        try {
            interpreterController.allSteps();
        } catch (StackException | IOException | StatementException | ExpressionEvaluationException |
                 InterpreterException exception) {
            System.out.println(exception.getMessage());
        }
    }
}
