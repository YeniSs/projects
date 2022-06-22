package pl.cp.first;


import static org.junit.jupiter.api.Assertions.assertTrue;

import java.util.Arrays;
import org.junit.jupiter.api.Test;

public class SudokuBoxTest {

    private SudokuBox fill() {
        return new SudokuBox(Arrays.asList(
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
        SudokuBox sudokuBox = fill();
        SudokuBox sudokuBox2 = (SudokuBox) sudokuBox.clone();
        assertTrue(sudokuBox.equals(sudokuBox2)
                && sudokuBox2.equals(sudokuBox));
    }
}
