package domain;

public class DTOStudentMedie {
    private long idStudent;
    private double medie;

    public DTOStudentMedie(long idStudent, double medie) {
        this.idStudent = idStudent;
        this.medie = medie;
    }

    public long getIdStudent() {
        return idStudent;
    }

    public double getMedie() {
        return (Math.floor(medie * 100)) / 100 + 1;
    }

    public double getMedieNeaproximata(){
        return medie;
    }
}
