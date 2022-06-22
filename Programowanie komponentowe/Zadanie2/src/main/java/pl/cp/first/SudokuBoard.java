package pl.cp.first;

public class SudokuBoard {

    private final int[][] board;
    private final SudokuSolver sudokuSolver;

    public static void main(final String[] args) {
        SudokuBoard sudokuBoard1 = new SudokuBoard(new BacktrackingSudokuSolver());
        sudokuBoard1.solveGame();
        sudokuBoard1.printBoard();

        if (sudokuBoard1.isBoardCorrect()) {
            System.out.print("Układ liczb na planszy jest prawidłowy");
        } else {
            System.out.print("Układ liczb na planszy jest nieprawidłowy");
        }
    }

    public SudokuBoard(SudokuSolver sudokuSolver) {
        this.board = new int[9][9];
        this.sudokuSolver = sudokuSolver;
    }

    public int getGrid(int x, int y) {
        return board[x][y];
    }

    public void setGrid(int x, int y, int value) {
        if (x >= 0 && x <= 8 && y >= 0 && y <= 8 && value >= 0 && value <= 9) {
            board[x][y] = value;
        }
    }

    public SudokuSolver getSudokuSolver() {
        return sudokuSolver;
    }

    public void printBoard() {
        for (int i = 0; i < 9; i++) {
            if (i % 3 == 0) {
                System.out.print("+-------+-------+-------+\n");
            }

            for (int j = 0; j < 9; j++) {
                if (j % 3 == 0) {
                    System.out.print("| ");
                }
                System.out.print(getGrid(i, j) + " ");
            }
            System.out.print("|");
            System.out.println();
        }
        System.out.print("+-------+-------+-------+\n");
    }


    public boolean isBoardFull() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (getGrid(i, j) == 0) {
                    return false;
                }
            }
        }
        return true;
    }

    public boolean isBoardCorrect() {
        int temp;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                temp = getGrid(i, j);
                setGrid(i, j, 0);
                if (isAllGood(i, j, temp)) {
                    setGrid(i, j, temp);
                } else {
                    return false;
                }
            }
        }
        return true;
    }

    public boolean isXGood(int x, int value) {
        for (int i = 0;i < 9; i++) {
            if (getGrid(x,i) == value) {
                return false;
            }
        }
        return true;
    }

    public boolean isYGood(int y, int value) {
        for (int i = 0;i < 9; i++) {
            if (getGrid(i,y) == value) {
                return false;
            }
        }
        return true;
    }

    public boolean isBoxGood(int x, int y, int value) {
        int x1 = x / 3 * 3;
        int y1 = y / 3 * 3;
        for (int i = 0;i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (value == getGrid(x1 + i, y1 + j)) {
                    return false;
                }
            }
        }
        return true;
    }

    public boolean isAllGood(int x, int y, int value) {
        return (isXGood(x,value) && isYGood(y,value) && isBoxGood(x,y,value));
    }

    public void solveGame() {
        sudokuSolver.solve(this);
    }
}


