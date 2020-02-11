package validators;

import domain.Student;

/**
 * Validator for validating the student
 */
public class ValidatorStudent implements Validator<Student> {

    /**
     * Validate student
     * @param entity - student we want to validate
     * @throws ValidationException
     * if the student name or surname is empty
     */
    @Override
    public void validate(Student entity) throws ValidationException {
        if(entity.getNume().length() == 0 || entity.getPrenume().length() == 0) {
            throw new ValidationException("Nume sau prenume vide");
        }
    }
}