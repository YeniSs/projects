package pl.cp.first;

import javafx.application.Application;
import javafx.stage.Stage;

import java.util.ResourceBundle;

public class Main extends Application {
    private final ResourceBundle resourceBundle = ResourceBundle.getBundle("lang");

    @Override
    public void start(Stage stage) throws Exception{
        FxmlStageSetup.buildStage(stage, "/main.fxml", resourceBundle.getString("title"), resourceBundle);
    }

    public static void main(String[] args) {
        launch(args);
    }
}
