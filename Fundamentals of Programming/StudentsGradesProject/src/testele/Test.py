from valid.Validators import *
from repo.Repository import Repository
from business.Controllers import StudentControl

class Test(object):
    def __init__(self):
        self.__id = 25
        self.__nume = "Dragomir Manuel"
        self.__grupa = 21503
        self.__Student1 = Student(self.__id, self.__nume, self.__grupa)
        
        self.__nume2 = "Gigi Mihai"
        self.__grupa2 = 21503
        self.__Student2 = Student(self.__id, self.__nume2, self.__grupa2)
        
        self.__bid = -25
        self.__bnume = ""
        self.__bgrupa = -1
        self.__BStudent = Student(self.__bid, self.__bnume, self.__bgrupa)
        
        self.__nrLab = 3
        self.__nrProb = 5
        self.__descriere = "Clase"
        self.__deadline = "22.10.2017"
        self.__Laborator1 = Laborator(self.__nrLab, self.__nrProb, self.__descriere, self.__deadline)
        
        self.__bnrLab = -1
        self.__bnrProb = 1
        self.__bdescriere = ""
        self.__bdeadline = "214.213.33"
        self.__bLaborator = Laborator(self.__bnrLab, self.__bnrProb, self.__bdescriere, self.__bdeadline)
        
        self.__validator1 = StudentValidator()
        self.__validator2 = LaboratorValidator()
        
        self.__repo1 = Repository()
        self.__repo2 = Repository()
        
        self.__servStud = StudentControl(self.__validator1, self.__repo1)
        
        
    def __testStudent(self):
        assert self.__id == self.__Student1.get_id()
        assert self.__nume == self.__Student1.get_nume()
        assert self.__grupa == self.__Student1.get_grupa()
        
    def __testLaborator(self):
        assert self.__nrLab == self.__Laborator1.get_nr_lab()
        assert self.__nrProb == self.__Laborator1.get_nr_prob()
        assert self.__descriere == self.__Laborator1.get_descriere()
        assert self.__deadline == self.__Laborator1.get_deadline()
        
    def __testValidStudent(self):
        try:
            self.__validator1.valideazaStudent(self.__Student1)
        except ValidError:
            assert False
            
        try:
            self.__validator1.valideazaStudent(self.__BStudent)
            assert False
        except ValidError as ve:
            assert str(ve) == "id invalid!\nnume invalid!\ngrupa invalida!\n"                    
        
    def __testValidLaborator(self):
        try:
            self.__validator2.valideazaLaborator(self.__bLaborator)
            assert False
        except ValidError as ve:
            assert str(ve) == "lab invalid!\ndescriere invalida!\nzi invalida!\nluna invalida!\nan invalid!\n"
            
    def __testRepoStud(self):
        self.__repo1.add(self.__Student1)
        list = []
        list.append(self.__Student1)
        
        assert self.__repo1.getAll() == list
        
        self.__repo1.remove(self.__Student1)
        assert self.__repo1.getAll() == []
        
        self.__repo1.add(self.__Student1)
        list = []
        list.append(self.__Student1)
        self.__repo1.update(self.__Student2)
        assert self.__repo1.search(self.__Student2) == self.__Student2
        
    def __testRepoLab(self):
        self.__repo2.add(self.__Laborator1)
        list = []
        list.append(self.__Laborator1)
        
        assert self.__repo2.getAll() == list
        
        self.__repo2.remove(self.__Laborator1)
        assert self.__repo2.getAll() == []
        
    def __testStudentControl(self):
        self.__servStud.addStudent(id, nume, grupa)
        # student in lista
        
            
    def runtests(self):
        self.__testStudent()
        self.__testLaborator()
        self.__testValidStudent()
        self.__testValidLaborator()
        self.__testRepoStud()
        self.__testRepoLab()


