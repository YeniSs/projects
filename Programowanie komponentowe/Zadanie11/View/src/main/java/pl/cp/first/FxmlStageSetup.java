package pl.cp.first;

import java.io.IOException;
import java.util.ResourceBundle;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class FxmlStageSetup {

    private static Stage stage;

    public static Stage getStage() {
        return stage;
    }

    private static void setStage(Stage stage) {
        FxmlStageSetup.stage = stage;
    }

    private static Parent loadFxml(String fxml, ResourceBundle resourceBundle) throws IOException {
        return new FXMLLoader(FxmlStageSetup.class.getResource(fxml), resourceBundle).load();
    }

    public static void buildStage(String filePath, ResourceBundle resourceBundle) throws IOException {
        stage.setScene(new Scene(loadFxml(filePath, resourceBundle)));
        stage.sizeToScene();
        stage.show();
    }

    public static void buildStage(String filePath, String title, ResourceBundle resourceBundle) throws IOException {
        stage.setScene(new Scene(loadFxml(filePath, resourceBundle)));
        stage.setTitle(title);
        stage.sizeToScene();
        stage.show();
    }

    public static void buildStage(Stage stage, String filePath, String title, ResourceBundle resourceBundle) throws IOException {
        setStage(stage);
        stage.setScene(new Scene(loadFxml(filePath, resourceBundle)));
        stage.setTitle(title);
        stage.sizeToScene();
        stage.show();
    }

}
