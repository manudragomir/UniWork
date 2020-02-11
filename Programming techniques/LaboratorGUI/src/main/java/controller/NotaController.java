package controller;

import com.itextpdf.text.*;
import com.itextpdf.text.pdf.*;
import domain.*;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.*;
import javafx.stage.Modality;
import javafx.stage.Stage;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.data.category.DefaultCategoryDataset;
import org.jfree.data.general.DefaultPieDataset;
import services.service.ServiceNota;
import services.service.ServiceStudent;
import services.service.ServiceTema;
import utils.Alerta;
import utils.EmailSender;
import utils.ObserverPattern.Observer;
import utils.PieChartCreator;

import java.awt.*;
import java.awt.geom.Rectangle2D;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class NotaController implements Observer {
    ObservableList<Tema> modelTema = FXCollections.observableArrayList();
    ObservableList<NotaDTO> modelNota = FXCollections.observableArrayList();

    private ServiceNota serviceNota;
    private ServiceTema serviceTema;
    private boolean ok = true;
    private String nume = "";

    @FXML
    TableView<NotaDTO> tblNote;
    @FXML
    TableColumn<NotaDTO, String> tblNStudent;
    @FXML
    TableColumn<NotaDTO, String> tblNGrupa;
    @FXML
    TableColumn<NotaDTO, String> tblNTema;
    @FXML
    TableColumn<NotaDTO, Double> tblNNota;
    @FXML
    TextField txtId;

    @FXML
    TextField txtStudent;

    @FXML
    ComboBox comboTema;
    @FXML
    ComboBox idComboTema;
    @FXML
    ComboBox idComboGrupa;


    @FXML
    DatePicker dataAdaugareNota;

    @FXML
    CheckBox checkIntarziere;

    @FXML
    Label textIntarziere;

    @FXML
    TextArea textFeedback;

    @FXML
    Button buttonGo;

    @FXML
    ComboBox idSelectGrupa;
    @FXML
    ComboBox<Student> idSelectStudent;
    @FXML
    TextField textNotaAcordata;
    @FXML
    Label idMedie;

    @FXML
    public void initialize() {
        tblNStudent.setCellValueFactory(new PropertyValueFactory<>("numeStudent"));
        tblNTema.setCellValueFactory(new PropertyValueFactory<>("descriereTema"));
        tblNGrupa.setCellValueFactory(new PropertyValueFactory<>("grupa"));
        tblNNota.setCellValueFactory(new PropertyValueFactory<>("valueNota"));

        checkIntarziere.selectedProperty().addListener(((observable, oldValue, newValue) -> {
            if(checkIntarziere.isSelected()){
                textFeedback.setText("GOOD JOB");
                textIntarziere.setText("Nu i se va scadea!");
            }
            else{
                anotherHomeworkSelected();;
            }
        }));

        checkIntarziere.setVisible(false);
        textIntarziere.setVisible(false);

        tblNote.setItems(modelNota);

        textFeedback.setText("OK!");


        idComboGrupa.getItems().addAll(
            "all",
                "221", "222",
                "223", "224",
                "225", "226",
                "227"
                );

        idComboGrupa.getSelectionModel().select(0);


        idSelectGrupa.getItems().addAll(
                "221", "222",
                "223", "224",
                "225", "226",
                "227");

    }

    public void updateListTema(List<Tema> list) {
        int contor = 0;
        for (int i = 0; i < list.size(); i++) {
            if(list.get(i).getDeadlineWeek() == StructuraAnUniversitar.getCurrentWeek()){
                contor = i;
                break;
            }
        }

        modelTema.setAll(list);
        comboTema.getSelectionModel().select(contor);
    }

    public String getMedie(List<NotaDTO> list) {
        double sum = 0;
        for (NotaDTO nota : list) {
            sum += nota.getValueNota();
        }
        if (list.size() == 0) {
            return "NaN";
        }
        return String.valueOf(Math.floor(sum / list.size() * 100) / 100);
    }

    public void anotherNota(){
        String tema = idComboTema.getSelectionModel().getSelectedItem().toString();
        String grupa = idComboGrupa.getSelectionModel().getSelectedItem().toString();
        List<NotaDTO> list = serviceNota.getAllNote();
        list = list.stream().filter(x ->((x.getDescriereTema().equals(tema) || tema.equals("all"))
                                                                    && (x.getGrupa().equals(grupa) || grupa.equals("all"))
        )).collect(Collectors.toList());
        updateListNota(list);
    }

    public void setNume(String nume){
        this.nume = nume;
    }


    public void updateListNota(List<NotaDTO> list){
        List<NotaDTO> lista = list.stream().filter(x -> {
            {return x.getNumeStudent().equals(nume) || nume.equals("");}
        }).collect(Collectors.toList());
        modelNota.setAll(lista);
        idMedie.setText(getMedie(lista));
    }

    public void setServiceNota(ServiceNota serviceNota) {
        this.serviceNota = serviceNota;
        updateListNota(serviceNota.getAllNote());
        serviceNota.addObserver(this);

        idSelectGrupa.getSelectionModel().selectedItemProperty().addListener( (options, oldValue, newValue) -> {
            idSelectStudent.setItems(FXCollections.observableList(serviceNota.getServiceStudent().getAllStudents()
                    .stream().filter(x -> x.getGrupa().equals(idSelectGrupa.getSelectionModel().getSelectedItem().toString())).collect(Collectors.toList())));
            }
        );

        /*

         */
        idSelectStudent.getSelectionModel().selectedItemProperty().addListener((observable, oldValue, newValue) -> {
            if(newValue != null){
                Long id = idSelectStudent.getSelectionModel().getSelectedItem().getId();
                List<Tema> list = serviceNota.getLipsaNota(id);
                updateListTema(list);
            }
        });
    }


    public void setServiceTema(ServiceTema serviceTema){
        this.serviceTema = serviceTema;
        comboTema.setItems(modelTema);
        dataAdaugareNota.setValue(LocalDate.now());
        updateListTema(serviceTema.getAllTeme());
        comboTema.getSelectionModel().selectedItemProperty().addListener((obs, oldSelection, newSelection) -> {
            anotherHomeworkSelected();
        });
        idComboTema.setItems(FXCollections.observableList(modelTema.stream().map(x -> x.getDescriere()).collect(Collectors.toList())));
        idComboTema.getItems().add("all");
        idComboTema.getSelectionModel().select("all");
        idComboTema.getSelectionModel().selectedItemProperty().addListener((obs, oldSelection, newSelection) -> {
            anotherNota();
        });
        idComboGrupa.getSelectionModel().selectedItemProperty().addListener((obs, oldSelection, newSelection) -> {
            anotherNota();
        });
    }

    private void anotherHomeworkSelected(){
        Tema tema = (Tema)comboTema.getValue();
        if(tema != null) {
            if (serviceNota.maxNota(tema.getId()) > 0) {
                if (serviceNota.maxNota(tema.getId()) <= 2) {
                    textIntarziere.setText("minus " + serviceNota.maxNota(tema.getId()) + " pct!");
                    textFeedback.setText("Intarziat cu " + serviceNota.maxNota(tema.getId()) + " sapt!");
                } else {
                    textIntarziere.setText("Tema nu poate fi predata fara motivare!");
                }
                textIntarziere.setVisible(true);
                checkIntarziere.setVisible(true);

            } else {
                textIntarziere.setVisible(false);
                checkIntarziere.setVisible(false);
                textFeedback.setText("GOOD JOB!");
            }
        }

    }

    public void handleButtonGo(ActionEvent actionEvent){
        String errors = "";
        if(idSelectStudent.getSelectionModel().getSelectedItem() == null){
            errors += "Niciun student selectat!";
        }
        else{
            txtId.setText(idSelectStudent.getSelectionModel().getSelectedItem().getId().toString());
        }
        if(txtId.getText().length() == 0){
            errors += "Niciun student nu a fost selectat!\n";
        }

        Tema tema = (Tema)comboTema.getValue();
        if(serviceNota.inTime(serviceNota.maxNota(tema.getId())) == false && checkIntarziere.isSelected() == false){
            errors += "Tema nu se mai poate preda!\n";
        }

        if(txtId.getText().length() != 0 && !serviceNota.check(Long.parseLong(txtId.getText()),tema.getId())){
            errors += "Exista deja o nota la aceasta tema!\n";
        }

        if(textNotaAcordata.getText().length() == 0){
            errors += "Nu s-a acordat nicio nota!\n";
        }else{
            try{
                double notaValue = Double.parseDouble(textNotaAcordata.getText());
            }
            catch(NumberFormatException nfe){
                errors += "nota nu-i intr-un format valid\n";
            }
        }


        if(errors.length() != 0){
            Alerta.show(errors, "EROARE");
        }
        else{
            Student student = serviceNota.getServiceStudent().searchStudent(Long.parseLong(txtId.getText()));
            String infos = "Student: " + student.getNume() + " " + student.getPrenume() + "\n";
            infos += "Primeste nota: " + textNotaAcordata.getText() + "\n";
            infos += "La tema: " + tema.getDescriere() + "\n";
            infos += "In data de: " + dataAdaugareNota.getValue() + "\n";
            infos += "FEEDBACK: " + textFeedback.getText() + "\n";
            if(textIntarziere.isVisible() && checkIntarziere.isSelected() == false){
                infos += "Penalitate -" + serviceNota.maxNota(tema.getId()) + " punct(e)\n => NOTA FINALA: "
                        + String.valueOf(Integer.parseInt(textNotaAcordata.getText()) - serviceNota.maxNota(tema.getId()));
            }
            if(checkIntarziere.isSelected()){
                infos += "Avand motivare\n";
            }
            createNewWindow(infos);
        }
    }

    public void createNewWindow(String infos){
        VBox root = new VBox(10);
        Button okBtn = new Button("OK");
        okBtn.autosize();
        Button cancelBtn = new Button("Cancel");

        cancelBtn.autosize();
        TextArea textFieldCheck = new TextArea(infos);
        textFieldCheck.autosize();
        textFieldCheck.setEditable(false);
        root.getChildren().addAll(textFieldCheck, okBtn, cancelBtn);


        Scene scene = new Scene(root, 700, 400);
        Stage stage = new Stage();
        stage.setTitle("CHECK INFO");
        scene.getStylesheets().add("BackgroundStudenti.css");
        scene.getStylesheets().add("LeButton.css");
        stage.setScene(scene);
        stage.initModality(Modality.APPLICATION_MODAL);
        stage.show();

        cancelBtn.setOnAction(new EventHandler<ActionEvent>() {
            public void handle(ActionEvent e) {
                stage.close();
            }
        });

        okBtn.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                Tema tema = (Tema) comboTema.getValue();
                Student student = serviceNota.getServiceStudent().searchStudent(Long.parseLong(txtId.getText()));
                Alert alert = new Alert(Alert.AlertType.INFORMATION);
                alert.setTitle("info");
                Nota nota = serviceNota.adaugaNota(student.getId(), tema.getId(),
                            Double.parseDouble(textNotaAcordata.getText()), java.sql.Date.valueOf(dataAdaugareNota.getValue()),
                            0, textFeedback.getText(), student.getCadruDidacticIndrumatorLab());

                if(nota == null) {
                    Alerta.show("Nota adaugata cu succes. Yay! \n" +
                            "Mail-ul catre student e in curs de trimitere chiar acum...!", "Succes");
                    sendEmail(student.getEmail(), infos, "Ai primit o nota, boss!");
                }
                else{
                    Alerta.show("Hopa! Se pare ca studentul are deja o nota la aceasta tema...", "Eroare");
                }

                stage.close();
            }
        });
    }

    private void sendEmail(String email, String infos, String s) {
        Thread t1 = new Thread(()->{
            EmailSender.send(email, infos, "Ti-am dat o nota, boss!");
        });
        t1.start();
    }

    @Override
    public void update() {
        updateListTema(serviceTema.getAllTeme());
        updateListNota(serviceNota.getAllNote());
    }

    public void handleBtnFilter1(){
        //createNewStudentsWindow(serviceNota.filterAverageGrade(), Format.formatCuMedie,
          //      "StudentiMedie");
    }

    public void handleBtnFilter2(){
        Tema tema = serviceNota.filterMostDifficultHW();

        final VBox root = new VBox();
        Label textLabel = new Label(tema.toString());
        root.getChildren().addAll(textLabel);
        root.setStyle("-fx-padding: 10;" +
                "-fx-border-style: solid inside;" +
                "-fx-border-width: 2;" +
                "-fx-border-insets: 5;" +
                "-fx-border-radius: 5;" +
                "-fx-border-color: blue;");
        Scene scene = new Scene(root, 350, 100);
        Stage stage = new Stage();
        stage.setScene(scene);
        stage.setTitle("Tema cea mai grea");
        stage.show();
    }

    public void handleBtnFilter3(){
       // createNewStudentsWindow(serviceNota.filterAcceptedStudents(), Format.formatCuMedie, "StudentiAdmisi");
    }

    public void handleBtnFilter4(){
        createNewStudentsWindow(serviceNota.filterPunctualStudents(), Format.formatFaraMedie, "StudentiPunctuali");
    }

    public void createNewStudentsWindow(List<Student> list, Format format, String nume){
        //stylesheets + list
        final VBox root = new VBox();
        ListView<Student> studentListView = new ListView<>();
        if(format == Format.formatCuMedie) {
            studentListView.setCellFactory((ListView<Student> student) -> new SomethingWith());
        }
        else{
            studentListView.setCellFactory((ListView<Student> student) -> new SomethingWithout());
        }
        studentListView.getItems().setAll(list);
        root.getChildren().add(studentListView);
        Scene scene = new Scene(root, 800, 500);

        scene.getStylesheets().add("Background.css");
        Stage stage = new Stage();
        stage.setScene(scene);
        stage.setTitle("STUDENTII CAUTATI!");
        stage.show();
    }

    /*public void insertIntoPdf(List<Student> studentsList, String name, int height, int width) throws FileNotFoundException, DocumentException {
        Document document = new Document();
        PdfWriter writer = PdfWriter.getInstance(document, new FileOutputStream(name + ".pdf"));

        document.open();

        PdfPTable table = new PdfPTable(2);
        Stream.of("NUME + PRENUME", "NOTA")
                .forEach(columnTitle -> {
                    PdfPCell header = new PdfPCell();
                    header.setBackgroundColor(BaseColor.CYAN);
                    header.setBorderWidth(2);
                    header.setPhrase(new Phrase(columnTitle));
                    table.addCell(header);
                });

        for (Student student:
             studentsList) {
            table.addCell(student.getNume() + " " + student.getPrenume());
            table.addCell(String.valueOf(student.getMedie()));
        }
        document.add(table);

        document.newPage();
        PdfContentByte contentByte = writer.getDirectContent();
        PdfTemplate template = contentByte.createTemplate(width, height);
        Graphics2D graphics2d = template.createGraphics(width, height,
                new DefaultFontMapper());
        Rectangle2D rectangle2d = new Rectangle2D.Double(0, 0, width, height);

        JFreeChart chart = PieChartCreator.generateBarChart(studentsList);
        chart.draw(graphics2d, rectangle2d);

        graphics2d.dispose();
        contentByte.addTemplate(template, 0, 0);

        document.close();
    }*/

    static class SomethingWith extends ListCell<Student> {
        @Override
        public void updateItem(Student item, boolean empty) {
            super.updateItem(item, empty);
            String value = null;
            if (item != null) {
               value = item.getNume() + " " + item.getPrenume() + " cu media " + item.getMedie();
            }
            this.setText(value);
            setGraphic(null);
        }
    }

    static class SomethingWithout extends ListCell<Student> {
        @Override
        public void updateItem(Student item, boolean empty) {
            super.updateItem(item, empty);
            String value = null;
            if (item != null) {
                value = item.getNume() + " " + item.getPrenume();
            }
            this.setText(value);
            setGraphic(null);
        }
    }
}

enum Format{
    formatCuMedie, formatFaraMedie
}