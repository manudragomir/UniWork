package domain;

import java.util.*;

public class StructuraSemestru extends Entity<Long> {
    private Date primaZi;
    private Map<Integer, Integer> pairs = new HashMap<Integer, Integer>();

    /**
     * A constructor for the term structure
     * @param primaZi which stores the first day of the term
     */
    public StructuraSemestru(Date primaZi) {
        this.primaZi = primaZi;
    }

    /**
     * @return first day of the term
     */
    public Date getPrimaZi() {
        return primaZi;
    }

    /**
     * Function that adds holidays of the term
     * @param startWeek the first day of the current holiday
     * @param numberOfWeeks how much is the holiday
     */
    public void adaugaVacanta(Date startWeek, int numberOfWeeks){
        Calendar calendar = new GregorianCalendar();
        Date trialTime = startWeek;
        calendar.setTime(trialTime);
        int countStartWeek = calendar.get(Calendar.WEEK_OF_YEAR);
        pairs.put(countStartWeek, numberOfWeeks);
    }

    /**
     * @return the number of the week in the current term structure
     */
    public int getCurrentWeekNumber(Date _trialTime){
        Calendar calendar = new GregorianCalendar();
        Date trialTime = _trialTime;
        calendar.setTime(trialTime);
        int saptCurenta = calendar.get(Calendar.WEEK_OF_YEAR);
        Date date = new GregorianCalendar(2020, Calendar.JANUARY, 1).getTime();
        if(trialTime.after(date)) saptCurenta += 52;//nr de saptamani dintr-un an

        Date ziStart = getPrimaZi();
        calendar.setTime(ziStart);
        int saptStart = calendar.get(Calendar.WEEK_OF_YEAR);

        int currentWeekNumber = saptCurenta - saptStart;
        for (Map.Entry<Integer,Integer> entry : pairs.entrySet()) {
            if (saptCurenta > entry.getKey()) {
                currentWeekNumber -= entry.getValue();
            }
        }
        return currentWeekNumber + 1;
    }

    /**
     *
     * Setter for first day
     */
    public void setPrimaZi(Date primaZi) {
        this.primaZi = primaZi;
    }
}
