package pl.cp.first;

import javafx.fxml.FXML;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import javafx.scene.text.Font;

public class SudokuBoardController {

    @FXML
    private GridPane sudokuBoardGrid;
    private final BacktrackingSudokuSolver backtrackingSudokuSolver =
            new BacktrackingSudokuSolver();
    private final SudokuBoard sudokuBoard = new SudokuBoard(backtrackingSudokuSolver);
    private final Difficulty difficulty = new Difficulty();


    @FXML
    private void initialize() {
        sudokuBoard.solveGame();
        difficulty.chooseLevel(sudokuBoard, StackPaneController.getLevel());
        fillGrid();
    }

    private void fillGrid() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                TextField textField = new TextField();
                textField.setMinSize(50, 50);
                textField.setFont(Font.font("Poor Richard",32));
                if (sudokuBoard.get(i, j) != 0) {
                    textField.setDisable(true);
                    textField.setText(String.valueOf(sudokuBoard.get(i, j)));
                }
                sudokuBoardGrid.add(textField, i, j);
            }
        }
    }
}
