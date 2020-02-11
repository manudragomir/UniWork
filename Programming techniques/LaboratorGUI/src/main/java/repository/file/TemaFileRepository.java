package repository.file;

import domain.Tema;
import validators.Validator;

public class TemaFileRepository extends AbstractFileRepository<Long, Tema> {
    public TemaFileRepository(Validator validator, String fileName) {
        super(validator, fileName);
    }

    @Override
    protected Tema createEntityFromLine(String linie) {
        String[] l = linie.split(";");
        Tema tema = new Tema(Integer.parseInt(l[2]),l[3]);
        tema.setStartWeek(Integer.parseInt(l[1]));
        tema.setId(Long.parseLong(l[0]));
        return tema;
    }

    @Override
    protected String createLineFromEntity(Tema entity) {
        return entity.getId() + ";" +
                entity.getStartWeek() + ";" +
                entity.getDeadlineWeek() + ";" +
                entity.getDescriere();
    }
}
