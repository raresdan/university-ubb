package exceptions;

public class ExpressionEvaluationException extends Exception {
    public ExpressionEvaluationException(String errorMessage) {
        super(errorMessage);
    }
}
