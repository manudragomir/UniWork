package repository;

import domain.Entity;
import validators.ValidationException;
import validators.Validator;

import java.util.HashMap;
import java.util.Map;

/**
 * Repository that saves student in memory
 */
public class InMemoryRepository<ID, E extends Entity<ID>> implements CrudRepository<ID, E> {
    private Validator validator;
    private Map<ID,E> entities;

    public InMemoryRepository(Validator validator) {
        this.validator = validator;
        entities = new HashMap<ID,E>();
    }

    @Override
    public E findOne(ID id) {
        if(id == null){
            throw new IllegalArgumentException("ID NUL!");
        }
        return entities.get(id);
    }

    @Override
    public Iterable<E> findAll() {
        return entities.values();
    }

    @Override
    public E save(E entity) throws ValidationException {
        if(entity == null){
            throw new IllegalArgumentException("ENTITATE NULA!");
        }
        validator.validate(entity);
        return entities.putIfAbsent(entity.getId(), entity);
    }

    @Override
    public E delete(ID id) {
        if(id == null){
            throw new IllegalArgumentException("ID NUL!");
        }
        E elem = entities.get(id);
        if(elem != null){
            entities.remove(id);
        }
        return elem;
    }

    @Override
    public E update(E entity) {
        if(entity == null){
            throw new IllegalArgumentException("Entitate nula!");
        }
        validator.validate(entity);
        E elem = entities.get(entity.getId());
        if(elem == null){
            return entity;
        }
        entities.put(entity.getId(), entity);
        return  null;
    }
}
