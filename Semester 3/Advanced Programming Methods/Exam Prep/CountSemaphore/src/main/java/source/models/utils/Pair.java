package source.models.utils;


import source.exceptions.InterpreterException;
import source.models.PrgState;

public class Pair {
    public final PrgState program;
    public final InterpreterException thrownException;

    public Pair(PrgState program, InterpreterException thrownException)
    {
        this.program = program;
        this.thrownException = thrownException;
    }
}
