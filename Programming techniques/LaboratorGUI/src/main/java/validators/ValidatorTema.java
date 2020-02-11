package validators;

import domain.Tema;

/**
 * Validator for validating the task
 */
public class ValidatorTema implements Validator<Tema> {

    /**
     * Validate homework in order to be plausible
     * @param entity - homework we want to validate
     * @throws ValidationException
     * if the given start and the deadline weeks are not between [1;14]
     * if the start week is greater than the end week
     */
    @Override
    public void validate(Tema entity) throws ValidationException {
        int start = entity.getStartWeek();
        int end = entity.getDeadlineWeek();
        if(!(start >= 1 && start <= 14 && end >=1 && end <=14)){
            throw new ValidationException("Saptamana e un numar natural intre 1 si 14!");
        }

        if(start > end){
            throw new ValidationException("Endline eronat!");
        }
    }
}
