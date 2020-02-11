package domain;

public class NotaUtila {
    private Long numarTema;
    private double valueNota;
    private int saptPredata;
    private int deadline;
    private String feedback;

    public NotaUtila(Long numarTema, double valueNota, int saptPredata, int deadline, String feedback) {
        this.numarTema = numarTema;
        this.valueNota = valueNota;
        this.saptPredata = saptPredata;
        this.deadline = deadline;
        this.feedback = feedback;
    }

    @Override
    public String toString() {
        return "Tema: " + numarTema + "\n" +
                "Nota: " + valueNota + "\n" +
                "Predata in saptamana: " + saptPredata + "\n" +
                "Deadline: " + deadline + "\n" +
                "Feedback: " + feedback;
    }
}
