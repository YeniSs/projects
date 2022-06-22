package pl.cp.first;

public class SudokuVerify {
    private final SudokuField[] set = new SudokuField[9];

    public SudokuVerify() {
        for (int i = 0;i < 9;i++) {
            set[i] = new SudokuField();
        }
    }

    public SudokuField[] getSudokuVerify() {
        return set.clone();
    }

    public void setSudokuVerify(SudokuField[] set) {
        for (int i = 0;i < 9; i++) {
            this.set[i].setFieldValue(set[i].getFieldValue());
        }
    }

    public boolean verify() {
        for (int i = 0;i < 9;i++) {
            if (set[i].getFieldValue() < 1 || set[i].getFieldValue() > 9) {
                return false;
            }
        }
        for (int i = 0;i < 9;i++) {
            for (int j = 0; j < 9; j++) {
                if (set[i].getFieldValue() == set[j].getFieldValue() && i != j) {
                    return false;
                }
            }
        }
        return true;
    }
}
