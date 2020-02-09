from domain.entities import Student, Laborator, Nota
from errors.erori import RepoError

class RepoStudent(object):
    
    def __init__(self):
        self.__studenti = []
        
    def store_studenti(self, Student):
        if Student in self.__studenti:
            raise RepoError("Exista deja studentul!")
        
        self.__studenti.append(Student)
        
    def searchById(self, idStudent):
        for student in self.__studenti:
            if student == idStudent:
                return student
            
        raise RepoError("Nu s-a gasit studentul!")
    
    def recursiveSearchById(self, idStudent, indice):
        '''recursiv'''
        if indice < 0:
            raise RepoError("NU s-a gasit studentul!")
        
        if self.__studenti[indice] == idStudent:
            return self.__studenti[indice]
        
        return self.recursiveSearchById(idStudent, indice-1)
        
            
    def delete_student(self, Student):
        if Student not in self.__studenti:
            raise RepoError("Nu exista studentul de sters!")
        
        for i in range(len(self.__studenti)):
            if self.__studenti[i] == Student:
                del self.__studenti[i]
                return
            
    def recursiveDelete(self, student, ok, indice):
        if ok == 1:
            return
        
        if indice < 0:
            raise RepoError("NU exista studentul!")
        
        if self.__studenti[indice] == student:
            ok = 1
            del self.__studenti[indice]
            return
        
        return self.recursiveDelete(student, ok, indice-1)
            
    def update_student(self, student):
        for i in range(len(self.__studenti)):
            if self.__studenti[i] == student:
                self.__studenti[i] = student
        
    
    def get_all_studenti(self):
        return self.__studenti[:]
    
    
class RepoLaborator(object):
    
    def __init__(self):
        self.__laboratoare = []
        
    def store_laboratoare(self, Laborator):
        if Laborator in self.__laboratoare:
            raise RepoError("Exista deja Laboratorul!")
        
        self.__laboratoare.append(Laborator)
        
    def update_laborator(self, laborator):
        for i in range(len(self.__laboratoare)):
            if self.__laboratoare[i] == laborator:
                self.__laboratoare[i] = laborator
                
    def delete_laborator(self, laborator):
        if laborator not in self.__laboratoare:
            raise RepoError("Nu exista laoratorul de sters!")
        
        for i in range(len(self.__laboratoare)):
            if self.__laboratoare[i] == laborator:
                del self.__laboratoare[i]
                return
        
    def searchById(self, nrlab, nrprb):
        for lab in self.__laboratoare:
            if lab.get_numar_problema() == nrprb and lab.get_numar_laborator() == nrlab:
                return lab
            
        raise RepoError("Nu s-a gasit lab!")
        
    def get_all_laboratoare(self):
        return self.__laboratoare[:]
    
    
class RepoNota(object):
    
    def __init__(self):
        self.__note = []
        
    def store_note(self, Nota):
        if Nota in self.__note:
            raise RepoError("Exista deja nota!")
        
        self.__note.append(Nota)
        
    def delete_nota(self, Value):
        for i in range(len(self.__note)):
            if self.__note[i] == Value:
                del self.__note[i]
                return
    
    def update_nota_stud(self, Student):
        for i in range(len(self.__note)):
            if self.__note[i].get_student() == Student:
                self.__note[i].set_student(Student)
    
    def update_nota_laborator(self, Laborator):
        for i in range(len(self.__note)):
            if self.__note[i].get_laborator() == Laborator:
                self.__note[i].set_laborator(Laborator)
        
    def get_all_note(self):
        return self.__note[:]

def TestDelNota():
    repoNota = RepoNota()
    st = Student(2, "mihai", 215)
    lab = Laborator(2, 2, "mihai", "22.10.2015")
    nota = Nota(2, st, lab)
    repoNota.store_note(nota)
    
    l = repoNota.get_all_note()
    assert len(l) == 1
    
    repoNota.delete_nota(st)
    
    l = repoNota.get_all_note()
    assert len(l) == 0
    

TestDelNota()

def TestRepoStudent():
    st = Student(12, "mihai", 215)
    repoSt = RepoStudent()
    repoSt.store_studenti(st)
    list = repoSt.get_all_studenti()
    assert len(list) == 1
    st = repoSt.searchById(12)
    repoSt.delete_student(st)
    list = repoSt.get_all_studenti()
    assert len(list) == 0
    
def TestSearchById():
    lab = Laborator(1,2,"strings", "22.10.2015")
    repoLab = RepoLaborator()
    repoLab.store_laboratoare(lab)
    assert repoLab.searchById(1, 2) == lab
    
    try:
        repoLab.searchById(1,1)
        assert False
    except RepoError as ve:
        assert str(ve) == "Nu s-a gasit lab!"
    

def TestDelUpdStudent():
    '''
    st = Student(1, "mihai", 215)
    repoSt = RepoStudent()
    repoSt.store_studenti(st)
    
    st1 = Student(1, "george", 217)
    repoSt.update_student(st1)
    list = repoSt.get_all_studenti()
    assert list[0].get_nume() == "george"
    
    repoSt.delete_student(st1)
    list = repoSt.get_all_studenti()
    assert len(list) == 0
    '''
    

TestRepoStudent()
TestSearchById()
TestDelUpdStudent()