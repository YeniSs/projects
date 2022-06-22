package pl.cp.first;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;


public class SudokuFieldTest {
    SudokuField testSudokuField;

    @BeforeEach
    public void sudokuVerify() {
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

    @Test
    void testToString() {
        SudokuField testSudokuField1 = new SudokuField(1);
        int value = testSudokuField1.getFieldValue();
        assertEquals(testSudokuField1.toString(), "pl.cp.first.SudokuField{value=" + value + "}");
    }


    @Test
    void testEqualsSameObjects() {
        SudokuField testSudokuField1 = testSudokuField;
        assertTrue(testSudokuField.equals(testSudokuField1));
    }

    @Test
    void testEqualsObjectIsNull() {
        SudokuField testSudokuField1 = null;
        assertFalse(testSudokuField.equals(testSudokuField1));
    }

    @Test
    void testEqualsObjectClassNotMatch() {
        SudokuVerify testSudokuVerify = new SudokuVerify();
        assertFalse(testSudokuField.equals(testSudokuVerify));
    }

    @Test
    void testGetClass() {
        SudokuField testSudokuField1 = new SudokuField();
        assertEquals(testSudokuField.getClass(), testSudokuField1.getClass());
    }

    @Test
    public void compareToTest() {
        SudokuField sudokuField = new SudokuField(5);
        SudokuField sudokuField2 = new SudokuField(5);

        assertEquals(sudokuField.compareTo(sudokuField2), 0);

        sudokuField.setFieldValue(8);
        assertTrue(sudokuField.compareTo(sudokuField2) >= 1);

        sudokuField.setFieldValue(2);
        assertTrue(sudokuField.compareTo(sudokuField2) <= -1);
    }

    @Test
    public void cloneTest() throws CloneNotSupportedException {
        SudokuField sudokuField = new SudokuField(2);
        SudokuField sudokuField2 = (SudokuField) sudokuField.clone();

        assertTrue(sudokuField.equals(sudokuField2)
                && sudokuField2.equals(sudokuField));
    }
}
