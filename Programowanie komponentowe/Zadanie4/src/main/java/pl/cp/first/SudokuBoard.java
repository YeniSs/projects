package pl.cp.first;

public class SudokuBoard {

    private final SudokuField[][] board;
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
        this.board = new SudokuField[9][9];
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                board[i][j] = new SudokuField();
            }
        }
        this.sudokuSolver = sudokuSolver;
    }

    public int get(int x, int y) {
        return board[x][y].getFieldValue();
    }

    public void set(int x, int y, int value) {
        if (x >= 0 && x <= 8 && y >= 0 && y <= 8 && value >= 0 && value <= 9) {
            board[x][y].setFieldValue(value);
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
                System.out.print(get(i, j) + " ");
            }
            System.out.print("|");
            System.out.println();
        }
        System.out.print("+-------+-------+-------+\n");
    }


    public boolean isBoardFull() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (get(i, j) == 0) {
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
                temp = get(i, j);
                set(i, j, 0);
                if (isAllGood(i, j, temp)) {
                    set(i, j, temp);
                } else {
                    return false;
                }
            }
        }
        return true;
    }

    public boolean isRowGood(int x, int value) {
        for (int i = 0;i < 9; i++) {
            if (get(x,i) == value) {
                return false;
            }
        }
        return true;
    }

    public boolean isColumnGood(int y, int value) {
        for (int i = 0;i < 9; i++) {
            if (get(i,y) == value) {
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
                if (value == get(x1 + i, y1 + j)) {
                    return false;
                }
            }
        }
        return true;
    }

    public boolean isAllGood(int x, int y, int value) {
        return (isRowGood(x,value) && isColumnGood(y,value) && isBoxGood(x,y,value));
    }

    public void solveGame() {
        sudokuSolver.solve(this);
    }

    public SudokuRow getRow(int y) {
        SudokuRow row = new SudokuRow();
        SudokuField[] values = new SudokuField[9];
        for (int i = 0;i < 9;i++) {
            values[i] = board[i][y];
        }
        row.setSudokuVerify(values);
        return row;
    }

    public SudokuColumn getColumn(int x) {
        SudokuColumn column = new SudokuColumn();
        SudokuField[] values = new SudokuField[9];
        System.arraycopy(board[x], 0, values, 0, 9);
        column.setSudokuVerify(values);
        return column;
    }

    public SudokuBox getBox(int x, int y) {
        SudokuField[] values = new SudokuField[9];
        x = x / 3 * 3;
        y = y / 3 * 3;
        int k = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++, k++) {
                values[k] = board[x + i][y + j];
            }
        }
        SudokuBox box = new SudokuBox();
        box.setSudokuVerify(values);
        return box;
    }

    public boolean checkBoard() {
        int j = 0;
        for (int i = 0;i < 9;i++, j++) {
            if (!getRow(i).verify() || !getColumn(i).verify() || !getBox(i,j).verify()) {
                return false;
            }
        }
        return true;
    }
}


