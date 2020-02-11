package domain;

import java.util.Objects;

/**
 * Class of the student with ID of type long
 */
public class Student extends Entity<Long> {
    private static Long contorId = 0L;
    private String nume, prenume, grupa, email, cadruDidacticIndrumatorLab;
    private double medie;

    /**
     * A constructor for Student
     * @param nume the first name of the student
     * @param prenume surname of the student
     * @param grupa the group of the student
     * @param email email of the student
     * @param cadruDidacticIndrumatorLab the name of the coordinator
     */
    public Student(String nume, String prenume, String grupa, String email, String cadruDidacticIndrumatorLab) {
        //default
        this.setId(0L);
        this.nume = nume;
        this.prenume = prenume;
        this.grupa = grupa;
        this.email = email;
        this.cadruDidacticIndrumatorLab = cadruDidacticIndrumatorLab;
    }
    /**
     *
     * Getter for name
     * @return name of the student
     */
    public String getNume() {
        return nume;
    }

    public void setMedie(double medie) {
        this.medie = medie;
    }

    public double getMedie() {
        return medie;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Student student = (Student) o;
        return ((Student) o).getId() == this.getId();
    }

    @Override
    public int hashCode() {
        return Objects.hash(nume);
    }

    /**
     *
     * Setter for name
     */
    public void setNume(String nume) {
        this.nume = nume;
    }

    /**
     *
     * Getter for surname
     * @return surname
     */
    public String getPrenume() {
        return prenume;
    }

    /**
     *
     * Setter for surname
     */
    public void setPrenume(String prenume) {
        this.prenume = prenume;
    }

    /**
     *
     * Getter for group
     * @return group
     */
    public String getGrupa() {
        return grupa;
    }

    /**
     *
     * Setter for group
     */
    public void setGrupa(String grupa) {
        this.grupa = grupa;
    }

    /**
     *
     * Getter for email
     * @return email
     */
    public String getEmail() {
        return email;
    }

    /**
     *
     * Setter for data
     */
    public void setEmail(String email) {
        this.email = email;
    }

    public String getCadruDidacticIndrumatorLab() {
        return cadruDidacticIndrumatorLab;
    }

    /**
     *
     * Setter for data
     */
    public void setCadruDidacticIndrumatorLab(String cadruDidacticIndrumatorLab) {
        this.cadruDidacticIndrumatorLab = cadruDidacticIndrumatorLab;
    }



    @Override
    public String toString() {
        return  "nume=" + nume +
                ", prenume=" + prenume +
                '}';
    }
}
