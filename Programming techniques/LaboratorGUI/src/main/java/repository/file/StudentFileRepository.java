package repository.file;

import domain.Student;
import validators.Validator;

public class StudentFileRepository extends AbstractFileRepository<Long, Student> {
    public StudentFileRepository(Validator validator, String fileName) {
        super(validator, fileName);
    }

    @Override
    protected Student createEntityFromLine(String linie) {
        String[] l = linie.split(";");
        Student s = new Student(l[1],l[2],l[3],l[4],l[5]);
        s.setId(Long.parseLong(l[0]));
        return s;
    }

    @Override
    protected String createLineFromEntity(Student entity) {
        return entity.getId() + ";" +
                entity.getNume() + ";" +
                entity.getPrenume() + ";" +
                entity.getGrupa() + ";" +
                entity.getEmail() + ";" +
                entity.getCadruDidacticIndrumatorLab();
    }
}
