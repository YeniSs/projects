package pl.cp.first;

import javafx.application.Application;
import javafx.stage.Stage;

public class Main extends Application {

    @Override
    public void start(Stage stage) throws Exception {
        FxmlStageSetup.setUpStage(stage, "/main.fxml", "Sudoku");
    }

    public static void main(String[] args) {
        launch(args);
    }
}
