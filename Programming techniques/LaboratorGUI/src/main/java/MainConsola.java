import controller.LoginController;
import controller.MainController;
import controller.NotaController;
import controller.StudentController;
import domain.LoginData;
import domain.StructuraAnUniversitar;
import domain.StructuraSemestru;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.SplitPane;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;
import repository.database.RepoNotaDB;
import repository.database.RepoStudentDB;
import repository.database.RepoTemaDB;
import services.config.ApplicationContext;
import services.service.ServiceAnUniv;
import services.service.ServiceNota;
import services.service.ServiceStudent;
import services.service.ServiceTema;
import utils.EmailSender;
import utils.FileFeedbackSaver;
import validators.ValidatorNota;
import validators.ValidatorStudent;
import validators.ValidatorTema;

import java.io.IOException;
import java.sql.SQLException;

public class MainConsola extends Application {

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) throws Exception {
/*
        FXMLLoader mainLoader = new FXMLLoader();
        mainLoader.setLocation(getClass().getResource("/view/mainView.fxml"));
        AnchorPane mainRoot = mainLoader.load();
        MainController mainController = mainLoader.getController();
        mainController.setServiceTema(serviceTema);
        mainController.setServiceStudent(serviceStudent);
        mainController.setServiceNota(serviceNota);*/

        FXMLLoader mainLoader = new FXMLLoader();
        mainLoader.setLocation(getClass().getResource("/view/loginView.fxml"));
        AnchorPane mainRoot = mainLoader.load();

        primaryStage.setScene(new Scene(mainRoot, 800, 400));
        primaryStage.setTitle("WELCOME TO MAP");
        primaryStage.show();
    }
}
