package pl.cp.first;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

import org.junit.jupiter.api.Test;


class FileSudokuBoardDaoTest {

    @Test
    public void testWriteRead() {
        SudokuBoard sudokuBoard = new SudokuBoard(new BacktrackingSudokuSolver());
        sudokuBoard.solveGame();
        FileSudokuBoardDao fileSudokuBoardDao = new FileSudokuBoardDao("sudokuboard");
        fileSudokuBoardDao.write(sudokuBoard);
        assertEquals(fileSudokuBoardDao.read(), sudokuBoard);
        
    }

    @Test
    public void testReadException() {
        FileSudokuBoardDao fileSudokuBoardDao = new FileSudokuBoardDao("null");
        Throwable exception = assertThrows(RuntimeException.class, fileSudokuBoardDao::read);
        assertEquals("java.io.FileNotFoundException: null (Nie można odnaleźć określonego pliku)",
                exception.getMessage());
    }

    @Test
    public void testWriteException() {
        SudokuBoard sudokuBoard = new SudokuBoard(new BacktrackingSudokuSolver());
        sudokuBoard.solveGame();
        FileSudokuBoardDao fileSudokuBoardDao = new FileSudokuBoardDao("");
        Throwable exception = assertThrows(RuntimeException.class,
                () -> fileSudokuBoardDao.write(sudokuBoard));
        assertEquals("java.io.FileNotFoundException:  "
                        + "(System nie może odnaleźć określonej ścieżki)",
                exception.getMessage());
    }
}