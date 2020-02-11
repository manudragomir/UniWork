package domain;

public class DTOTemaMedie {
    private long idTema;
    private double medie;

    public DTOTemaMedie(long idTema, double medie) {
        this.idTema = idTema;
        this.medie = medie;
    }

    public long getIdTema() {
        return idTema;
    }

    public double getMedie(){
        return (Math.floor(medie * 100)) / 100;
    }
}