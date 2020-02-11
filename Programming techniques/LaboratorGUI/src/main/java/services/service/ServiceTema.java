package services.service;


import controller.TemaController;
import domain.StructuraAnUniversitar;
import domain.Tema;
import repository.CrudRepository;
import utils.ObserverPattern.Observable;
import validators.ValidationException;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

public class ServiceTema extends Observable {
    private CrudRepository repository = null;

    public ServiceTema(CrudRepository repository) {
        this.repository = repository;
    }

    public Tema addTema(Tema tema) {
        Tema t = (Tema) repository.save(tema);
        notifyy();
        return t;
    }

    public Tema removeTema(Long id) {
        Tema t = (Tema) repository.delete(id);
        notifyy();
        return t;
    }

    public Tema updateTema(Tema tema) throws ValidationException {
        if(tema.getDeadlineWeek() < StructuraAnUniversitar.getCurrentWeek() || tema.getDeadlineWeek() > 14){
            throw new ValidationException("Nu poate fi acest deadline!");
        }
        Tema t = (Tema) repository.update(tema);
        notifyy();
        return t;
    }

    public List<Tema> getAllTeme(){
        Collection<Tema> collection = (Collection<Tema>) repository.findAll();
        List<Tema> list = new ArrayList<Tema>(collection);
        return list;
    }

    public Tema searchTema(Long id){
        return (Tema) repository.findOne(id);
    }

}
