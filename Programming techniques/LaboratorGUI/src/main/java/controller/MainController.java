package controller;

import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;
import javafx.stage.Window;
import repository.database.RepoStudentDB;
import services.service.ServiceNota;
import services.service.ServiceStudent;
import services.service.ServiceTema;
import validators.ValidatorStudent;

import javax.swing.text.html.ImageView;
import javax.xml.ws.Service;
import java.io.IOException;
import java.sql.SQLException;
import java.util.List;

public class MainController {
    private ServiceStudent serviceStudent;
    private ServiceNota serviceNota;
    private ServiceTema serviceTema;

    public void setServiceStudent(ServiceStudent serviceStudent){
        this.serviceStudent = serviceStudent;
    }

    public void setServiceTema(ServiceTema serviceTema){
        this.serviceTema = serviceTema;
    }

    public void setServiceNota(ServiceNota serviceNota){this.serviceNota = serviceNota; }

    public void btnAce(ActionEvent actionEvent) throws IOException {
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("/view/loginView.fxml"));
        AnchorPane root = loader.load();
        LoginController loginController = loader.getController();
        Stage stage = new Stage();
        Scene scene = new Scene(root, 800, 400);

        stage.setScene(scene);
        stage.setTitle("Studenti");
        stage.show();
    }

    public void handleNewStudentStage(ActionEvent actionEvent) throws IOException, SQLException {
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("/view/studentView.fxml"));
        AnchorPane root = loader.load();
        StudentController studentController = loader.getController();


        Stage stage = new Stage();
        studentController.setService(serviceStudent);
        Scene scene = new Scene(root, 1000, 700);
        scene.getStylesheets().add("BackgroundOne.css");
        stage.setScene(scene);
        stage.setTitle("Studenti");
        stage.show();
    }

    public void handleNewNotaStage(ActionEvent actionEvent) throws IOException {
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("/view/notaView.fxml"));
        AnchorPane root = loader.load();
        NotaController notaController = loader.getController();

        notaController.setServiceTema(serviceTema);
        notaController.setServiceNota(serviceNota);

        Stage stage = new Stage();
        stage.setScene(new Scene(root, 1000, 700));
        stage.setTitle("Note");
        stage.show();
    }

    public void handleNewTemaStage(ActionEvent actionEvent) throws IOException {
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("/view/temaView.fxml"));
        AnchorPane root = loader.load();
        TemaController temaController = loader.getController();

        temaController.setService(serviceTema);

        Stage stage = new Stage();
        stage.setScene(new Scene(root, 1000, 700));
        stage.setTitle("Tema");
        stage.show();
    }
}
