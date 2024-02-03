package source.view.command;



import source.controller.Controller;
import source.exceptions.ExpressionEvaluationException;
import source.exceptions.InterpreterException;
import source.exceptions.StackException;
import source.exceptions.StatementException;
import source.models.PrgState;
import source.models.statements.IStatement;
import source.models.utils.MyDictionary;
import source.repository.IRepository;
import source.repository.ProgramsRepository;

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
