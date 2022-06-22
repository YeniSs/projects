package pl.cp.first;

import java.util.ArrayList;
import java.util.List;

public class SudokuBox extends SudokuVerify {
    public SudokuBox(List<SudokuField> values) {
        this.setSudokuVerify(values);
    }

    @Override
    protected Object clone() throws CloneNotSupportedException {
        List<SudokuField> fields = new ArrayList<>(getSudokuVerify());
        return new SudokuBox(fields);
    }
}