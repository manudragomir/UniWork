package services.service;

import domain.Student;
import repository.CrudRepository;
import utils.ObserverPattern.Observable;
import validators.ValidationException;

import java.util.*;
import java.util.stream.Collectors;

public class ServiceStudent extends Observable {
    private CrudRepository repository = null;

    public ServiceStudent(CrudRepository repository) {
        this.repository = repository;
    }

    public Student addStudent(Student student) throws ValidationException {
        Student s = (Student) repository.save(student);
        notifyy();
        return s;
    }

    public Student removeStudent(Long id) {
        Student s = (Student) repository.delete(id);
        notifyy();
        return s;
    }

    public Student searchStudent(Long id){
        return (Student) repository.findOne(id);
    }

    public Student updateStudent(Student student) {
        Student s = (Student) repository.update(student);
        notifyy();
        return s;
    }

    public List<Student> getAllStudents(){
        Collection<Student> collection = (Collection<Student>) repository.findAll();
        List<Student> list = new ArrayList<Student>(collection);
        return list;
    }


    public List<Student> filterStudentsOfAGroup(String grupa) {
        List<Student> list = getAllStudents();
        List<Student> res = list.stream()
                .filter(s -> s.getGrupa().equals(grupa))
                .collect(Collectors.toList());
        return res;

    }


}
