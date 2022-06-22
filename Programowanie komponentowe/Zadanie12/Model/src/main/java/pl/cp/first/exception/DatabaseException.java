package pl.cp.first.exception;

public class DatabaseException extends DaoException {
    public DatabaseException(Throwable cause) {
        super(cause);
    }
}
