package pl.cp.first;

import pl.cp.first.exception.DaoException;

public interface Dao<T> extends AutoCloseable {
    T read() throws DaoException;

    void write(T object) throws DaoException;
}
