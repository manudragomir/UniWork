package services.service;

import domain.StructuraAnUniversitar;
import domain.StructuraSemestru;
import utils.FileDates;

import java.util.Date;
import java.util.Map;


public class ServiceAnUniv {
    String filename1, filename2;

    public ServiceAnUniv(String filename1, String filename2) {
        this.filename1 = filename1;
        this.filename2 = filename2;
    }

    public void setDate(){
        FileDates fileDatesSemester1 = new FileDates(filename1);
        FileDates fileDatesSemester2 = new FileDates(filename2);
        Date firstDayOfFirstSemester = fileDatesSemester1.getFirstDayOfSemester();
        Date firstDayOfSecondSemester = fileDatesSemester2.getFirstDayOfSemester();
        StructuraSemestru sem1 = new StructuraSemestru(firstDayOfFirstSemester);
        StructuraSemestru sem2 = new StructuraSemestru(firstDayOfSecondSemester);
        Map<Date, Integer> holidaysOfFirstSemester = fileDatesSemester1.getHolidaysOfSemester();
        Map<Date, Integer> holidaysOfSecondSemester = fileDatesSemester2.getHolidaysOfSemester();

        for (Map.Entry<Date,Integer> entry : holidaysOfFirstSemester.entrySet()) {
            sem1.adaugaVacanta(entry.getKey(), entry.getValue());
        }

        for (Map.Entry<Date,Integer> entry : holidaysOfSecondSemester.entrySet()) {
            sem2.adaugaVacanta(entry.getKey(), entry.getValue());
        }

        StructuraAnUniversitar anUniversitar = new StructuraAnUniversitar(2019, sem1, sem2);
    }
}
