package pl.cp.first;

import java.util.Arrays;
import java.util.List;
import org.apache.commons.lang3.builder.EqualsBuilder;
import org.apache.commons.lang3.builder.HashCodeBuilder;
import org.apache.commons.lang3.builder.ToStringBuilder;

public class SudokuBoard {

    private final List<List<SudokuField>> board = Arrays.asList(new List[9]);
    private final SudokuSolver sudokuSolver;

    public SudokuBoard(SudokuSolver sudokuSolver) {
        for (int i = 0; i < 9; i++) {
            board.set(i, Arrays.asList(new SudokuField[9]));
            for (int j = 0; j < 9; j++) {
                board.get(i).set(j, new SudokuField());
            }
        }
        this.sudokuSolver = sudokuSolver;
    }

    public int get(int x, int y) {
        return board.get(x).get(y).getFieldValue();
    }

    public void set(int x, int y, int value) {
        if (x >= 0 && x <= 8 && y >= 0 && y <= 8 && value >= 0 && value <= 9) {
            board.get(x).get(y).setFieldValue(value);
        }
    }

    public SudokuSolver getSudokuSolver() {
        return sudokuSolver;
    }

    public String printBoard() {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < 9; i++) {
            if (i % 3 == 0) {
                sb.append("+-------+-------+-------+\n");
            }

            for (int j = 0; j < 9; j++) {
                if (j % 3 == 0) {
                    sb.append("| ");
                }
                sb.append(get(i, j)).append(" ");
            }
            sb.append("|\n");
        }
        sb.append("+-------+-------+-------+\n");
        return sb.toString();
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

    public SudokuRow getRow(int y) {
        SudokuRow row = new SudokuRow();
        List<SudokuField> values = Arrays.asList(new SudokuField[9]);
        for (int i = 0; i < 9; i++) {
            values.set(i, new SudokuField(get(i, y)));
        }
        row.setSudokuVerify(values);
        return row;
    }

    public SudokuColumn getColumn(int x) {
        SudokuColumn column = new SudokuColumn();
        List<SudokuField> values = Arrays.asList(new SudokuField[9]);
        for (int i = 0; i < 9; i++) {
            values.set(i, new SudokuField(get(x, i)));
        }
        column.setSudokuVerify(values);
        return column;
    }

    public SudokuBox getBox(int x, int y) {
        List<SudokuField> values = Arrays.asList(new SudokuField[9]);
        x = x / 3 * 3;
        y = y / 3 * 3;
        int k = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++, k++) {
                values.set(k, new SudokuField(get(x + i, y + j)));
            }
        }
        SudokuBox box = new SudokuBox();
        box.setSudokuVerify(values);
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
        return new EqualsBuilder().append(board, that.board)
                .append(sudokuSolver, that.sudokuSolver).isEquals();
    }

    @Override
    public int hashCode() {
        return new HashCodeBuilder(17, 37).append(board).append(sudokuSolver).toHashCode();
    }

    @Override
    public String toString() {
        return new ToStringBuilder(this)
                .append("board", board)
                .append("sudokuSolver", sudokuSolver)
                .toString();
    }
}


