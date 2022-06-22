package pl.cp.first;

import static org.junit.jupiter.api.Assertions.assertSame;

import org.junit.jupiter.api.Test;


class SudokuBoardDaoFactoryTest {

    @Test
    void testGetFileDao() {
        Dao<SudokuBoard> test = SudokuBoardDaoFactory.getFileDao("sudokuboard");
        assertSame(test.getClass(), FileSudokuBoardDao.class);
    }
}