package repository.database;

import domain.Entity;
import repository.CrudRepository;
import validators.ValidationException;
import validators.Validator;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

public abstract class RepoAbstractDB<ID, E extends Entity<ID>> implements CrudRepository<ID, E> {
    protected Connection c;
    protected Validator validator;
    protected Statement stmt;

    public RepoAbstractDB(Validator validator) throws SQLException {
        this.validator = validator;
        c = Connect.connect();
        stmt  = c.createStatement();
    }

    public abstract ResultSet returnEntityById(ID id) throws SQLException;
    public abstract E createEntityByResultSet(ResultSet resultSet) throws SQLException;

    @Override
    public E findOne(ID id) {
        try {
            ResultSet resultSet = returnEntityById(id);
            if(resultSet.next() == true) {
                return createEntityByResultSet(resultSet);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }

    public abstract ResultSet getAllEntitiesFromDB() throws SQLException;

    @Override
    public Iterable<E> findAll() {
        try {
            List<E> entityList = new ArrayList<>();
            ResultSet resultSet = getAllEntitiesFromDB();
            while (resultSet.next()) {
                E entity = (E)createEntityByResultSet(resultSet);
                entityList.add(entity);
            }
            return entityList;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }

    public abstract void saveSQLQuery(E entity) throws SQLException;
    public abstract void deleteSQLQuery(ID id) throws SQLException;
    public abstract void updateSQLQuery(E entity) throws SQLException;
    @Override
    public E save(E entity) throws ValidationException {
        if (entity == null) {
            throw new IllegalArgumentException("ENTITATE NULA!");
        }

        validator.validate(entity);
        try {
            if(findOne(entity.getId()) == null){
                saveSQLQuery(entity);
                return null;
            }
            return entity;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public E delete(ID id) {
        if (id == null) {
            throw new IllegalArgumentException("ID NULL!");
        }

        E entity = findOne(id);
        if(entity == null){
            return null;
        }
        try {
            deleteSQLQuery(id);
            return entity;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public E update(E entity) {
        if(entity == null){
            throw new IllegalArgumentException("Entitate nula!");
        }

        validator.validate(entity);

        if(findOne(entity.getId()) == null){
            return entity;
        }
        try {
            updateSQLQuery(entity);
            return null;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }
}
