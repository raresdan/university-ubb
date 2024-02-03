package controller;

import exceptions.InterpreterException;
import models.PrgState;

public class Pair {
    final PrgState program;
    final InterpreterException thrownException;

    public Pair(PrgState program, InterpreterException thrownException)
    {
        this.program = program;
        this.thrownException = thrownException;
    }
}
