package controller;

import domain.StructuraAnUniversitar;
import domain.Student;
import domain.Tema;
import javafx.beans.property.ReadOnlyObjectWrapper;
import javafx.collections.FXCollections;
import javafx.collections.ListChangeListener;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.geometry.Insets;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.image.Image;
import javafx.scene.layout.*;
import javafx.scene.paint.Color;
import javafx.util.Callback;

import services.service.ServiceNota;
import services.service.ServiceStudent;
import services.service.ServiceTema;
import utils.Alerta;
import utils.EmailSender;
import utils.ObserverPattern.Observer;
import validators.ValidationException;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.locks.ReentrantLock;
import java.util.stream.Collectors;

public class TemaController implements Observer {
    private ServiceTema serviceTema;
    private ServiceNota serviceNota;
    ObservableList<Tema> modelTema = FXCollections.observableArrayList();

    @FXML
    TableColumn<Tema, Long> tblId;
    @FXML
    TableColumn<Tema, Integer> tblStartWeek;
    @FXML
    TableColumn<Tema, Integer> tblDeadlineWeek;
    @FXML
    TableColumn<Tema, String> tblDescriere;
    @FXML
    TableView<Tema> tblTeme;
    @FXML
    TextField txtId;
    @FXML
    Label txtStartWeek;
    @FXML
    TextField txtDeadlineWeek;
    @FXML
    TextArea txtDescriere;

    @FXML
    public void initialize() {
        tblId.setCellValueFactory(new PropertyValueFactory<>("id"));
        tblStartWeek.setCellValueFactory(new PropertyValueFactory<>("StartWeek"));
        tblDeadlineWeek.setCellValueFactory(new PropertyValueFactory<>("DeadlineWeek"));
        tblDescriere.setCellValueFactory(new PropertyValueFactory<>("descriere"));
        tblTeme.setItems(modelTema);
        txtStartWeek.setText(String.valueOf(StructuraAnUniversitar.getCurrentWeek()));
    }

    public void updateList(List<Tema> list){
        modelTema.setAll(list);
    }

    public void setServiceNota(ServiceNota serviceNota){
        this.serviceNota = serviceNota;
    }

    public void setService(ServiceTema serviceTema) {
        this.serviceTema = serviceTema;
        updateList(serviceTema.getAllTeme());
        rowSelected();
        serviceTema.addObserver(this);
    }

    public void rowSelected(){
        tblTeme.getSelectionModel().selectedItemProperty().addListener((obs, oldSelection, newSelection) -> {
            if(newSelection == null) {
                txtId.setText("");
                txtDeadlineWeek.setText("");
                txtStartWeek.setText("");
                txtDescriere.setText("");
            }
            else {
                txtDescriere.setText(newSelection.getDescriere());
                txtDeadlineWeek.setText(String.valueOf(newSelection.getDeadlineWeek()));
                txtStartWeek.setText(String.valueOf(newSelection.getStartWeek()));
                txtId.setText(newSelection.getId().toString());
            }
        });
    }

    @FXML
    ProgressIndicator idProgress;

    public void sendEmailsToEveryone(){
        List<Student> studentList = serviceNota.getServiceStudent().getAllStudents();
        ExecutorService executor = Executors.newFixedThreadPool(6);

        ReentrantLock mutex = new ReentrantLock();
        idProgress.setVisible(true);
        idProgress.setProgress(0);
        double epsilon = (double)1 / studentList.size();
        System.out.println(epsilon);

        studentList.forEach(t->{
            Runnable runnable = ()-> {
                EmailSender.send(t.getEmail(), "Au fost realizate unele update-uri in ceea ce priveste temele" +
                        "", "Update Teme!");
                try {
                    mutex.lock();
                    idProgress.setProgress(idProgress.getProgress() + epsilon);
                } finally {
                    mutex.unlock();
                }

            };

            executor.submit(runnable);
        });


        executor.shutdown();
    }

    public void handleAdauga(){
        Tema tema;
        try{
            tema = new Tema(Integer.parseInt(txtDeadlineWeek.getText()), txtDescriere.getText());
            tema.setId(Long.parseLong(txtId.getText()));
            tema = serviceTema.addTema(tema);
            Alerta.show("Efectuat cu succes!", "Succes");
            sendEmailsToEveryone();
        }
        catch(ValidationException vae){
            Alerta.show(vae.getMessage(), "MARE EROARE");
        }
        catch(Exception ve) {
            Alerta.show("Campuri incorecte", "Eroare");
        }
    }

    public void handleSterge(){
        Tema tema;
        try{
            serviceNota.stergeNoteleDupaTeme(Long.parseLong(txtId.getText()));
            tema = serviceTema.removeTema(Long.parseLong(txtId.getText()));
            if(tema != null) {
                Alerta.show("Sters cu succes!", "Succes");
            }
            else{
                Alerta.show("Id-ul nu exista", "Eroare");
            }
        }
        catch(NumberFormatException e) {
            Alerta.show("Id-ul no se puede", "Error");
        }
    }

    public void handleUpdate(){
        Tema tema;
        try{

            Integer start = Integer.parseInt(txtStartWeek.getText());
            tema = new Tema(Integer.parseInt(txtDeadlineWeek.getText()), txtDescriere.getText());
            tema.setId(Long.parseLong(txtId.getText()));
            tema.setStartWeek(start);
            tema = serviceTema.updateTema(tema);
            if(tema == null){
                Alerta.show("Efectuat cu succes! Se trimit mail-uri", "Succes");
            }
            else{
                Alerta.show("ID-ul este inexistent", "Eroare");
            }
            sendEmailsToEveryone();
        }
        catch(ValidationException vae){
            Alerta.show(vae.getMessage(), "Insucces!");
        }
        catch(Exception ve) {
            Alerta.show("Campuri incorecte", "Eroare");
        }
    }

    @Override
    public void update() {
        updateList(serviceTema.getAllTeme());
    }
}
