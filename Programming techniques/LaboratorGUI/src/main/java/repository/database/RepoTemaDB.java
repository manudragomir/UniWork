package repository.database;

import domain.Tema;
import validators.Validator;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class RepoTemaDB extends RepoAbstractDB<Long, Tema> {
    public RepoTemaDB(Validator validator) throws SQLException {
        super(validator);
    }

    public ResultSet returnEntityById(Long id) throws SQLException {
        String SQL = "SELECT * FROM teme where tid = ?;";
        PreparedStatement state = c.prepareStatement(SQL);
        state.setLong(1, id);
        ResultSet resultSet = state.executeQuery();
        return resultSet;
    }

    public Tema createEntityByResultSet(ResultSet resultSet) throws SQLException {
        Long id = resultSet.getLong("tid");
        String descript = resultSet.getString("descript");
        int startWeek = resultSet.getInt("startWeek");
        int deadlineWeek = resultSet.getInt("deadlineWeek");
        Tema tema = new Tema(deadlineWeek, descript);
        tema.setStartWeek(startWeek);
        tema.setId(id);
        return tema;
    }

    public ResultSet getAllEntitiesFromDB() throws SQLException {
        String SQLQuery = "SELECT * FROM teme;";
        ResultSet resultSet = stmt.executeQuery(SQLQuery);
        return resultSet;
    }

    public void saveSQLQuery(Tema entity) throws SQLException {
        String SQLInsertion = "INSERT INTO teme (tid, descript, startWeek, deadlineWeek) " +
                "VALUES (?, ?, ?, ?)";
        PreparedStatement st = c.prepareStatement(SQLInsertion);
        st.setLong(1, entity.getId());
        st.setInt(3, entity.getStartWeek());
        st.setInt(4, entity.getDeadlineWeek());
        st.setString(2, entity.getDescriere());
        st.executeUpdate();
        st.close();
    }

    public void updateSQLQuery(Tema entity) throws SQLException {
        String SQLQueryUpdate = "UPDATE teme SET startWeek = ?, deadlineWeek = ?, descript = ? WHERE tid = ?";
        PreparedStatement stateUpdate = c.prepareStatement(SQLQueryUpdate);
        stateUpdate.setInt(1, entity.getStartWeek());
        stateUpdate.setInt(2, entity.getDeadlineWeek());
        stateUpdate.setString(3, entity.getDescriere());
        stateUpdate.setLong(4, entity.getId());
        stateUpdate.execute();
    }

    public void deleteSQLQuery(Long currId) throws SQLException {
        String SQLQueryDeletion = "DELETE FROM teme WHERE tid = ?";
        PreparedStatement stateDeletion = c.prepareStatement(SQLQueryDeletion);
        stateDeletion.setLong(1, currId);
        stateDeletion.executeUpdate();
    }

}
