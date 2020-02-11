package repository.database;

import java.sql.Connection;
import java.sql.DriverManager;

public class Connect {
    /**
     * function that connects the application to the database note
     */
    public static Connection connect(){
        Connection c = null;
        try {
            Class.forName("org.postgresql.Driver");
            c = DriverManager
                    .getConnection("jdbc:postgresql://localhost:5432/note",
                            "postgres", "123");
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(0);
        }
        return c;
    }
}
