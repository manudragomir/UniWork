package controller;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.IOException;

public class WelcomeController {
    private Stage primaryStage;
    @FXML
    public void handleSignOut(ActionEvent event) throws IOException {
        Stage stageCurrent = (Stage)((Node) event.getSource()).getScene().getWindow();
        stageCurrent.hide();
        primaryStage.show();
    }

    public void setPrimaryStage(Stage primaryStage) {
        this.primaryStage = primaryStage;
    }
}
