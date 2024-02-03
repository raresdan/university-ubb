package exceptions;

public class InterpreterException extends Exception{
    public InterpreterException()
    {
        super();
    }

    public InterpreterException(String errorMessage)
    {
        super(errorMessage);
    }
}
