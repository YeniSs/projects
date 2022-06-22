package pl.cp.first;

import java.util.Arrays;
import java.util.List;

public class SudokuVerify {
    private final List<SudokuField> list = Arrays.asList(new SudokuField[9]);

    public SudokuVerify() {
        for (int i = 0;i < 9;i++) {
            list.set(i, new SudokuField());
        }
    }

    public List<SudokuField> getSudokuVerify() {
        return list;
    }

    public void setSudokuVerify(List<SudokuField> lista) {
        for (int i = 0;i < 9; i++) {
            list.set(i, lista.get(i));
        }
    }

    public boolean verify() {
        for (int i = 0;i < 9;i++) {
            if (list.get(i).getFieldValue() < 1 || list.get(i).getFieldValue() > 9) {
                return false;
            }
        }
        for (int i = 0;i < 9;i++) {
            for (int j = 0; j < 9; j++) {
                if (list.get(i).getFieldValue() == list.get(j).getFieldValue() && i != j) {
                    return false;
                }
            }
        }
        return true;
    }
}

