package pl.cp.first;

import java.io.IOException;
import javafx.fxml.FXML;
import javafx.scene.control.ComboBox;

public class StackPaneController {
    private static String level;

    public static String getLevel() {
        return level;
    }

    @FXML
    private ComboBox<?> comboBoxDifficulty;

    @FXML
    public void startGameButtonAction() throws IOException {
        if (!comboBoxDifficulty.getSelectionModel().isEmpty()) {
            level = comboBoxDifficulty.getSelectionModel().getSelectedItem().toString();
        } else {
            level = "Latwy";
        }
        FxmlStageSetup.buildStage("/sudokuBoard.fxml");
    }
}
