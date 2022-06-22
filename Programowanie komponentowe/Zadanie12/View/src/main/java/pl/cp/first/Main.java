package pl.cp.first;

import javafx.application.Application;
import javafx.stage.Stage;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import pl.cp.first.exception.NoFileException;

import java.io.IOException;

public class Main extends Application {

    private static final Logger log = LoggerFactory.getLogger(Main.class);

    public static void main(String[] args) {
        log.info("App started!");
        launch(args);
    }

    @Override
    public void start(Stage stage) throws NoFileException {
        try {
            FxmlStageSetup.buildStage(stage, "/window.fxml");
        } catch (IOException e) {
            log.warn("Stage building failed!");
            throw new NoFileException(e);
        }
    }
}