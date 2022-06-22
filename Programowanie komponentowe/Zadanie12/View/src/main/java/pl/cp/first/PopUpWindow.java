package pl.cp.first;

import javafx.scene.control.ChoiceDialog;
import javafx.scene.control.TextInputDialog;

import java.util.List;
import java.util.Optional;

public class PopUpWindow {

    public String textInputDialog() {
        var dialog = new TextInputDialog();
        dialog.setTitle("Save to DB");
        dialog.setHeaderText("Saving board to DB");
        dialog.setContentText("Enter board name:");
        Optional<String> result = dialog.showAndWait();
        return result.orElse("");
    }

    public String choiceDialog(List<String> boardsList) {
        var dialog = new ChoiceDialog<String>("choose",boardsList);
        dialog.setTitle("Load from DB");
        dialog.setHeaderText("Loading board from DB");
        dialog.setContentText("Choose saved board:");
        Optional<String> result = dialog.showAndWait();
        return result.orElse("");
    }
}