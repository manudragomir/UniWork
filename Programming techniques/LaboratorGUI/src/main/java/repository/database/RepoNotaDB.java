package repository.database;

import domain.IDNota;
import domain.Nota;
import validators.Validator;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Date;

public class RepoNotaDB extends RepoAbstractDB<IDNota, Nota> {
    public RepoNotaDB(Validator validator) throws SQLException {
        super(validator);
    }

    public ResultSet returnEntityById(IDNota id) throws SQLException {
        String SQL = "SELECT * FROM grades G INNER JOIN studenti S on ? = G.sid INNER JOIN teme T ON ? = G.tid;";
        PreparedStatement state = c.prepareStatement(SQL);
        state.setLong(1, (Long)id.getStudentId());
        state.setLong(2, (Long)id.getTemaId());
        ResultSet resultSet = state.executeQuery();
        return resultSet;
    }

    public Nota createEntityByResultSet(ResultSet resultSet) throws SQLException {
        Long idStudent = resultSet.getLong("sid");
        Long idTema = resultSet.getLong("tid");
        String profesor = resultSet.getString("teacher");
        double value = resultSet.getDouble("value");
        Date data = resultSet.getDate("data");
        Nota nota = new Nota(data,value,profesor);
        nota.setId(new IDNota(idStudent, idTema));
        return nota;
    }

    public ResultSet getAllEntitiesFromDB() throws SQLException {
        String SQLQuery = "SELECT * FROM grades G;";
        ResultSet resultSet = stmt.executeQuery(SQLQuery);
        return resultSet;
    }

    public void saveSQLQuery(Nota entity) throws SQLException {
        String SQLInsertion = "INSERT INTO grades (sid, tid, value, data, teacher) " +
                "VALUES (?, ?, ?, ?, ?)";
        PreparedStatement st = c.prepareStatement(SQLInsertion);
        st.setLong(1, entity.getId().getStudentId());
        st.setLong(2, entity.getId().getTemaId());
        st.setDouble(3, entity.getValue());
        st.setDate(4, new java.sql.Date(entity.getData().getTime()));
        st.setString(5, entity.getProfesor());
        st.executeUpdate();
        st.close();
    }

    public void deleteSQLQuery(IDNota idNota) throws SQLException {
        ResultSet resultSet;
        String SQLQueryDeletion = "DELETE FROM grades WHERE tid = ? and sid = ?;";
        PreparedStatement stateDeletion = c.prepareStatement(SQLQueryDeletion);
        stateDeletion.setLong(1, (Long)idNota.getTemaId());
        stateDeletion.setLong(2, (Long)idNota.getStudentId());
        stateDeletion.executeUpdate();
    }

    public void updateSQLQuery(Nota entity) throws SQLException {
        String SQLQueryUpdate = "UPDATE grades SET data = ?, value = ?, profesor = ? WHERE tid = ? and sid = ?;";
        PreparedStatement stateUpdate = c.prepareStatement(SQLQueryUpdate);
        stateUpdate.setDate(1, new java.sql.Date(entity.getData().getTime()));
        stateUpdate.setDouble(2, entity.getValue());
        stateUpdate.setString(3, entity.getProfesor());
        stateUpdate.setLong(4, (Long)entity.getId().getStudentId());
        stateUpdate.setLong(5, (Long)entity.getId().getTemaId());
        stateUpdate.execute();
    }
}