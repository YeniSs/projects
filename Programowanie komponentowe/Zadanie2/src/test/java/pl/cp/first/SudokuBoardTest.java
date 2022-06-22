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
    public void setUp() {
        testSudokuBoard = new SudokuBoard(new BacktrackingSudokuSolver());
    }

    @Test
    public void testSetGetGrid() {
        testSudokuBoard.setGrid(row, column, value);
        Assertions.assertEquals(testSudokuBoard.getGrid(1, 2), 3);
    }

    @Test
    public void testSetGridOversize() {
        int value = 10;
        testSudokuBoard.setGrid(row,column,value);
        Assertions.assertEquals(testSudokuBoard.getGrid(row,column), 0);
    }

    @Test
    public void testIsBoardFull() {
        for (int i = 0; i < 9; i++){
            for (int j = 0; j < 9; j++) {
                testSudokuBoard.setGrid(i,j,i+1);
            }
        }
        Assertions.assertTrue(testSudokuBoard.isBoardFull());
    }

    @Test
    public void testIsBoardNotFull() {
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++) {
                testSudokuBoard.setGrid(i,j,i+1);
            }
        }
        Assertions.assertFalse(testSudokuBoard.isBoardFull());
    }

    @Test
    public void testIsXGood() {
        for(int i=0; i<8; i++) {
            testSudokuBoard.setGrid(0,i,i);
        }
        Assertions.assertTrue(testSudokuBoard.isXGood(0,9));
    }

    @Test
    public void testIsXNotGood() {
        for(int i=0; i<9; i++) {
            testSudokuBoard.setGrid(0,i,i);
        }
        Assertions.assertFalse(testSudokuBoard.isXGood(0,8));
    }

    @Test
    public void testIsYGood() {
        for(int i=0; i<8; i++){
            testSudokuBoard.setGrid(i,0,i);
        }
        Assertions.assertTrue(testSudokuBoard.isYGood(0,9));
    }

    @Test
    public void testIsYNotGood() {
        for(int i=0; i<9; i++){
            testSudokuBoard.setGrid(i,0,i);
        }
        Assertions.assertFalse(testSudokuBoard.isYGood(0,8));
    }

    @Test
    public void testIsBoxGood() {
        int tmp = 0;
        for(int i=0; i<2; i++){
            for(int j=0; j < 2; j++){
                testSudokuBoard.setGrid(i,j,++tmp);
            }
        }
        Assertions.assertTrue(testSudokuBoard.isBoxGood(2,2,5));
    }

    @Test
    public void testIsBoxNotGood() {
        int tmp = 0;
        for(int i=0; i<2; i++){
            for(int j=0; j < 2; j++){
                testSudokuBoard.setGrid(i,j,++tmp);
            }
        }
        Assertions.assertFalse(testSudokuBoard.isBoxGood(2,2,2));
    }

    @Test
    public void testIsAllGood() {
        int tmp = 0;
        for(int i=0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                testSudokuBoard.setGrid(i, j, ++tmp);
            }
        }
        testSudokuBoard.setGrid(2,2,0);
        Assertions.assertTrue(testSudokuBoard.isAllGood(2,2,9));
    }

    @Test
    public void testIsNotAllGood() {
        int tmp = 0;
        for(int i=0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                testSudokuBoard.setGrid(i, j, ++tmp);
            }
        }
        testSudokuBoard.setGrid(2,2,0);
        Assertions.assertFalse(testSudokuBoard.isAllGood(2,2,8));
    }

    @Test
    public void testSolveGame() {
        testSudokuBoard.solveGame();
        Assertions.assertTrue(testSudokuBoard.isBoardCorrect());
    }
}
