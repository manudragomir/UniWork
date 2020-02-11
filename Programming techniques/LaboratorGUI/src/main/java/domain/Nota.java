package domain;


import java.util.Date;

/**
 * Class for Grades
 */
public class Nota extends Entity<IDNota> {
    private Date data;
    private Tema tema;
    private double value;
    private String profesor;

    /**
     * A constructor for the Grade
     * @param data the data when the mark grade is assigned
     * @param profesor the name of the teacher who gave the grade
     * @param student the student that receive the grade
     * @param tema the homework the grade is assigned
     */
    public Nota(Date data, String profesor, Student student, Tema tema, double value) {
        this.data = data;
        this.value = value;
        this.profesor = profesor;
        IDNota idNota = new IDNota(student.getId(), tema.getId());
        this.setId(idNota);
    }

    public Nota(Date data, double value, String profesor){
        this.data = data;
        this.value = value;
        this.profesor = profesor;
    }

    @Override
    public String toString() {
        return "Nota{" + this.getId().getStudentId() + " " + this.getId().getTemaId() +
                "data=" + data +
                ", value=" + value +
                ", profesor='" + profesor + '\'' +
                '}';
    }

    public String getProfesor() {
        return profesor;
    }

    public double getValue(){return value;}

    /**
     *
     * Getter for data
     * @return data
     */
    public Date getData() {
        return data;
    }

    /**
     *
     * Setter for data
     */
    public void setData(Date data) {
        this.data = data;
    }
}
