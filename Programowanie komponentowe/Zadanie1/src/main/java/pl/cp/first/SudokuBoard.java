package pl.cp.first;

import java.util.Arrays;
import java.util.Random;

public class SudokuBoard {
    private int[][] board;
    private final int siZE = 9;

    public void fillBoard() {
        this.board = new int[this.siZE][this.siZE];

        var random = new Random();

        for (int num = 0; num < this.siZE; num++) {
            this.board[num][random.nextInt(this.siZE)] = num + 1;
        }

        this.resolveBoard();
    }

    public boolean isAccept(final int row, final int col, final int num) {
        return this.isColAccept(row, col, num) && this.isRowAccept(row, col, num)
                && this.isSquareAccept(row, col, num);
    }

    public int getValue(final int row, final int col) {
        return this.board[row][col];
    }

    @Override
    public String toString() {
        var strBuild = new StringBuilder();

        for (int row = 0; row < this.siZE; row++) {
            if (row % 3 == 0 && row % 9 != 0) {
                strBuild.append("\n------+-------+------\n");
            }
            for (int col = 0; col < this.siZE; col++) {
                if (col % 3 == 0 && col % 9 != 0) {
                    strBuild.append("| ");
                }
                strBuild.append(this.board[row][col]);
                strBuild.append(' ');
            }
            strBuild.append('\n');
        }
        return strBuild.toString();
    }

    private boolean resolveBoard() {
        for (int row = 0; row < this.siZE; row++) {
            for (int col = 0; col < this.siZE; col++) {
                if (this.board[row][col] == 0) {
                    for (int num = 1; num < 10; num++) {
                        if (this.isAccept(row, col, num)) {
                            this.board[row][col] = num;
                            if (this.resolveBoard()) {
                                return true;
                            } else {
                                this.board[row][col] = 0;
                            }
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }

    private boolean isRowAccept(final int row, final int _col, final int num) {
        for (int col = 0; col < this.siZE; col++) {
            if (this.board[row][col] == num && col != _col) {
                return false;
            }
        }
        return true;
    }

    private boolean isColAccept(final int _row, final int col, final int num) {
        for (int row = 0; row < this.siZE; row++) {
            if (this.board[row][col] == num && row != _row) {
                return false;
            }
        }
        return true;
    }

    private boolean isSquareAccept(final int _row, final int _col, final int num) {
        var elRow = _row / 3 * 3;
        var elCol = _col / 3 * 3;
        for (int row = elRow; row < elRow + 3; row++) {
            for (int col = elCol; col < elCol + 3; col++) {
                if (this.board[row][col] == num && row != _row && col != _col) {
                    return false;
                }
            }
        }
        return true;
    }
}


