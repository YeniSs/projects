package pl.cp.first;

import java.io.Serializable;
import java.util.Random;

public class BacktrackingSudokuSolver implements SudokuSolver, Serializable {
    Random generator = new Random();

    @Override
    public void solve(SudokuBoard board) {
        int randInt;
        int value;
        randInt = generator.nextInt(9) + 1;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board.get(i, j) == 0) {
                    for (int z = 0; z < 9; z++) {
                        value = (randInt + z) % 9 + 1;
                        if (board.isAllGood(i, j, value)) {
                            board.set(i, j, value);
                            solve(board);
                            if (board.isBoardFull()) {
                                return;
                            }
                        }
                    }
                    board.set(i, j, 0);
                    return;
                }
            }
        }
    }

}

