from repository.Repositories import RepoStudent, RepoLaborator, RepoNota
from domain.entities import Student, Laborator, Nota
from errors.erori import FileRepoError

class StudentFileRepository(RepoStudent):
    def __init__(self, fileName="students.txt"):
        RepoStudent.__init__(self)
        self.__fName = fileName
    
    def store_studenti(self, student):
        RepoStudent.store_studenti(self, student)
        self.__storeToFile()
    
    def delete_student(self, student):
        RepoStudent.delete_student(self, student)
        self.__storeToFile()        
    
    def update_student(self, student):
        RepoStudent.update_student(self, student)
        self.__storeToFile()
        
    def searchById(self, idStudent):
        return RepoStudent.searchById(self, idStudent)
    
    def __loadFromFile(self):
        try:
            f = open(self.__fName, "r")
            line = f.readline().strip()
            while line != "":
                attrs = line.split(";")
                student = Student(attrs[0], attrs[1], attrs[2])
                RepoStudent.store_studenti(self, student)
                line = f.readline().strip()
        except IOError:
            raise FileRepoError()
        finally:
            f.close()
        
    def __storeToFile(self):
        f = open(self.__fName, "w")
        sts = RepoStudent.get_all_studenti(self)
        for st in sts:
            strf = str(st.get_id()) + ";" + str(st.get_nume()) + ";" + str(st.get_grupa())
            strf = strf + "\n"
            f.write(strf)
        f.close()
        
    def __appendToFile(self, st):
        f = open(self.__fName, "a")
        strf = str(st.get_id()) + ";" + str(st.get_nume()) + ";" + str(st.get_grupa())
        f.write(strf)
        f.close()
        
    def get_all_studenti(self):
        students = []
        try:
            f = open(self.__fName, "r")
            line = f.readline().strip()
            while line != "":
                attrs = line.split(";")
                student = Student(attrs[0], attrs[1], attrs[2])
                students.append(student)
                line = f.readline().strip()
        except IOError:
            raise FileRepoError()
        finally:
            f.close()
            
        return students
    
def TestFileStudenti():
    x = StudentFileRepository("test.txt")
    st = Student(13, "alin", 200)
    x.store_studenti(st)
    l = x.get_all_studenti()
    assert len(l) == 1
    x.delete_student(13)
    l = x.get_all_studenti()
    assert len(l) == 0
    
TestFileStudenti()
            
        
class LaboratorFileRepository(RepoLaborator):
    def __init__(self, fileName="labs.txt"):
        RepoLaborator.__init__(self)
        self.__fName = fileName
    
    def store_laboratoare(self, laborator):
        RepoLaborator.store_laboratoare(self, laborator)
        self.__storeToFile()
    
    def delete_laborator(self, laborator):
        RepoLaborator.delete_laborator(self, laborator)
        self.__storeToFile()        
    
    def update_laborator(self, laborator):
        RepoLaborator.update_laborator(self, laborator)
        self.__storeToFile()
        
    def searchById(self, nrlab, nrprb):
        return RepoLaborator.searchById(self, nrlab, nrprb)
    
    def __loadFromFile(self):
        try:
            f = open(self.__fName, "r")
            line = f.readline().strip()
            while line != "":
                attrs = line.split(";")
                lab = Laborator(attrs[0], attrs[1], attrs[2], attrs[3])
                RepoLaborator.store_laboratoare(self, lab)
                line = f.readline().strip()
        except IOError:
            raise FileRepoError()
        finally:
            f.close()
        
    def __storeToFile(self):
        f = open(self.__fName, "w")
        labs = RepoLaborator.get_all_laboratoare(self)
        for lab in labs:
            strf = str(lab.get_numar_laborator()) + ";" + str(lab.get_numar_problema()) + ";" + str(lab.get_descriere()) + ';' + str(lab.get_deadline())
            strf = strf + "\n"
            f.write(strf)
        f.close()
        
    def get_all_laboratoare(self):
        labs = []
        try:
            f = open(self.__fName, "r")
            line = f.readline().strip()
            while line != "":
                attrs = line.split(";")
                lab = Laborator(attrs[0], attrs[1], attrs[2], attrs[3])
                labs.append(lab)
                line = f.readline().strip()
        except IOError:
            raise FileRepoError()
        finally:
            f.close() 
            
        return labs
        
class NotaFileRepository(RepoNota):
    def __init__(self, studentRepo, laboratorRepo, fileName="note.txt"):
        RepoNota.__init__(self)
        self.__studentRepo = studentRepo
        self.__laboratorRepo = laboratorRepo
        self.__fName = fileName
        #self.__loadFromFile()
    
    def store_note(self, nota):
        RepoNota.store_note(self, nota)
        self.__storeToFile()
    
    def __loadFromFile(self):
        try:
            f = open(self.__fName, "r")
        except IOError:
            raise FileRepoError()()

        line = f.readline().strip()
        while line != "":
            attrs = line.split(";")
            student = self.__studentRepo.searchById(int(attrs[1]))
            laborator = self.__laboratorRepo.searchById(int(attrs[2]), int(attrs[3]))
            nota = Nota(int(attrs[0]), student, laborator)
            RepoNota.store_note(self, nota)
            line = f.readline().strip()
        f.close()
        
    def __storeToFile(self):
        f = open(self.__fName, "w")
        gradeList = RepoNota.get_all_note(self)
        for grade in gradeList:
            gradeStr = str(grade.get_mark()) + ";" + str(grade.get_student().get_id()) + ";" + str(grade.get_laborator().get_numar_laborator()) + ";" + str(grade.get_laborator().get_numar_problema()) + "\n"
            f.write(gradeStr)
        f.close()
    
    def get_all_note(self):
        note = []
        try:
            f = open(self.__fName, "r")
        except IOError:
            raise FileRepoError()()

        line = f.readline().strip()
        while line != "":
            attrs = line.split(";")
            student = self.__studentRepo.searchById(int(attrs[1]))
            laborator = self.__laboratorRepo.searchById(int(attrs[2]), int(attrs[3]))
            nota = Nota(int(attrs[0]), student, laborator)
            note.append(nota)
            line = f.readline().strip()
        f.close()
        return note
        

    
