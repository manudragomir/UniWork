package validators;


/**
 * Validator interface
 */
public interface Validator<E> {
    /**
     * @throws ValidationException
     * if the entity is not valid
     */
    void validate(E entity) throws ValidationException;
}
