package pl.cp.first;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertSame;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;




public class SudokuBoardTest {


    SudokuBoard testSudokuBoard;

    @BeforeEach
    public void sudokuSet() {
        testSudokuBoard = new SudokuBoard(new BacktrackingSudokuSolver());
    }

    @Test
    public void testSetGood() {
        int row = 1;
        int column = 2;
        int value = 3;

        testSudokuBoard.set(row, column, value);
        assertEquals(testSudokuBoard.get(row, column), value);
    }

    @Test
    public void testWrongGet() {
        int row = 1;
        int column = 2;
        int value = 9;
        testSudokuBoard.set(row, column, value);
        assertEquals(testSudokuBoard.get(row, column), 9);
    }

    @Test
    public void testSet() {
        int row = 1;
        int column = 2;
        int value = 3;

        testSudokuBoard.set(row, column, value);
        assertEquals(testSudokuBoard.get(row, column), 3);
    }

    @Test
    public void testSetNegative() {
        testSudokuBoard.set(-1, 0, 1);
        testSudokuBoard.set(10, 0, 1);
        testSudokuBoard.set(0, -1, 1);
        testSudokuBoard.set(0, 10, 1);
        testSudokuBoard.set(0, 0, -1);
        testSudokuBoard.set(0, 0, 10);
        assertEquals(testSudokuBoard.get(0, 0), 0);
    }

    @Test
    public void testGetSudokuSolver() {
        var testBacktrackingSudokuSolver = new BacktrackingSudokuSolver();
        var testSudokuBoard = new SudokuBoard(testBacktrackingSudokuSolver);
        assertSame(testSudokuBoard.getSudokuSolver(), testBacktrackingSudokuSolver);
    }


    @Test
    public void testIsBoardGood() {
        testSudokuBoard.solveGame();
        assertTrue(testSudokuBoard.checkBoard());
    }

    @Test
    public void testIsBoardNotGood() {
        testSudokuBoard.solveGame();
        testSudokuBoard.set(0, 0, (testSudokuBoard.get(0, 0) + 1) % 9 + 1);
        Assertions.assertFalse(testSudokuBoard.checkBoard());
    }

    @Test
    public void testIsBoardFull() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                testSudokuBoard.set(i, j, i + 1);
            }
        }
        assertTrue(testSudokuBoard.isBoardFull());
    }

    @Test
    public void testIsBoardNotFull() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                testSudokuBoard.set(i, j, i + 1);
            }
        }
        Assertions.assertFalse(testSudokuBoard.isBoardFull());
    }

    @Test
    public void testIsRowGood() {
        for (int i = 0; i < 8; i++) {
            testSudokuBoard.set(0, i, i);
        }
        assertTrue(testSudokuBoard.isRowGood(0, 9));
    }

    @Test
    public void testIsRowNotGood() {
        for (int i = 0; i < 9; i++) {
            testSudokuBoard.set(0, i, i);
        }
        Assertions.assertFalse(testSudokuBoard.isRowGood(0, 8));
    }

    @Test
    public void testIsColumnGood() {
        for (int i = 0; i < 8; i++) {
            testSudokuBoard.set(i, 0, i);
        }
        assertTrue(testSudokuBoard.isColumnGood(0, 9));
    }

    @Test
    public void testIsColumnNotGood() {
        for (int i = 0; i < 9; i++) {
            testSudokuBoard.set(i, 0, i);
        }
        Assertions.assertFalse(testSudokuBoard.isColumnGood(0, 8));
    }

    @Test
    public void testIsBoxGood() {
        int tmp = 0;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                testSudokuBoard.set(i, j, ++tmp);
            }
        }
        assertTrue(testSudokuBoard.isBoxGood(2, 2, 5));
    }

    @Test
    public void testIsBoxNotGood() {
        int tmp = 0;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                testSudokuBoard.set(i, j, ++tmp);
            }
        }
        Assertions.assertFalse(testSudokuBoard.isBoxGood(2, 2, 2));
    }

    @Test
    public void testIsAllGood() {
        int tmp = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                testSudokuBoard.set(i, j, ++tmp);
            }
        }
        testSudokuBoard.set(2, 2, 0);
        assertTrue(testSudokuBoard.isAllGood(2, 2, 9));
    }

    @Test
    public void testIsNotAllGood() {
        int tmp = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                testSudokuBoard.set(i, j, ++tmp);
            }
        }
        testSudokuBoard.set(2, 2, 0);
        Assertions.assertFalse(testSudokuBoard.isAllGood(2, 2, 8));
    }

    @Test
    public void testSolveGame() {
        testSudokuBoard.solveGame();
        assertTrue(testSudokuBoard.isBoardCorrect());
    }

    @Test
    public void testIsBoxGoodPositive() {
        int k = 0;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                testSudokuBoard.set(i, j, ++k);
            }
        }
        assertTrue(testSudokuBoard.isBoxGood(2, 2, 5));
    }

    @Test
    public void testIsBoxGoodNegative() {
        int k = 0;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                testSudokuBoard.set(i, j, ++k);
            }
        }
        assertFalse(testSudokuBoard.isBoxGood(2, 2, 2));
    }

    @Test
    public void testCheckBoardPositive() {
        testSudokuBoard.solveGame();
        assertTrue(testSudokuBoard.checkBoard());
    }

    @Test
    public void testCheckBoardNegative() {
        assertFalse(testSudokuBoard.checkBoard());
    }

    @Test
    void testEqualsSameObjects() {
        SudokuBoard testSudokuBoard1 = testSudokuBoard;
        assertTrue(testSudokuBoard.equals(testSudokuBoard1));
    }

    @Test
    void testEqualsObjectIsNull() {
        SudokuBoard testSudokuBoard1 = null;
        assertFalse(testSudokuBoard.equals(testSudokuBoard1));
    }

    @Test
    void testEqualsObjectClassNotMatch() {
        SudokuField testSudokuField = new SudokuField(1);
        assertFalse(testSudokuBoard.equals(testSudokuField));
    }

    @Test
    void testEqualsObjectsAreEquals() {
        SudokuBoard testSudokuBoard1 = new SudokuBoard(new BacktrackingSudokuSolver());
        testSudokuBoard.solveGame();
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                testSudokuBoard1.set(i,j,testSudokuBoard.get(i,j));
            }
        }
        assertTrue(testSudokuBoard.equals(testSudokuBoard1));
    }

    @Test
    void testHashCode() {
        SudokuBoard testSudokuBoard1 = new SudokuBoard(new BacktrackingSudokuSolver());
        testSudokuBoard.solveGame();
        assertNotEquals(testSudokuBoard.hashCode(),testSudokuBoard1.hashCode());

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                testSudokuBoard1.set(i,j,testSudokuBoard.get(i,j));
            }
        }
        assertEquals(testSudokuBoard.hashCode(),testSudokuBoard1.hashCode());
    }

    @Test
    public void testToString() {
        assertFalse(testSudokuBoard.toString().isEmpty());
    }

    @Test
    public void cloneTest() throws CloneNotSupportedException {
        BacktrackingSudokuSolver backtrackingSudokuSolver = new BacktrackingSudokuSolver();
        SudokuBoard sudokuBoard = new SudokuBoard(backtrackingSudokuSolver);
        sudokuBoard.solveGame();
        SudokuBoard sudokuBoard2 = (SudokuBoard) sudokuBoard.clone();

        assertTrue(sudokuBoard.equals(sudokuBoard2)
                && sudokuBoard2.equals(sudokuBoard));
    }
}
