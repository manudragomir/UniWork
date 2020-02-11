package repository.database;

import domain.Student;
import validators.Validator;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class RepoStudentDB extends RepoAbstractDB<Long, Student> {
    public RepoStudentDB(Validator validator) throws SQLException {
        super(validator);
    }

    public ResultSet returnEntityById(Long id) throws SQLException {
        String SQL = "SELECT * FROM studenti where id = ?;";
        PreparedStatement state = c.prepareStatement(SQL);
        state.setLong(1, id);
        ResultSet resultSet = state.executeQuery();
        return resultSet;
    }

    public Student createEntityByResultSet(ResultSet resultSet) throws SQLException {
        Long id = resultSet.getLong("id");
        String nume = resultSet.getString("first_name");
        String prenume = resultSet.getString("last_name");
        String email = resultSet.getString("email");
        String grupa = resultSet.getString("groupNo");
        String cd = resultSet.getString("teacher");
        Student s = new Student(nume, prenume, grupa, email, cd);
        s.setId(id);
        return s;
    }

    public ResultSet getAllEntitiesFromDB() throws SQLException {
        String SQLQuery = "SELECT * FROM studenti;";
        ResultSet resultSet = stmt.executeQuery(SQLQuery);
        return resultSet;
    }

    public void saveSQLQuery(Student entity) throws SQLException {
        String SQLInsertion = "INSERT INTO studenti (id, first_name, last_name, groupno, email, teacher) " +
                            "VALUES (?, ?, ?, ?, ?, ?);";

        PreparedStatement st = c.prepareStatement(SQLInsertion);
        st.setLong(1, entity.getId());
        st.setString(2, entity.getNume());
        st.setString(3, entity.getPrenume());
        st.setString(4, entity.getGrupa());
        st.setString(5, entity.getEmail());
        st.setString(6, entity.getCadruDidacticIndrumatorLab());
        st.executeUpdate();
        st.close();
    }


    public void updateSQLQuery(Student entity) throws SQLException {
        String SQLQueryUpdate = "UPDATE studenti SET first_name = ?, last_name = ?, email = ?, groupno = ?," +
                "teacher = ? WHERE id = ?";
        PreparedStatement stateUpdate = c.prepareStatement(SQLQueryUpdate);
        stateUpdate.setString(1, entity.getNume());
        stateUpdate.setString(2, entity.getPrenume());
        stateUpdate.setString(3, entity.getEmail());
        stateUpdate.setString(4, entity.getGrupa());
        stateUpdate.setString(5, entity.getCadruDidacticIndrumatorLab());
        stateUpdate.setLong(6, entity.getId());
        stateUpdate.execute();
    }

    public void deleteSQLQuery(Long id) throws SQLException {
        String SQLQueryDeletion = "DELETE FROM studenti WHERE id = ?";
        PreparedStatement stateDeletion = c.prepareStatement(SQLQueryDeletion);
        stateDeletion.setLong(1, id);
        stateDeletion.executeUpdate();
    }
}
