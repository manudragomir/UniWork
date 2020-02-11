package utils;

import javafx.scene.control.Alert;

public class Alerta {
    public static void show(String message, String title) {
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.getDialogPane().getStylesheets().add("ErrorPane.css");

        alert.getDialogPane().getStylesheets().add("SaveButton.css");
        alert.setTitle(title);
        alert.setHeaderText(null);
        alert.setContentText(message);
        alert.getDialogPane().setPrefSize(600,200);
        alert.show();
    }
}
