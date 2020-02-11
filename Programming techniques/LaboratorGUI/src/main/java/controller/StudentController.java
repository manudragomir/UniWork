package controller;

import domain.Student;
import javafx.beans.property.ReadOnlyObjectWrapper;
import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.collections.ListChangeListener;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.geometry.Insets;
import javafx.scene.control.Alert;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.image.Image;
import javafx.scene.layout.*;
import javafx.scene.paint.Color;
import javafx.util.Callback;

import services.service.ServiceNota;
import services.service.ServiceStudent;
import utils.Alerta;
import utils.ObserverPattern.Observer;
import validators.ValidationException;

import java.util.Collections;
import java.util.List;
import java.util.stream.Collectors;

public class StudentController implements Observer {
    private ServiceStudent serviceStudent;
    private ServiceNota serviceNota;
    ObservableList<Student> modelStudent = FXCollections.observableArrayList();

    @FXML
    TableColumn<Student, Long> tblId;

    @FXML
    TableColumn<Student, String> tblNume;

    @FXML
    TableColumn<Student, String> tblPrenume;

    @FXML
    TableColumn<Student, String> tblGrupa;

    @FXML
    TableColumn<Student, String> tblEmail;

    @FXML
    TableColumn<Student, String> tblProf;

    @FXML
    TableView<Student> tblStudenti;
    //----endTableView//

    @FXML
    TextField txtId;

    @FXML
    TextField txtNume;

    @FXML
    TextField txtPrenume;

    @FXML
    TextField txtGrupa;

    @FXML
    TextField txtEmail;

    @FXML
    TextField txtProf;

    @FXML
    TextField searchBox;

    @FXML
    HBox hboxImg;

    @FXML
    public void initialize() {
        tblId.setCellValueFactory(new PropertyValueFactory<>("id"));
        tblNume.setCellValueFactory(new PropertyValueFactory<>("Nume"));
        tblPrenume.setCellValueFactory(new PropertyValueFactory<>("Prenume"));
        tblGrupa.setCellValueFactory(new PropertyValueFactory<>("Grupa"));
        tblEmail.setCellValueFactory(new PropertyValueFactory<>("Email"));
        tblProf.setCellValueFactory(new PropertyValueFactory<>("cadruDidacticIndrumatorLab"));
        tblStudenti.setItems(modelStudent);
        BackgroundImage myBI= new BackgroundImage(new Image("file:salut.jpg",true),
                BackgroundRepeat.REPEAT, BackgroundRepeat.NO_REPEAT, BackgroundPosition.DEFAULT,
                BackgroundSize.DEFAULT);
        hboxImg.setBackground(new Background(myBI));

    }

    public void updateList(List<Student> list){
        modelStudent.setAll(list);
    }

    public void setService(ServiceStudent serviceStudent) {
        this.serviceStudent = serviceStudent;
        updateList(serviceStudent.getAllStudents());
        rowSelected();
        serviceStudent.addObserver(this);
        searchBox.textProperty().addListener((observable, s,t1) -> handleSearch());
    }

    public void setServiceNota(ServiceNota serviceNota){
        this.serviceNota = serviceNota;
    }

    public void handleSearch(){
        String value = searchBox.getText();
        updateList(serviceStudent.getAllStudents().stream()
                .filter(s -> {return (s.getNume().contains(value) || s.getPrenume().contains(value));})
                .collect(Collectors.toList()));
    }

    public void rowSelected(){
        tblStudenti.getSelectionModel().selectedItemProperty().addListener((obs, oldSelection, newSelection) -> {
                if(newSelection == null) {
                    txtNume.setText("");
                    txtPrenume.setText("");
                    txtEmail.setText("");
                    txtGrupa.setText("");
                    txtProf.setText("");
                    txtId.setText("");
                }
                else {
                    txtNume.setText(newSelection.getNume());
                    txtPrenume.setText(newSelection.getPrenume());
                    txtEmail.setText(newSelection.getEmail());
                    txtGrupa.setText(newSelection.getGrupa());
                    txtProf.setText(newSelection.getCadruDidacticIndrumatorLab());
                    txtId.setText(newSelection.getId().toString());
                }
        });
    }

    public void handleAdauga(){
        Student student;
        try{
            student = new Student(txtNume.getText(), txtPrenume.getText(), txtGrupa.getText(), txtEmail.getText(),
                                        txtProf.getText());
            student.setId(Long.parseLong(txtId.getText()));
            student = serviceStudent.addStudent(student);
            if(student == null){
                Alerta.show("Studentul a fost adaugat cu succes!", "Succes");
            }
            else{
                Alerta.show("Studentul nu e de gasit", "Eroare");
            }
        }
        catch(ValidationException ve){
            Alerta.show(ve.getMessage(), "Eroare");
        }
        catch(Exception ve) {
            Alerta.show("Campuri eronate!", "Eroare");
        }
    }

    public void handleSterge(){
        Student student;
        try{
            serviceNota.stergeNoteleDupaStudent(Long.parseLong(txtId.getText()));
            student = serviceStudent.removeStudent(Long.parseLong(txtId.getText()));
            if(student != null){
                Alerta.show("Studentul a fost sters cu succes!", "Succes");
            }
            else{
                Alerta.show("Studentul cu id-ul respectiv nu exista", "Eroare");
            }
        }
        catch(NumberFormatException e) {
            Alerta.show("Id-ul nu este numar intreg", "Error!");
        }
    }

    public void handleUpdate(){
        Student student;
        try{
            student = new Student(txtNume.getText(), txtPrenume.getText(), txtGrupa.getText(), txtEmail.getText(),
                    txtProf.getText());
            student.setId(Long.parseLong(txtId.getText()));
            student = serviceStudent.updateStudent(student);
            if(student == null){
                Alerta.show("Studentul a fost updatat cu succes", "Succes!");
            }
            else{
                Alerta.show("Id inexistent", "Insucces");
            }
        }
        catch(ValidationException ve){
            Alerta.show(ve.getMessage(), "Eroare");
        }
        catch(Exception e) {
            Alerta.show("Date incorecte", "Eroare");
        }
    }

    @Override
    public void update() {
        updateList(serviceStudent.getAllStudents());
    }
}
