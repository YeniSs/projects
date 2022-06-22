package pl.cp.first;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

import org.junit.jupiter.api.Test;
import pl.cp.first.exception.FileIoException;

class FileSudokuBoardDaoTest {

    @Test
    public void testReadException() {
        FileSudokuBoardDao fileSudokuBoardDao = (FileSudokuBoardDao) SudokuBoardDaoFactory
                .getFileDao("null");
        assertThrows(FileIoException.class, fileSudokuBoardDao::read);
    }

    @Test
    public void testWriteException() {
        FileSudokuBoardDao fileSudokuBoardDao = (FileSudokuBoardDao) SudokuBoardDaoFactory
                .getFileDao("");

        SudokuBoard sudokuBoard = new SudokuBoard(new BacktrackingSudokuSolver());
        sudokuBoard.solveGame();
        assertThrows(FileIoException.class,
                () -> fileSudokuBoardDao.write(sudokuBoard));
    }

    @Test
    public void testWriteRead() throws FileIoException {
        FileSudokuBoardDao fileSudokuBoardDao = (FileSudokuBoardDao) SudokuBoardDaoFactory
                .getFileDao("sudokuBoard");

        SudokuBoard sudokuBoard = new SudokuBoard();
        sudokuBoard.solveGame();

        fileSudokuBoardDao.write(sudokuBoard);
        assertEquals(fileSudokuBoardDao.read(), sudokuBoard);
    }
}