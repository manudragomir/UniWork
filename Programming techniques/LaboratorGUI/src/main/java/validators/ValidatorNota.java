package validators;

import domain.Nota;

public class ValidatorNota implements Validator<Nota> {
    @Override
    public void validate(Nota entity) throws ValidationException {
        if(entity.getValue() < 1 || entity.getValue() > 10) {
            throw new ValidationException("Nota nu este valida!");
        }
    }
}
