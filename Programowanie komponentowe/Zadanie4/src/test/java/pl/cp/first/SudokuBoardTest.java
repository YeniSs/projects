package pl.cp.first;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;


public class SudokuBoardTest {
    public static int row = 1;
    public static int column = 2;
    public static int value = 3;

    SudokuBoard testSudokuBoard;

    @BeforeEach
    public void sudokuSet() {
        testSudokuBoard = new SudokuBoard(new BacktrackingSudokuSolver());
    }

    @Test
    public void testIsBoardGood() {
        testSudokuBoard.solveGame();
        Assertions.assertTrue(testSudokuBoard.checkBoard());
    }

    @Test
    public void testIsBoardNotGood() {
        testSudokuBoard.solveGame();
        testSudokuBoard.set(0, 0, (testSudokuBoard.get(0, 0) + 1) % 9 + 1);
        Assertions.assertFalse(testSudokuBoard.checkBoard());
    }

    @Test
    public void testSetGet() {
        testSudokuBoard.set(row, column, value);
        Assertions.assertEquals(testSudokuBoard.get(1, 2), 3);
    }

    @Test
    public void testSetOversize() {
        int value = 10;
        testSudokuBoard.set(row,column,value);
        Assertions.assertEquals(testSudokuBoard.get(row,column), 0);
    }

    @Test
    public void testIsBoardFull() {
        for (int i = 0; i < 9; i++){
            for (int j = 0; j < 9; j++) {
                testSudokuBoard.set(i,j,i+1);
            }
        }
        Assertions.assertTrue(testSudokuBoard.isBoardFull());
    }

    @Test
    public void testIsBoardNotFull() {
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++) {
                testSudokuBoard.set(i,j,i+1);
            }
        }
        Assertions.assertFalse(testSudokuBoard.isBoardFull());
    }

    @Test
    public void testIsRowGood() {
        for(int i=0; i<8; i++) {
            testSudokuBoard.set(0,i,i);
        }
        Assertions.assertTrue(testSudokuBoard.isRowGood(0,9));
    }

    @Test
    public void testIsRowNotGood() {
        for(int i=0; i<9; i++) {
            testSudokuBoard.set(0,i,i);
        }
        Assertions.assertFalse(testSudokuBoard.isRowGood(0,8));
    }

    @Test
    public void testIsColumnGood() {
        for(int i=0; i<8; i++){
            testSudokuBoard.set(i,0,i);
        }
        Assertions.assertTrue(testSudokuBoard.isColumnGood(0,9));
    }

    @Test
    public void testIsColumnNotGood() {
        for(int i=0; i<9; i++){
            testSudokuBoard.set(i,0,i);
        }
        Assertions.assertFalse(testSudokuBoard.isColumnGood(0,8));
    }

    @Test
    public void testIsBoxGood() {
        int tmp = 0;
        for(int i=0; i<2; i++){
            for(int j=0; j < 2; j++){
                testSudokuBoard.set(i,j,++tmp);
            }
        }
        Assertions.assertTrue(testSudokuBoard.isBoxGood(2,2,5));
    }

    @Test
    public void testIsBoxNotGood() {
        int tmp = 0;
        for(int i=0; i<2; i++){
            for(int j=0; j < 2; j++){
                testSudokuBoard.set(i,j,++tmp);
            }
        }
        Assertions.assertFalse(testSudokuBoard.isBoxGood(2,2,2));
    }

    @Test
    public void testIsAllGood() {
        int tmp = 0;
        for(int i=0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                testSudokuBoard.set(i, j, ++tmp);
            }
        }
        testSudokuBoard.set(2,2,0);
        Assertions.assertTrue(testSudokuBoard.isAllGood(2,2,9));
    }

    @Test
    public void testIsNotAllGood() {
        int tmp = 0;
        for(int i=0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                testSudokuBoard.set(i, j, ++tmp);
            }
        }
        testSudokuBoard.set(2,2,0);
        Assertions.assertFalse(testSudokuBoard.isAllGood(2,2,8));
    }

    @Test
    public void testSolveGame() {
        testSudokuBoard.solveGame();
        Assertions.assertTrue(testSudokuBoard.isBoardCorrect());
    }

}
