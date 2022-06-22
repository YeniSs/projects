package pl.cp.first.exception;

import java.io.IOException;

public class NoFileException extends IOException {
    public NoFileException(Throwable cause) {
        super(cause);
    }
}
