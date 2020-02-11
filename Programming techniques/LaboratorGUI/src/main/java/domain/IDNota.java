package domain;

import java.util.Objects;

public class IDNota {
    private Long studentId;
    private Long temaId;

    public IDNota(Long studentId, Long temaId) {
        this.studentId = studentId;
        this.temaId = temaId;
    }

    public Long getStudentId() {
        return studentId;
    }

    public void setStudentId(Long studentId) {
        this.studentId = studentId;
    }

    public Long getTemaId() {
        return temaId;
    }

    public void setTemaId(Long temaId) {
        this.temaId = temaId;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        IDNota idNota = (IDNota) o;
        return studentId.equals(idNota.studentId) &&
                temaId.equals(idNota.temaId);
    }

    @Override
    public int hashCode() {
        return Objects.hash(studentId, temaId);
    }
}
