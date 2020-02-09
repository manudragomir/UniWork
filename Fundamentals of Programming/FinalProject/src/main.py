from ui.Console import Console
from repository.Repositories import RepoStudent, RepoLaborator, RepoNota
from validare.Validator import StudentValidator, LaboratorValidator, NotaValidator
from business.Controllers import ServiceStudent, ServiceLaborator, ServiceNota
from repository.FileRepositories import StudentFileRepository,\
    LaboratorFileRepository, NotaFileRepository

repoStudent = RepoStudent()
validStudent = StudentValidator()
serviceStudent = ServiceStudent(repoStudent, validStudent)

repoLaborator = RepoLaborator()
validLaborator = LaboratorValidator()
serviceLaborator = ServiceLaborator(repoLaborator, validLaborator)

repoNota = RepoNota()
validNota = NotaValidator()
serviceNota = ServiceNota(validNota, repoNota, repoStudent, repoLaborator)


serviceStudent.addStudent(1, "Olaru Cristian", 215)
serviceStudent.addStudent(2, "Dumitrescu George", 215)
serviceStudent.addStudent(3, "Vaida George", 215)
serviceStudent.addStudent(4, "Benga Ionut", 217)
serviceStudent.addStudent(5, "Benga Vlad", 217)
serviceStudent.addStudent(6, "Grigore Alin", 218)
serviceStudent.addStudent(7, "Dragomir Manuel", 215)
serviceStudent.addStudent(8, "Marica Andrada", 215)
serviceStudent.addStudent(9, "Rauta Milena", 218)
serviceStudent.addStudent(10, "Balinth Andrei", 219)


serviceLaborator.addLaborator(2, 1, "strings", "22.10.2015")
serviceLaborator.addLaborator(2, 2, "strings", "22.12.2015")
serviceLaborator.addLaborator(2, 3, "strings", "22.12.2015")
serviceLaborator.addLaborator(2, 4, "strings", "22.09.2015")
serviceLaborator.addLaborator(3, 1, "clase", "22.10.2016")
serviceLaborator.addLaborator(4, 1, "teste", "22.10.2017")
serviceLaborator.addLaborator(5, 1, "arhitectura", "22.11.2015")
serviceLaborator.addLaborator(6, 1, "operatii", "22.11.2015")
serviceLaborator.addLaborator(6, 2, "operatii", "22.12.2015")


serviceNota.addNota(2, 2, 1, 10)
serviceNota.addNota(3, 2, 2, 9)
serviceNota.addNota(4, 2, 2, 10)
serviceNota.addNota(6, 2, 4, 6)
serviceNota.addNota(6, 3, 1, 3)
serviceNota.addNota(7, 2, 2, 10)
serviceNota.addNota(3, 6, 1, 2)
serviceNota.addNota(6, 6, 1, 5)

c = Console(serviceStudent, serviceLaborator, serviceNota)
c.run()