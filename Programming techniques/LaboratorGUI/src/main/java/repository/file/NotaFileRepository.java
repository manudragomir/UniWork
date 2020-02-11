package repository.file;

import domain.IDNota;
import domain.Nota;
import validators.Validator;

import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;

public class NotaFileRepository extends AbstractFileRepository<IDNota, Nota> {
    public NotaFileRepository(Validator validator, String fileName) {
        super(validator, fileName);
    }

    @Override
    protected Nota createEntityFromLine(String linie) {
        String[] l = linie.split(";");
        Nota nota = null;
        try {
            nota = new Nota(new SimpleDateFormat("dd.MM.yyyy").parse(l[3]),Double.parseDouble(l[2]), l[4]);
        } catch (ParseException e) {
            e.printStackTrace();
        }
        nota.setId(new IDNota(Long.parseLong(l[0]), Long.parseLong(l[1])));
        return nota;
    }

    @Override
    protected String createLineFromEntity(Nota entity) {
        DateFormat dateFormat = new SimpleDateFormat("dd.MM.yyyy");
        return entity.getId().getStudentId() + ";" +
                entity.getId().getTemaId() + ";" +
                entity.getValue() + ";" +
                dateFormat.format(entity.getData()) + ";" +
                entity.getProfesor();
    }
}
