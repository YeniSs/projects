package pl.cp.first;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class SudokuFieldTest {
    SudokuField testSudokuField;

    @BeforeEach
    public void sudokuSet() {
        testSudokuField = new SudokuField();
    }

    @Test
    public void testDefaultValue() {
        assertEquals(testSudokuField.getFieldValue(), 0);
    }

    @Test
    public void testSetGetSudokuField() {
        testSudokuField.setFieldValue(1);
        assertEquals(testSudokuField.getFieldValue(), 1);
    }

}
