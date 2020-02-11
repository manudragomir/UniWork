package services.service;

import domain.*;
import repository.CrudRepository;
import utils.FileFeedbackSaver;
import utils.ObserverPattern.Observable;

import java.util.*;
import java.util.function.Function;
import java.util.stream.Collectors;

public class ServiceNota extends Observable {
    private ServiceStudent serviceStudent;
    private ServiceTema serviceTema;
    CrudRepository repository;
    FileFeedbackSaver fileFeedbackSaver;

    public ServiceNota(ServiceStudent serviceStudent, ServiceTema serviceTema, CrudRepository repository,
                       FileFeedbackSaver fileFeedbackSaver) {
        this.fileFeedbackSaver = fileFeedbackSaver;
        this.serviceStudent = serviceStudent;
        this.serviceTema = serviceTema;
        this.repository = repository;
    }

    public int maxNota(Long idTema){
        int currentWeek = StructuraAnUniversitar.getCurrentWeek();
        Tema tema = serviceTema.searchTema(idTema);
        return currentWeek - tema.getDeadlineWeek();
    }

    public boolean check(Long idStudent, Long idTema){
        if(serviceStudent.searchStudent(idStudent) != null
        && serviceTema.searchTema(idTema) != null){
            return true;
        }
        return false;
    }

    public boolean inTime(int dif){
        if(dif>=3){
            return false;
        }
        return true;
    }

    public void stergeNoteleDupaStudent(Long idStudent){
        Collection<Nota> collection = (Collection<Nota>) repository.findAll();
        List<Nota> list = new ArrayList<Nota>(collection);
        list.stream().forEach(x -> {
            if(x.getId().getStudentId().equals(idStudent)){
                repository.delete(new IDNota(idStudent, x.getId().getTemaId()));
            }
        });
    }

    public void stergeNoteleDupaTeme(Long idTema){
        Collection<Nota> collection = (Collection<Nota>) repository.findAll();
        List<Nota> list = new ArrayList<Nota>(collection);
        list.stream().forEach(x -> {
            if(x.getId().getTemaId().equals(idTema)){
                repository.delete(new IDNota(x.getId().getStudentId(), idTema));
            }
        });
    }

    //Date in loc de string - data
    public Nota adaugaNota(Long idStudent, Long idTema, Double valNota, Date data, int activ, String feedback, String profesor){
        check(idStudent, idTema);
        IDNota idNota = new IDNota(idStudent, idTema);
        Nota nota = null;
        if(maxNota(idTema) > 0)
            valNota -= maxNota(idTema);

        //ii acord un bonus
        if(serviceTema.searchTema(idTema).getDeadlineWeek() > StructuraAnUniversitar.getWeekFromData(data)){
            if(valNota < 9){
                valNota++;
            }
        }
        if(activ == 1 && valNota <= 9.75){
            valNota += 0.25;
        }
        nota = new Nota(data, valNota, profesor);
        nota.setId(idNota);

        Nota result = (Nota) repository.save(nota);
        if(result == null){
            NotaUtila notaUtila = new NotaUtila(idTema, valNota, StructuraAnUniversitar.getWeekFromData(data),
                    serviceTema.searchTema(idTema).getDeadlineWeek(), feedback);
            fileFeedbackSaver.storeToFile(
                    serviceStudent.searchStudent(idStudent).getNume()+"_"+serviceStudent.searchStudent(idStudent).getPrenume(),
                    notaUtila);
        }
        notifyy();
        return result;
    }

    public List<NotaDTO> getAllNote(){
        Collection<Nota> collection = (Collection<Nota>) repository.findAll();
        List<Nota> list = new ArrayList<Nota>(collection);
        List<NotaDTO> listaNote = new ArrayList<>();
        for (Nota nota : list) {
            Long idStudent = (Long) nota.getId().getStudentId();
            Long idTema = (Long) nota.getId().getTemaId();
            if(serviceStudent.searchStudent(idStudent) != null && serviceTema.searchTema(idTema) != null) {
                NotaDTO notaCurenta = new NotaDTO(serviceStudent.searchStudent(idStudent).getNume()+" "
                        +serviceStudent.searchStudent(idStudent).getPrenume(),
                         serviceStudent.searchStudent(idStudent).getGrupa(),
                        serviceTema.searchTema(idTema).getDescriere(),
                        nota.getValue());

                listaNote.add(notaCurenta);
            }
        }
        return listaNote;
    }

    public List<Student> filterStudentsForHW(Long tema) {
        Collection<Nota> collection = (Collection<Nota>) repository.findAll();
        List<Nota> list = new ArrayList<Nota>(collection);
        List<Student> res =
                list.stream()
                    .filter(n -> n.getId().getTemaId() == tema)
                    .map(n -> n.getId().getStudentId())
                    .map(idSt -> serviceStudent.searchStudent((Long) idSt))
                    .collect(Collectors.toList());
        return res;
    }

    public ServiceStudent getServiceStudent() {
        return serviceStudent;
    }

    public ServiceTema getServiceTema(){
        return serviceTema;
    }

    public List<Student> filterStudentsForHWWithTeacher(Long tema, String profesor) {
        Collection<Nota> collection = (Collection<Nota>) repository.findAll();
        List<Nota> list = new ArrayList<Nota>(collection);
        List<Student> res =
                list.stream()
                        .filter(n -> n.getId().getTemaId() == tema)
                        .filter(n -> n.getProfesor().equals(profesor))
                        .map(n -> n.getId().getStudentId())
                        .map(idSt -> serviceStudent.searchStudent((Long) idSt))
                        .collect(Collectors.toList());
        return res;
    }

    public List<Nota> filterNotesFromAHWAndAWeek(Long tema, int saptamana) {
        Collection<Nota> collection = (Collection<Nota>) repository.findAll();
        List<Nota> list = new ArrayList<Nota>(collection);
        List<Nota> res =
                list.stream()
                    .filter(n -> n.getId().getTemaId() == tema)
                    .filter(n -> {return StructuraAnUniversitar.getWeekFromData(n.getData()) == saptamana;})
                    .collect(Collectors.toList());

        return res;
    }

    public List<DTOTemaMedie> filterMostDifficultHW2(){
        Collection<Nota> collection = (Collection<Nota>) repository.findAll();
        List<Nota> list = new ArrayList<Nota>(collection);
        Map<Long, Double> result =
                list.stream()
                        .collect(
                                Collectors.groupingBy(
                                        nota->nota.getId().getTemaId(), Collectors.summingDouble(Nota::getValue)
                                ));
        int number = getServiceStudent().getAllStudents().size();
        List<DTOTemaMedie> dtoTemaMedies = new ArrayList<>();
        result.entrySet().stream().forEach(x -> {
                        DTOTemaMedie elem = new DTOTemaMedie(x.getKey(), x.getValue() / number);
                        dtoTemaMedies.add(elem);
                });
       // Optional<Map.Entry<Long, Double>> minAverage = result.entrySet().stream().min((x, y)-> (int) (x.getValue() - y.getValue()));

        return dtoTemaMedies;
    }

    public Tema filterMostDifficultHW(){
        Collection<Nota> collection = (Collection<Nota>) repository.findAll();
        List<Nota> list = new ArrayList<Nota>(collection);
        Map<Long, List<Nota>> result =
                list.stream()
                        .collect(
                                Collectors.groupingBy(
                                        n->n.getId().getTemaId()
                                ));

        double medieMin = 10;
        Tema rezultat = null;

        List<Tema> temes = serviceTema.getAllTeme();
        double numitor = serviceStudent.getAllStudents().size();

        for(Tema tema: temes) {
            List<Nota> resuult = result.get(tema.getId());
            double medie = 0;
            double numarator = 0;
            if(resuult != null){
                for (Nota n : resuult) {
                    numarator += n.getValue();
                }
            }
            if (numitor != 0) {
                medie = numarator / numitor;
            }
            if (medie <= medieMin) {
                rezultat = serviceTema.searchTema(tema.getId());
                medieMin = medie;
                }
            }

        return rezultat;
    }

    public List<DTOStudentMedie> filterAverageGrade(){
        Collection<Nota> collection = (Collection<Nota>) repository.findAll();
        List<Nota> list = new ArrayList<Nota>(collection);
        Map<Long, List<Nota>> result = new HashMap<>();
        for (Student s:
             serviceStudent.getAllStudents()) {
            result.put(s.getId(), list.stream()
                                      .filter( n -> n.getId().getStudentId().equals(s.getId()) )
                                      .collect(Collectors.toList()));
        }

        List<DTOStudentMedie> rezultat = new ArrayList<>();

        List<Tema> temes = serviceTema.getAllTeme();
        result.forEach(
                (studentId,listaDeNote) -> {
                    double numarator = 0;
                    double numitor = 0;
                    for(Tema tema: temes){
                        double value = 0;
                        for (Nota nota : listaDeNote) {
                            if(tema.getId() == nota.getId().getTemaId()) {
                                value = nota.getValue();
                                break;
                            }
                        }

                        int pondere = tema.getDeadlineWeek() - tema.getStartWeek();
                        if(pondere == 0){
                            pondere = 1;
                        }
                        numarator += pondere * value;
                        numitor += pondere;
                    }
                    rezultat.add(new DTOStudentMedie(studentId, numarator/numitor));
                }
        );

        return rezultat;
    }
    public List<DTOStudentMedie> filterAcceptedStudents(){
        List<DTOStudentMedie> result =
                filterAverageGrade().stream()
                .filter(x->(x.getMedie() >= 1))
                .collect(Collectors.toList());
        return result;
    }

    public List<Student> filterPunctualStudents(){
        Collection<Nota> collection = (Collection<Nota>) repository.findAll();
        List<Nota> list = new ArrayList<Nota>(collection);
        Map<Long, List<Nota>> result =
                list.stream()
                        .collect(
                                Collectors.groupingBy(
                                        nota->nota.getId().getStudentId())
                        );

        List<Student> rezultat = new ArrayList<>();
        result.forEach(
                (studentId,listaDeNote) -> {
                    if(serviceTema.getAllTeme().size() == listaDeNote.size()) {
                        boolean ok = true;
                        for (Nota nota : listaDeNote) {
                            Tema tema = serviceTema.searchTema(nota.getId().getTemaId());
                            if (StructuraAnUniversitar.getWeekFromData(nota.getData()) > tema.getDeadlineWeek()) {
                                ok = false;
                                break;
                            }
                        }
                        if (ok == true) {
                            Student student = serviceStudent.searchStudent(studentId);
                            rezultat.add(student);
                        }
                    }
                }
        );
        return rezultat;
    }

    public List<Tema> getLipsaNota(Long idStudent) {
        List<Tema> rezultat = new ArrayList<>();
        List<Tema> allTeme = serviceTema.getAllTeme();
        Collection<Nota> collection = (Collection<Nota>) repository.findAll();
        List<Nota> allNote = new ArrayList<Nota>(collection);
        for(Tema tema : allTeme){
            boolean ok = true;
            for(Nota nota: allNote){
                if(nota.getId().getStudentId() == idStudent && nota.getId().getTemaId() == tema.getId()){
                    ok = false;
                    break;
                }
            }
            if(ok == true){
                rezultat.add(tema);
            }
        }
        return rezultat;
    }
}
