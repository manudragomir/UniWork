from modelul.Student import Student
from modelul.Laborator import Laborator
from modelul.Nota import Nota

class StudentControl(object):
    
    def __init__(self, __repoStudent, __validatorStudent):
        self.__repoStudent = __repoStudent
        self.__validatorStudent = __validatorStudent
        
    def addStudent(self, id, nume, grupa):
        '''
        Functie ce valideaza un student si apoi il adauga in baza de date specifica
        '''
        st = Student(id,nume,grupa)
        self.__validatorStudent.valideazaStudent(st)
        self.__repoStudent.add(st)
        
    def delStudent(self, id):
        st = Student(id, "Nume", 200)
        self.__validatorStudent.valideazaStudent(st)
        self.__repoStudent.remove(st)
        
    def updStudent(self, id, nume, grupa):
        st = Student(id,nume,grupa)
        self.__validatorStudent.valideazaStudent(st)
        self.__repoStudent.update(st)
        
    def srcStudent(self, string):
        rez = ''
        list = self.__repoStudent.getAll()
        
        for x in list:
            numele_stud = x.get_nume()
            if string in numele_stud:
                rez += numele_stud
                rez += '\n'
                
        return rez
        
    def src1Student(self, string):
        return self.__repoStudent.searchStr(string, functionEqualityStudents)
        
    def getAllStud(self):
        return self.__repoStudent.getAll()
    
def functionEqualityStudents(Student1, key):
    return key in Student1.get_nume()

def functionEqualityLabs(Lab1, key):
    return key in Lab1.get_descriere()
    
class LaboratorControl(object):
    
    def __init__(self, __repoLaborator, __validatorLaborator):
        self.__repoLaborator = __repoLaborator
        self.__validatorLaborator = __validatorLaborator
        
    def addLaborator(self, nrLab, nrProb, descriere, data):
        '''
        Functie ce valideaza un laborator si apoi il adauga in baza de date specifica
        '''
        lab = Laborator(nrLab, nrProb, descriere, data)
        self.__validatorLaborator.valideazaLaborator(lab)
        self.__repoLaborator.add(lab)
        
    def delLaborator(self, nrLab, nrProb):
        '''
        Functie ce sterge un laborator
        '''
        lab = Laborator(nrLab, nrProb, "Salut", "20.10.2015")
        self.__validatorLaborator.valideazaLaborator(lab)
        self.__repoLaborator.remove(lab)
        
    def updLaborator(self, nrLab, nrProb, descriere, data):
        lab = Laborator(nrLab, nrProb, descriere, data)
        self.__validatorLaborator.valideazaLaborator(lab)
        return self.__repoLaborator.update(lab)
        
    def srcLaborator(self, string):
        rez = ''
        list = self.__repoLaborator.getAll()
        
        for x in list:
            desc_lab = x.get_descriere()
            if string in desc_lab:
                rez += desc_lab
                rez += '\n'
                
        return rez
    
    def src1Laborator(self, string):
        return self.__repoLaborator.searchStr(string, functionEqualityLabs)
              
    def getAllLabs(self):
        return self.__repoLaborator.getAll()
    

class NotaControl(object):
    def __init__(self, __validatorNota, __repoNota, __repoStudent, __repoLaborator):
        self.__validatorNota = __validatorNota
        self.__repoStudent = __repoStudent
        self.__repoNota = __repoNota
        self.__repoLaborator = __repoLaborator

    def addNota(self, nota, student, laborator):
        grade = Nota(nota,student,laborator)
        self.__validatorNota.valideazaNota(grade)
        