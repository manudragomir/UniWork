package domain;

import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;

/**
 * Class that have details about the structure of the university year
 */
public class StructuraAnUniversitar extends Entity<Long> {
    private int an;
    private static StructuraSemestru sem1;
    private static StructuraSemestru sem2;

    /**
     *
     * Constructor for StructuraAnUniversitar
     * @param an -the year of the university year
     * @param sem1 - the structure for first term
     * @param sem2 - the structure for second term
     */
    public StructuraAnUniversitar(int an, StructuraSemestru sem1, StructuraSemestru sem2) {
        this.an = an;
        this.sem1 = sem1;
        this.sem2 = sem2;
    }

    public static int getWeekFromData(Date data) {
        Calendar calendar = new GregorianCalendar();
        Date trialTime = data;
        calendar.setTime(trialTime);

        //daca e mai mare decat a doua zi calculez in functie de semestru 2
        if(trialTime.after(sem2.getPrimaZi())){
            return sem2.getCurrentWeekNumber(trialTime);
        }
        else{
            return sem1.getCurrentWeekNumber(trialTime);
        }
    }

    public static int getCurrentWeek(){
        Calendar calendar = new GregorianCalendar();
        Date trialTime = new Date();
        calendar.setTime(trialTime);

        //daca e mai mare decat a doua zi calculez in functie de semestru 2
        if(trialTime.after(sem2.getPrimaZi())){
            return sem2.getCurrentWeekNumber(trialTime);
        }
        else{
            return sem1.getCurrentWeekNumber(trialTime);
        }
    }
}
