package pl.cp.first;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

public class BacktrackingSudokuSolverTest {

    @Test
    public void testSolve() {
        BacktrackingSudokuSolver sudokuSolver = new BacktrackingSudokuSolver();
        SudokuBoard testSudokuBoard = new SudokuBoard(sudokuSolver);
        sudokuSolver.solve(testSudokuBoard);
        Assertions.assertTrue(testSudokuBoard.isBoardCorrect());
    }

    @Test
    public void testDifferentSolves() {
        boolean isBoardTheSame = false;
        for (int i = 0; i < 100; i++) {
            SudokuBoard testSudokuBoard1 = new SudokuBoard(new BacktrackingSudokuSolver());
            SudokuBoard testSudokuBoard2 = new SudokuBoard(new BacktrackingSudokuSolver());
            testSudokuBoard1.getSudokuSolver().solve(testSudokuBoard1);
            testSudokuBoard2.getSudokuSolver().solve(testSudokuBoard2);

            compareBoards:
            for (int j = 0; j < 9; j++) {
                for (int k = 0; k < 9; k++) {
                    if (testSudokuBoard1.get(j, k) != testSudokuBoard2.get(j, k)) {
                        break compareBoards;
                    }
                    if (j == 8 && k == 8) {
                        isBoardTheSame = true;
                    }
                }
            }
        }
        Assertions.assertFalse(isBoardTheSame);
    }
}
