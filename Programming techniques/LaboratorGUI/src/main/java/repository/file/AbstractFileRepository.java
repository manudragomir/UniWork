package repository.file;

import domain.Entity;
import repository.InMemoryRepository;
import validators.ValidationException;
import validators.Validator;

import java.io.BufferedWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.util.Collection;
import java.util.List;

public abstract class AbstractFileRepository<ID, E extends Entity<ID>> extends InMemoryRepository<ID, E> {
    private String fileName;
    public AbstractFileRepository(Validator validator, String fileName) {
        super(validator);
        this.fileName = fileName;
        loadData();
    }

    protected abstract E createEntityFromLine(String linie);
    protected abstract String createLineFromEntity(E entity);

    private void loadData() {
        Path path = Paths.get(fileName);
        try {
            List<String> lines = Files.readAllLines(path);
            lines.forEach(linie -> {
                E entity = createEntityFromLine(linie);
                super.save(entity);
            });
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void storeData(){
        Path path = Paths.get(fileName);
        try (BufferedWriter bufferedWriter = Files.newBufferedWriter(path, StandardOpenOption.TRUNCATE_EXISTING)) {
            Collection<E> valuesToMatch = (Collection<E>) findAll();
            for (E entity: valuesToMatch) {
                bufferedWriter.write(createLineFromEntity(entity));
                bufferedWriter.newLine();
            }
        } catch (IOException e) { e.printStackTrace(); }
    }

    @Override
    public E save(E entity) throws ValidationException {
        E result = super.save(entity);
        if(result == null){
            storeData();
        }
        return result;
    }

    @Override
    public E delete(ID id) {
        E result = super.delete(id);
        if(result != null){
            storeData();
        }
        return result;
    }

    @Override
    public E update(E entity) {
        E result = super.update(entity);
        if(result == null){
            storeData();
        }
        return result;
    }
}
