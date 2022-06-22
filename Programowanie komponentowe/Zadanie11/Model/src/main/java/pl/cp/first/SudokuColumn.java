package pl.cp.first;

import java.util.ArrayList;
import java.util.List;

public class SudokuColumn extends SudokuVerify {
    public SudokuColumn(List<SudokuField> values) {
        this.setSudokuVerify(values);
    }

    @Override
    protected Object clone() throws CloneNotSupportedException {
        List<SudokuField> fields = new ArrayList<>(getSudokuVerify());
        return new SudokuColumn(fields);
    }
}