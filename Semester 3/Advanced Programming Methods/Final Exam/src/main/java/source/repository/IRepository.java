package source.repository;



import source.exceptions.InterpreterException;
import source.models.PrgState;

import java.io.IOException;
import java.util.List;

public interface IRepository {
    void addProgram(PrgState programToAdd);

    List<PrgState> getAllPrograms();
    void setProgramsList(List<PrgState> newPrograms);

    void logProgramState(PrgState currentProgram) throws InterpreterException;
}
