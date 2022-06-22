package pl.cp.first;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;

import static org.junit.jupiter.api.Assertions.*;

public class SudokuBoardTest {
    private final SudokuBoard board = new SudokuBoard();

    @Test
    void fillBoard() {
        this.board.fillBoard();
        var boards = new ArrayList<String>();
        for (var i = 0; i < 10; i++) {
            this.board.fillBoard();
            for (var board: boards) {
                assertNotEquals(board, this.board.toString());
            }
            boards.add(this.board.toString());
        }
    }

    @Test
    void isCorrect(){
        this.board.fillBoard();
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                assertTrue(this.board.isAccept(row, col, this.board.getValue(row, col)));
            }
        }
    }
}
