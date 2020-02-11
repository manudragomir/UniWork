package utils;

import domain.DTOStudentMedie;
import domain.Student;
import javafx.scene.chart.XYChart;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.axis.NumberAxis;
import org.jfree.chart.axis.NumberTickUnit;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.chart.plot.XYPlot;
import org.jfree.chart.renderer.xy.XYItemRenderer;
import org.jfree.data.category.CategoryDataset;
import org.jfree.data.category.DefaultCategoryDataset;

import javax.swing.*;
import java.awt.*;
import java.util.HashMap;
import java.util.List;

public class PieChartCreator {
    private static DefaultCategoryDataset createDataset1(List<DTOStudentMedie> studentList) {
        DefaultCategoryDataset dataSet = new DefaultCategoryDataset();
        int[] a = new int[11];
        for (int i = 0; i <= 10; i++) {
            a[i] = 0;
        }
        for (DTOStudentMedie student : studentList) {
            a[(int)student.getMedie()]++;
        }
        for (int i = 1; i < 10; i++) {
            dataSet.setValue(a[i], "Nota", "[" + String.valueOf(i) + ";" + String.valueOf(i+1) + "]");
        }

        dataSet.setValue(a[10], "Nota", "10");
        return dataSet;
    }

    private static DefaultCategoryDataset createDataset2(List<DTOStudentMedie> studentList){
        DefaultCategoryDataset dataSet = new DefaultCategoryDataset();
        HashMap<Integer, Integer> hashMap = new HashMap<>();
        for (int i = 221; i <= 227; i++) {
            hashMap.putIfAbsent(i, 0);
        }
        for (DTOStudentMedie student: studentList) {
            Double d = student.getMedieNeaproximata();

            hashMap.put(d.intValue(),
                    hashMap.get(d.intValue()) + 1);
        }

        for (int i = 221; i <= 227; i++) {
            dataSet.setValue(hashMap.get(i).doubleValue(), "Numar", String.valueOf(i));
        }
        return dataSet;
    }


    public static JFreeChart generateBarChart(List<DTOStudentMedie> studentList, String titlu, String numeOx, String numeOy) {
        DefaultCategoryDataset dataSet = new DefaultCategoryDataset();
        if(numeOx.equals("Grupa"))
            dataSet = createDataset2(studentList);
        else{
            dataSet = createDataset1(studentList);
        }

        JFreeChart chart = ChartFactory.createBarChart(
                titlu, numeOx, numeOy,
                dataSet, PlotOrientation.VERTICAL, false, true, false);

        chart.getCategoryPlot().getRangeAxis().setStandardTickUnits(NumberAxis.createIntegerTickUnits());
        return chart;
    }

    private static JFreeChart createChart(CategoryDataset dataset, String titlu, String numeOx, String numeOy) {
        JFreeChart barChart = ChartFactory.createBarChart(
                titlu,
                numeOx,
                numeOy,
                dataset,
                PlotOrientation.VERTICAL,
                false, true, false);
        return barChart;
    }

}
