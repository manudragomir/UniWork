package domain;

public class Entity<ID> {
    private ID id;

    /**
     * Getting the ID of the entity
     * @return Returns the id of the current entity
     */
    public ID getId() {
        return id;
    }

    /**
     * Setting the ID of the entity
     * @param  id The ID we want to set for the current entity
     */
    public void setId(ID id) {
        this.id = id;
    }
}