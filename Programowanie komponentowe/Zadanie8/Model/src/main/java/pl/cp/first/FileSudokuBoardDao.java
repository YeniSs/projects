package pl.cp.first;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;

public class FileSudokuBoardDao implements Dao<SudokuBoard> {

    private final String fileName;

    public FileSudokuBoardDao(String fileName) {
        this.fileName = fileName;
    }

    @Override
    public SudokuBoard read() {
        SudokuBoard sudokuBoard = new SudokuBoard(null);
        String line;

        try (BufferedReader fileReader = new BufferedReader(new FileReader(fileName))) {
            for (int i = 0;i < 9; i++) {
                line = fileReader.readLine();
                String[] pieces = line.split(",");
                for (int j = 0;j < 9; j++) {
                    sudokuBoard.set(i,j,Integer.parseInt(pieces[j]));
                }
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        return sudokuBoard;
    }

    @Override
    public void write(SudokuBoard sudokuBoard) {
        try (PrintWriter printWriter = new PrintWriter(new File(fileName))) {
            for (int i = 0;i < 9; i++) {
                for (int j = 0;j < 9; j++) {
                    printWriter.print(sudokuBoard.get(i,j));
                    if (j < 8) {
                        printWriter.print(",");
                    } else {
                        printWriter.println();
                    }
                }
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public void close() throws Exception {

    }

}
