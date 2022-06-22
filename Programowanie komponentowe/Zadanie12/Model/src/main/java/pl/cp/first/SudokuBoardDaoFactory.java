package pl.cp.first;

public class SudokuBoardDaoFactory {
    public static Dao<SudokuBoard> getFileDao(String fileName) {
        return new FileSudokuBoardDao(fileName);
    }

    public static Dao<SudokuBoard> getDatabaseDao(String boardName) {
        return new JdbcSudokuBoardDao(boardName);
    }

}

