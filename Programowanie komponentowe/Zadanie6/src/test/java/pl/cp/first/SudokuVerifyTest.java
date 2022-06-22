package pl.cp.first;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

public class SudokuVerifyTest {
    List<SudokuField> testSudokuFields;
    SudokuVerify testSudokuVerify;

    @BeforeEach
    public void sudokuSet() {
        testSudokuFields = new ArrayList<>(9);
        for (int i = 0; i < 9; i++) {
            testSudokuFields.add(new SudokuField());
        }
        testSudokuVerify = new SudokuVerify();
        for (int i = 0; i < 9; i++) {
            testSudokuVerify.getSudokuVerify().get(i).setFieldValue(i + 1);
        }
    }

    @Test
    public void testGetSudokuVerify() {
        for (int i = 0; i < 9; i++) {
            assertEquals(testSudokuVerify.getSudokuVerify().get(i).getFieldValue(), i + 1);
        }
    }

    @Test
    public void testSetSudokuVerify() {
        for (int i = 0; i < 9; i++) {
            testSudokuFields.get(i).setFieldValue((i + 1) * 10);
        }
        testSudokuVerify.setSudokuVerify(testSudokuFields);
        for (int i = 0; i < 9; i++) {
            assertEquals(testSudokuVerify.getSudokuVerify().get(i).getFieldValue(),
                    testSudokuFields.get(i).getFieldValue());
        }
    }

    @Test
    public void testVerifyNumberOutOfRange() {
        for (int i = 0; i < 9; i++) {
            testSudokuFields.get(i).setFieldValue((i + 1) * 100);
        }
        testSudokuVerify.setSudokuVerify(testSudokuFields);
        assertFalse(testSudokuVerify.verify());
    }

    @Test
    public void testVerifyNumberRepeats() {
        for (int i = 0; i < 9; i++) {
            testSudokuFields.get(i).setFieldValue(1);
        }
        testSudokuVerify.setSudokuVerify(testSudokuFields);
        assertFalse(testSudokuVerify.verify());
    }

    @Test
    public void testVerifyPositive() {
        for (int i = 0; i < 9; i++) {
            testSudokuFields.get(i).setFieldValue(i + 1);
        }
        testSudokuVerify.setSudokuVerify(testSudokuFields);
        assertTrue(testSudokuVerify.verify());
    }
}