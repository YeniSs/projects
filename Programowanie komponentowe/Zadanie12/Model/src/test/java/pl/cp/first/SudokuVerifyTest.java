package pl.cp.first;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.util.ArrayList;
import java.util.List;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

public class SudokuVerifyTest {
    List<SudokuField> testSudokuFields;
    SudokuVerify testSudokuVerify;

    @BeforeEach
    public void sudokuVerify() {
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

    @Test
    void testToString() {
        SudokuVerify testSudokuVerify1 = new SudokuVerify();
        assertFalse(testSudokuVerify1.toString().isEmpty());
    }

    @Test
    void testEqualsSameObjects() {
        SudokuVerify testSudokuVerify1 = testSudokuVerify;
        assertEquals(testSudokuVerify, testSudokuVerify1);
    }

    @Test
    void testEqualsObjectIsNull() {
        SudokuVerify testSudokuVerify1 = null;
        assertNotEquals(testSudokuVerify, testSudokuVerify1);
    }

    @Test
    void testEqualsBuilder() {
        SudokuVerify testSudokuVerify1 = new SudokuVerify();
        SudokuVerify testSudokuVerify2 = new SudokuVerify();
        assertEquals(testSudokuVerify1, testSudokuVerify2);
    }

    @Test
    void testHashCode() {
        SudokuVerify testSudokuVerify1 = new SudokuVerify();
        SudokuVerify testSudokuVerify2 = new SudokuVerify();
        assertEquals(testSudokuVerify2.hashCode(),testSudokuVerify1.hashCode());
        testSudokuVerify1.getSudokuVerify().set(0, new SudokuField(5));
        assertNotEquals(testSudokuVerify2.hashCode(),testSudokuVerify1.hashCode());
    }
}