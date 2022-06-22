package pl.cp.first;

import static org.junit.jupiter.api.Assertions.assertTrue;

import java.util.Arrays;
import org.junit.jupiter.api.Test;

public class SudokuRowTest {

    private SudokuRow fill() {
        return new SudokuRow(Arrays.asList(
                new SudokuField(1),
                new SudokuField(2),
                new SudokuField(3),
                new SudokuField(4),
                new SudokuField(5),
                new SudokuField(6),
                new SudokuField(7),
                new SudokuField(8),
                new SudokuField(9)));
    }

    @Test
    public void cloneTest() throws CloneNotSupportedException {
        SudokuRow sudokuRow = fill();
        SudokuRow sudokuRow2 = (SudokuRow) sudokuRow.clone();
        assertTrue(sudokuRow.equals(sudokuRow2)
                && sudokuRow2.equals(sudokuRow));
    }
}
