package controller;

import com.itextpdf.text.*;
import com.itextpdf.text.Font;
import com.itextpdf.text.pdf.*;
import domain.DTOStudentMedie;
import domain.DTOTemaMedie;
import domain.Student;
import domain.Tema;
import javafx.beans.property.ReadOnlyObjectWrapper;
import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.scene.Node;
import javafx.scene.chart.BarChart;
import javafx.scene.chart.CategoryAxis;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.scene.control.*;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.AnchorPane;
import javafx.stage.DirectoryChooser;
import javafx.stage.FileChooser;
import javafx.stage.Stage;
import javafx.stage.Window;
import javafx.util.Callback;
import org.jfree.chart.JFreeChart;
import services.service.ServiceNota;
import utils.PieChartCreator;

import javax.swing.*;
import java.awt.*;
import java.awt.geom.Rectangle2D;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class RapoarteController {
    private ServiceNota serviceNota;

    @FXML
    RadioButton noteLaborator;
    @FXML
    RadioButton temeGrele;
    @FXML
    RadioButton studentiExamen;
    @FXML
    RadioButton studentiTeme;
    @FXML
    TableView tblResults;
    @FXML
    BarChart chartArea;
    @FXML
    CategoryAxis xAxa;
    @FXML
    NumberAxis yAxa;

    TableColumn numeStudent;
    TableColumn medieStudent;

    @FXML
    public void initialize(){
        tblResults.setVisible(false);
    }

    void populateTabel(List<DTOStudentMedie> list){
        tblResults.setVisible(true);
        tblResults.getItems().clear();
        tblResults.getColumns().clear();

        numeStudent = new TableColumn<DTOStudentMedie, String>("Nume student");
        medieStudent = new TableColumn<DTOStudentMedie, Double>("Media");
        numeStudent.setPrefWidth(2 * tblResults.getWidth() / 3);
        medieStudent.setPrefWidth(tblResults.getWidth() / 3);
        tblResults.getColumns().addAll(numeStudent, medieStudent);

        numeStudent.setCellValueFactory(new Callback<TableColumn.CellDataFeatures<DTOStudentMedie, Double>, ObservableValue<Double>>() {
            public ObservableValue<Double> call(TableColumn.CellDataFeatures<DTOStudentMedie, Double> p) {
                return new ReadOnlyObjectWrapper(serviceNota.getServiceStudent().searchStudent(p.getValue().getIdStudent()).getNume()
                + " " + serviceNota.getServiceStudent().searchStudent(p.getValue().getIdStudent()).getPrenume());
            }
        });
        medieStudent.setCellValueFactory(new Callback<TableColumn.CellDataFeatures<DTOStudentMedie, Double>, ObservableValue<Double>>() {
            public ObservableValue<Double> call(TableColumn.CellDataFeatures<DTOStudentMedie, Double> p) {
                return new ReadOnlyObjectWrapper(Math.floor(p.getValue().getMedie() * 100) / 100);
            }
        });
        medieStudent.setCellValueFactory(new PropertyValueFactory<>("medie"));
        tblResults.setItems(FXCollections.observableList(list));
    }

    void updateChart(List<DTOStudentMedie> list){
        chartArea.setVisible(true);
        chartArea.getData().clear();
        chartArea.layout();
        int[] a = new int[11];
        for (int i = 1; i <= 10; i++) {
            a[i] = 0;
        }
        for (DTOStudentMedie dtoStudentMedie:
                list) {
            a[(int)dtoStudentMedie.getMedie()]++;
        }

        XYChart.Series chart = new XYChart.Series();

        for (int i = 2; i <= 10; i++) {
            chart.getData().add(new XYChart.Data<>("[" + String.valueOf(i-1) +";" + String.valueOf(i)+"]", a[i]));
        }
        chart.getData().add(new XYChart.Data<>("Exact 10", a[10]));
        chartArea.setTitle("Mediile obtinute");

        chartArea.getXAxis().setLabel("Intervalul de notare");
        chartArea.getXAxis().setAnimated(false);

        chartArea.getYAxis().setLabel("Numar studenti");
        chartArea.getYAxis().setAnimated(false);
        chartArea.getYAxis().setAutoRanging(false);
        yAxa.setLowerBound(0);
        yAxa.setUpperBound(25);
        yAxa.setTickUnit(5);

        chartArea.getData().add(0, chart);
    }

    void populateTabelStudenti(List<Student> list){
        tblResults.setVisible(true);
        tblResults.getItems().clear();
        tblResults.getColumns().clear();

        numeStudent = new TableColumn("Nume student");
        medieStudent = new TableColumn("Grupa");

        numeStudent.setPrefWidth(2 * tblResults.getWidth() / 3);
        medieStudent.setPrefWidth(tblResults.getWidth() / 3);
        tblResults.getColumns().addAll(numeStudent, medieStudent);

        numeStudent.setCellValueFactory(new Callback<TableColumn.CellDataFeatures<Student, String>, ObservableValue<String>>() {
            public ObservableValue<String> call(TableColumn.CellDataFeatures<Student, String> p) {
                return new ReadOnlyObjectWrapper(serviceNota.getServiceStudent().searchStudent(p.getValue().getId()).getNume()
                        + " " + serviceNota.getServiceStudent().searchStudent(p.getValue().getId()).getPrenume());
            }
        });

        medieStudent.setCellValueFactory(new PropertyValueFactory<>("grupa"));
        tblResults.setItems(FXCollections.observableList(list));
    }

    void populateTabelTeme(List<DTOTemaMedie> list){
        list.sort((x,y) -> {return (int) (x.getMedie() - y.getMedie());});
        tblResults.setVisible(true);
        tblResults.getItems().clear();
        tblResults.getColumns().clear();

        numeStudent = new TableColumn("Descriere tema");
        medieStudent = new TableColumn("Medie tema");

        numeStudent.setPrefWidth(2 * tblResults.getWidth() / 3);
        medieStudent.setPrefWidth(tblResults.getWidth() / 3);

        numeStudent.setCellValueFactory(new Callback<TableColumn.CellDataFeatures<DTOTemaMedie, String>, ObservableValue<String>>() {
            public ObservableValue<String> call(TableColumn.CellDataFeatures<DTOTemaMedie, String> p) {
                return new ReadOnlyObjectWrapper(serviceNota.getServiceTema().searchTema(p.getValue().getIdTema()).getDescriere());
            }
        });
        medieStudent.setCellValueFactory(new PropertyValueFactory<>("medie"));



        tblResults.getSortOrder().clear();
        tblResults.getSortOrder().add(medieStudent);
        medieStudent.setSortType(TableColumn.SortType.DESCENDING);
        medieStudent.setSortable(true);

        tblResults.getColumns().addAll(numeStudent, medieStudent);
        tblResults.setItems(FXCollections.observableList(list));
    }

    void updateChartStudenti(List<Student> list){
        chartArea.setVisible(true);
        chartArea.setTitle("Histograma studenti");
        chartArea.getData().clear();
        chartArea.layout();
        xAxa.setLabel("Grupa");
        xAxa.setAnimated(false);

        yAxa.setAutoRanging(false);
        yAxa.setAnimated(false);
        yAxa.setLowerBound(0);
        yAxa.setUpperBound(25);
        yAxa.setTickUnit(5);


        HashMap<Integer, Integer> hashMap = new HashMap<>();
        for (int i = 221; i <= 227; i++) {
            hashMap.putIfAbsent(i, 0);
        }
        for (Student student:
                list) {
            hashMap.put(Integer.parseInt(student.getGrupa()), hashMap.get(Integer.parseInt(student.getGrupa())) + 1);
        }


        XYChart.Series chart = new XYChart.Series();
        chart.getData().clear();
        for (int i = 221; i <= 227; i++) {
            chart.getData().add(new XYChart.Data<>(String.valueOf(i), hashMap.get(i)));
        }


        chartArea.getData().add(chart);
    }

    public String getDirector(){
        DirectoryChooser directoryChooser = new DirectoryChooser();
        directoryChooser.setInitialDirectory(new File("src"));
        File selectedDirectory = directoryChooser.showDialog(chartArea.getScene().getWindow());

        String label = selectedDirectory.getAbsolutePath();
        return label;
    }

    public void handleNoteSave() throws FileNotFoundException, DocumentException {
        String whereTo = getDirector();
        insertStudentsIntoPdf(serviceNota.filterAverageGrade(), "raportMediiStudenti",600, 600, whereTo, "Medie"
        ,"Raport cu mediile studentilor la MAP");
    }

    public void handleMedieTeme(){
        return;
    }

    public void handleStudentiAdmisi() throws FileNotFoundException, DocumentException {
        String whereTo = getDirector();
        List <DTOStudentMedie> lista = serviceNota.filterAcceptedStudents().stream()
                .map(x -> {
                    return new DTOStudentMedie(x.getIdStudent(),
                            Double.valueOf(serviceNota.getServiceStudent()
                                    .searchStudent(x.getIdStudent()).getGrupa()));
                }).collect(Collectors.toList());
        insertStudentsIntoPdf(lista, "raportStudentiAdmisi",600, 600, whereTo, "Grupa",
                "Raport cu studentii admisi in examen");
    }

    public void handleAllTeme() throws FileNotFoundException, DocumentException {
        String whereTo = getDirector();
        List <DTOStudentMedie> lista = serviceNota.filterAcceptedStudents().stream()
                                                                .map(x -> {
                                                                    return new DTOStudentMedie(x.getIdStudent(),
                                                                            Double.valueOf(serviceNota.getServiceStudent()
                                                                                    .searchStudent(x.getIdStudent()).getGrupa()));
                                                                }).collect(Collectors.toList());
        insertStudentsIntoPdf(lista, "raportStudentiPunctuali",600, 600, whereTo, "Grupa",
                "Raport cu studentii punctuali");
    }


    @FXML
    public void handleNoteLaborator(){
        populateTabel(serviceNota.filterAverageGrade());
        updateChart(serviceNota.filterAverageGrade());
    }

    @FXML
    public void handleTemeGrele(){
        populateTabelTeme(serviceNota.filterMostDifficultHW2());
        chartArea.setVisible(false);
    }

    @FXML
    public void handleStudentiExamen(){
        List<Student> lista = serviceNota.filterAcceptedStudents().stream().map(x ->
                serviceNota.getServiceStudent().searchStudent(x.getIdStudent())).collect(Collectors.toList());
        populateTabelStudenti(lista);
        updateChartStudenti(lista);
    }

    @FXML
    public void handleStudentiTeme(){
        populateTabelStudenti(serviceNota.filterPunctualStudents());
        updateChartStudenti(serviceNota.filterPunctualStudents());
    }
    @FXML
    public void setServiceNota(ServiceNota serviceNota){
        this.serviceNota = serviceNota;
    }

    public void insertStudentsIntoPdf(List<DTOStudentMedie> list, String name, int height, int width, String path, String coloana
                                      ,String titlu) throws FileNotFoundException, DocumentException {
        Document document = new Document();
        PdfWriter writer = PdfWriter.getInstance(document, new FileOutputStream(path + "\\" +
                name + ".pdf"));

        document.addTitle(titlu);

        document.open();

        Paragraph paragraph = new Paragraph(titlu);
        document.add(new Paragraph(titlu));
        document.add(new Paragraph("Tabel:"));

        PdfPTable table = new PdfPTable(2);

        Stream.of("NUME + PRENUME", coloana)
                .forEach(columnTitle -> {
                    PdfPCell header = new PdfPCell();
                    header.setBackgroundColor(BaseColor.CYAN);
                    header.setBorderWidth(2);
                    header.setPhrase(new Phrase(columnTitle));
                    table.addCell(header);
                });

        int contor = 0;
        for (DTOStudentMedie student: list) {
            String studentName = serviceNota.getServiceStudent().searchStudent(student.getIdStudent()).getNume() + " " +
                    serviceNota.getServiceStudent().searchStudent(student.getIdStudent()).getPrenume();
            table.addCell(studentName);
            if(coloana.equals("Grupa")){
                Double d = student.getMedieNeaproximata();
                table.addCell(String.valueOf(d.intValue()));
            }
            else{
                table.addCell(String.valueOf(student.getMedie()));
            }
            contor++;
            ///paginare de 40 manuala
            if(contor % 40 == 0){
                document.add(table);
                document.newPage();
                table.flushContent();
            }
        }
        if(contor % 40 != 0){
            document.add(table);
            document.newPage();
        }

        PdfContentByte contentByte = writer.getDirectContent();
        PdfTemplate template = contentByte.createTemplate(width, height);
        Graphics2D graphics2d = template.createGraphics(width, height,
                new DefaultFontMapper());
        Rectangle2D rectangle2d = new Rectangle2D.Double(0, 0, width, height);

        JFreeChart chart = PieChartCreator.generateBarChart(list, titlu, coloana, "Numar studenti");
        chart.draw(graphics2d, rectangle2d);

        graphics2d.dispose();
        contentByte.addTemplate(template, 0, 0);

        document.close();
    }
}
