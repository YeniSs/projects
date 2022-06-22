package pl.cp.first;

import java.util.ArrayList;
import java.util.List;

public class SudokuRow extends SudokuVerify {
    public SudokuRow(List<SudokuField> values) {
        this.setSudokuVerify(values);
    }

    @Override
    protected Object clone() throws CloneNotSupportedException {
        List<SudokuField> fields = new ArrayList<>(getSudokuVerify());
        return new SudokuRow(fields);
    }
}