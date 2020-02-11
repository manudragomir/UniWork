package domain;

public class NotaDTO {
    private String numeStudent;
    private String grupa;
    private String descriereTema;
    private double valueNota;

    public NotaDTO(String numeStudent, String grupa, String descriereTema, double valueNota) {
        this.numeStudent = numeStudent;
        this.grupa = grupa;
        this.descriereTema  = descriereTema;
        this.valueNota = valueNota;
    }

    public String getNumeStudent() {
        return numeStudent;
    }

    public String getGrupa(){
        return grupa;
    }

    public void setNumeStudent(String numeStudent) {
        this.numeStudent = numeStudent;
    }

    public String getDescriereTema() {
        return descriereTema;
    }

    public void setDescriereTema(String descriereTema) {
        this.descriereTema = descriereTema;
    }

    public double getValueNota() {
        return valueNota;
    }

    public void setValueNota(double valueNota) {
        this.valueNota = valueNota;
    }

    @Override
    public String toString() {
        return "NotaDTO{" +
                "numeStudent='" + numeStudent + '\'' +
                ", descriereTema='" + descriereTema + '\'' +
                ", valueNota=" + valueNota +
                '}';
    }
}
