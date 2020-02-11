package domain;

import validators.ValidationException;

public class Tema extends Entity<Long> {
    private String descriere;
    private int startWeek, deadlineWeek;
    private double mediet;
    private static Long contorId = 0L;

    /**
     * constructor of tema
     * @param deadlineWeek - deadline
     * @param descriere - description
     */
    public Tema(int deadlineWeek, String descriere) {
        this.setId(0L);
        this.startWeek = StructuraAnUniversitar.getCurrentWeek();
        this.deadlineWeek = deadlineWeek;
        this.descriere = descriere;
    }

    public double getMediet() {
        return mediet;
    }

    public void setMediet(double mediet) {
        this.mediet = mediet;
    }

    public String getDescriere() {
        return descriere;
    }

    public void setDescriere(String descriere) {
        this.descriere = descriere;
    }

    public int getStartWeek() {
        return startWeek;
    }
    public int getDeadlineWeek() {
        return deadlineWeek;
    }

    public void setStartWeek(int startWeek) {
        this.startWeek = startWeek;
    }


    public void setDeadlineWeek(int deadlineWeek) {
        this.deadlineWeek = deadlineWeek;

    }

    @Override
    public String toString() {
        return "Tema: " + super.getId().toString() + " " +
                "descriere='" + descriere + '\'' +
                ", startWeek=" + startWeek +
                ", deadlineWeek=" + deadlineWeek;
    }
}
