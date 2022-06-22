package pl.cp.first;

import java.io.Serializable;
import java.util.Arrays;
import java.util.List;
import org.apache.commons.lang3.builder.EqualsBuilder;
import org.apache.commons.lang3.builder.HashCodeBuilder;
import org.apache.commons.lang3.builder.ToStringBuilder;

public class SudokuBoard implements Serializable, Cloneable {
    private final SudokuField[][] board;
    private final SudokuSolver sudokuSolver;

    public SudokuBoard() {
        this.board = new SudokuField[9][9];
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                board[i][j] = new SudokuField();
            }
        }
        this.sudokuSolver = new BacktrackingSudokuSolver();
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

    public int get(int row, int y) {
        if (row >= 0 && row <= 8 && y >= 0 && y <= 8) {
            return board[row][y].getFieldValue();
        } else {
            return -1;
        }
    }

    public void set(int x, int y, int value) {
        if (x >= 0 && x <= 8 && y >= 0 && y <= 8 && value >= 0 && value <= 9) {
            board[x][y].setFieldValue(value);
        }
    }

    public SudokuSolver getSudokuSolver() {
        return sudokuSolver;
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
                }
            }
        }
        return true;
    }

    public boolean isRowGood(int x, int value) {
        for (int i = 0; i < 9; i++) {
            if (get(x, i) == value) {
                return false;
            }
        }
        return true;
    }

    public boolean isColumnGood(int y, int value) {
        for (int i = 0; i < 9; i++) {
            if (get(i, y) == value) {
                return false;
            }
        }
        return true;
    }

    public boolean isBoxGood(int x, int y, int value) {
        int x1 = x / 3 * 3;
        int y1 = y / 3 * 3;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (value == get(x1 + i, y1 + j)) {
                    return false;
                }
            }
        }
        return true;
    }

    public boolean isAllGood(int x, int y, int value) {
        return (isRowGood(x, value) && isColumnGood(y, value) && isBoxGood(x, y, value));
    }

    public void solveGame() {
        sudokuSolver.solve(this);
    }

    public SudokuRow getRow(int column) {
        SudokuRow row = new SudokuRow(Arrays.asList(new SudokuField[9]));
        for (int i = 0;i < 9;i++) {
            row.getSudokuVerify().set(i, new SudokuField(get(i, column)));
        }
        return row;
    }

    public SudokuColumn getColumn(int row) {
        SudokuColumn column = new SudokuColumn(Arrays.asList(new SudokuField[9]));
        for (int i = 0;i < 9;i++) {
            column.getSudokuVerify().set(i, new SudokuField(get(row, i)));
        }
        return column;
    }


    public SudokuBox getBox(int row, int column) {
        SudokuBox box = new SudokuBox(Arrays.asList(new SudokuField[9]));
        row = row / 3 * 3;
        column = column / 3 * 3;
        int k = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++, k++) {
                box.getSudokuVerify().set(k, new SudokuField(get(row + i, column + j)));
            }
        }
        return box;
    }

    public boolean checkBoard() {
        int j = 0;
        for (int i = 0; i < 9; i++, j++) {
            if (!getRow(i).verify() || !getColumn(i).verify() || !getBox(i, j).verify()) {
                return false;
            }
        }
        return true;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) {
            return true;
        }
        if (o == null || getClass() != o.getClass()) {
            return false;
        }
        SudokuBoard that = (SudokuBoard) o;
        return new EqualsBuilder().append(board, that.board).isEquals();
    }

    @Override
    public int hashCode() {
        return new HashCodeBuilder(17, 37).append(board).toHashCode();
    }

    @Override
    public String toString() {
        return new ToStringBuilder(this)
                .append("board", board)
                .append("sudokuSolver", sudokuSolver)
                .toString();
    }

    @Override
    protected Object clone() throws CloneNotSupportedException {
        BacktrackingSudokuSolver backtrackingSudokuSolver = new BacktrackingSudokuSolver();
        SudokuBoard sudokuBoard = new SudokuBoard(backtrackingSudokuSolver);
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                sudokuBoard.set(i, j, get(i, j));
            }
        }
        return sudokuBoard;
    }
    public boolean isFieldEditable(int row, int column) {
        return board[row][column].isEditable();
    }

    public void setFieldEditable(int column, int row) {
        board[column][row].setEditable();
    }
}


