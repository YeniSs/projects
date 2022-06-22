package pl.cp.first;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class SudokuVerifyTest {
    SudokuField[] testSudokuFields;
    SudokuVerify testSudokuVerify;

    @BeforeEach
    public void sudokuSet() {
        testSudokuFields = new SudokuField[9];
        for (int i = 0;i < 9;i++) {
            testSudokuFields[i] = new SudokuField();
        }
        testSudokuVerify = new SudokuVerify();
        for (int i = 0;i < 9;i++) {
            testSudokuVerify.getSudokuVerify()[i].setFieldValue(i + 1);
        }
    }

    @Test
    public void testGetSudokuVerify() {
        for (int i = 0;i < 9;i++) {
            assertEquals(testSudokuVerify.getSudokuVerify()[i].getFieldValue(), i + 1);
        }
    }

    @Test
    public void testSetSudokuVerify() {
        for (int i = 0;i < 9;i++) {
            testSudokuFields[i].setFieldValue((i + 1) * 10);
        }
        testSudokuVerify.setSudokuVerify(testSudokuFields);
        for (int i = 0;i < 9;i++) {
            assertEquals(testSudokuVerify.getSudokuVerify()[i].getFieldValue(),
                    testSudokuFields[i].getFieldValue());
        }
    }

    @Test
    public void testVerifyNumberOutOfRange() {
        for (int i = 0;i < 9;i++) {
            testSudokuFields[i].setFieldValue((i + 1) * 100);
        }
        testSudokuVerify.setSudokuVerify(testSudokuFields);
        assertFalse(testSudokuVerify.verify());
    }

    @Test
    public void testVerifyNumberRepeats() {
        for (int i = 0;i < 9;i++) {
            testSudokuFields[i].setFieldValue(1);
        }
        testSudokuVerify.setSudokuVerify(testSudokuFields);
        assertFalse(testSudokuVerify.verify());
    }

    @Test
    public void testVerifyPositive() {
        for (int i = 0;i < 9;i++) {
            testSudokuFields[i].setFieldValue(i + 1);
        }
        testSudokuVerify.setSudokuVerify(testSudokuFields);
        assertTrue(testSudokuVerify.verify());
    }
}