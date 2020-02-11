package controller;

import domain.LoginData;
import domain.Tema;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;
import org.jfree.data.json.JSONUtils;
import repository.database.RepoNotaDB;
import repository.database.RepoStudentDB;
import repository.database.RepoTemaDB;
import services.config.ApplicationContext;
import services.service.ServiceAnUniv;
import services.service.ServiceNota;
import services.service.ServiceStudent;
import services.service.ServiceTema;
import utils.Alerta;
import utils.FileFeedbackSaver;
import utils.Privilegii;
import validators.ValidatorNota;
import validators.ValidatorStudent;
import validators.ValidatorTema;

import java.io.IOException;
import java.security.NoSuchAlgorithmException;
import java.sql.SQLException;
import java.util.List;
import java.util.stream.Collectors;


public class LoginController {
    private ServiceNota serviceNota;
    private Stage primaryStage;
    @FXML
    TextField username;
    @FXML
    PasswordField password;

    @FXML
    public void initialize() throws SQLException {
        designApp();
    }

    public void designApp() throws SQLException {
        String file1 = ApplicationContext.getPROPERTIES().getProperty("data.firstTerm");
        String file2 = ApplicationContext.getPROPERTIES().getProperty("data.secondTerm");
        ServiceAnUniv serviceAnUniv = new ServiceAnUniv(file1, file2);
        serviceAnUniv.setDate();

        RepoStudentDB repoStudentDB = new RepoStudentDB(new ValidatorStudent());
        RepoTemaDB repoTemaDB = new RepoTemaDB(new ValidatorTema());
        RepoNotaDB repoNotaDB = new RepoNotaDB(new ValidatorNota());
        FileFeedbackSaver fileFeedbackSaver = new FileFeedbackSaver();
        ServiceStudent serviceStudent = new ServiceStudent(repoStudentDB);
        ServiceTema serviceTema = new ServiceTema(repoTemaDB);

        serviceNota = new ServiceNota(serviceStudent, serviceTema, repoNotaDB, fileFeedbackSaver);

    }

    private AnchorPane LoadStudenti() throws IOException {
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("/view/studentView.fxml"));
        AnchorPane root = loader.load();
        StudentController studentController = loader.getController();
        studentController.setService(serviceNota.getServiceStudent());
        studentController.setServiceNota(serviceNota);
        root.getStylesheets().add("BackgroundStudenti.css");
        return root;
    }

    private AnchorPane LoadTeme() throws IOException {
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("/view/temaView.fxml"));
        AnchorPane root = loader.load();
        TemaController temaController = loader.getController();
        temaController.setService(serviceNota.getServiceTema());
        temaController.setServiceNota(serviceNota);
        root.getStylesheets().add("BackgroundStudenti.css");
        return root;
    }

    private AnchorPane LoadNote(String nume) throws IOException{
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("/view/notaView.fxml"));
        AnchorPane root = loader.load();
        NotaController notaController = loader.getController();
        notaController.setNume(nume);
        notaController.setServiceNota(serviceNota);
        notaController.setServiceTema(serviceNota.getServiceTema());
        root.getStylesheets().add("BackgroundStudenti.css");
        return root;
    }

    private AnchorPane LoadWelcome() throws IOException{
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("/view/welcomeView.fxml"));
        AnchorPane root = loader.load();
        WelcomeController welcomeController = loader.getController();
        welcomeController.setPrimaryStage(primaryStage);
        return root;
    }

    private AnchorPane LoadRapoarte() throws IOException {
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("/view/rapoarteView.fxml"));
        AnchorPane root = loader.load();
        RapoarteController rapoarteController = loader.getController();
        rapoarteController.setServiceNota(serviceNota);
        return root;
    }

    public void handleSignIn(ActionEvent event) throws IOException, NoSuchAlgorithmException {
        LoginData loginData = new LoginData();
        String user = username.getText();
        String pass = password.getText();
        Privilegii value = loginData.checkData(user, pass);

        if(Privilegii.EXTERN == value){
            Alerta.show("user sau parola incorecte!", "UPSI");
        }
        else{
            Stage stageCurrent = (Stage)((Node) event.getSource()).getScene().getWindow();
            parentStage(stageCurrent);
            stageCurrent.hide();
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("/view/principalView.fxml"));
            TabPane root = loader.load();
            PrincipalController principalController = loader.getController();
            List<Tab> list = root.getTabs();
            for (Tab tab: list){
                if(tab.getId().equals("idWelcome")){
                    tab.setContent(LoadWelcome());
                }
                if(tab.getId().equals("idTabStudenti")){
                    if(value == Privilegii.ADMIN){
                        tab.setContent(LoadStudenti());
                    }
                    else{
                        tab.setDisable(true);
                    }
                }
                else if(tab.getId().equals("idTabTeme")){
                    if(value != Privilegii.ADMIN) {
                        AnchorPane node = LoadTeme();
                        List<Node> lista = node.getChildren().stream()
                                .filter(x -> x.getId().equals("idDown")).collect(Collectors.toList());

                        if(Privilegii.STUD == value){
                            lista.get(0).setVisible(false);
                        }

                        tab.setContent(node);

                    }
                    else{
                        tab.setDisable(true);
                    }
                }
                else if(tab.getId().equals("idTabNote")){
                    if(value != Privilegii.ADMIN){

                        AnchorPane node = new AnchorPane();
                        if(Privilegii.STUD == value){
                            node = LoadNote("Dragomir Manuel");
                            ((SplitPane)node.getChildren().get(0)).getItems().get(0).setVisible(false);
                        }
                        else{
                            node = LoadNote("");
                        }

                        tab.setContent(node);
                    }
                    else{
                        tab.setDisable(true);
                    }
                }
            }


            if(value == Privilegii.PROF){
                Tab newTab = new Tab("Rapoarte");
                newTab.setContent(LoadRapoarte());
                root.getTabs().add(newTab);
            }

            Stage stage = new Stage();
            Scene scene = new Scene(root, 1000, 730);
            stage.setScene(scene);
            stage.setTitle("Meniu");
            stage.show();
        }
    }

    public void parentStage(Stage primaryStage) {
        this.primaryStage = primaryStage;
    }
}
