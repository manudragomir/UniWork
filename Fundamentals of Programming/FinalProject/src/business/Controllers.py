from domain.entities import Student, Laborator, Nota, NoteAvgDTO
from repository.Repositories import RepoStudent, RepoLaborator, RepoNota
from validare.Validator import StudentValidator, LaboratorValidator,\
    NotaValidator

class ServiceStudent(object):
    def __init__(self, repoStudent, validStudent):
        self.__repoStudent = repoStudent
        self.__validStudent = validStudent
        
    def addStudent(self, id, nume, grupa):
        st = Student(id, nume, grupa)
        self.__validStudent.valideazaStudent(st)
        self.__repoStudent.store_studenti(st)
        
    def searchStudent(self, nume):
        list_students = self.getAllStudenti()
        lista = []
        for student in list_students:
            if nume in student.get_nume():
                lista.append(student)
                
        return lista          
    
    def recSearchStudent(self, idStud):
        n = len(self.getAllStudenti())
        stud = self.__repoStudent.recursiveSearchById(idStud,n-1)
        return stud
        
    def getAllStudenti(self):
        list = self.__repoStudent.get_all_studenti()
        return list
    
class ServiceLaborator(object):
    def __init__(self, repoLaborator, LaboratorValidator):
        self.__repoLaborator = repoLaborator
        self.__validLaborator = LaboratorValidator
        
    def addLaborator(self, nrlab, nrpb, descriere, deadline):
        lab = Laborator(nrlab, nrpb, descriere, deadline)
        self.__validLaborator.valideazaLaborator(lab)
        self.__repoLaborator.store_laboratoare(lab)
        
    def searchLaborator(self, nume):
        list_labs = self.getAllLaboratoare()
        lista = []
        for lab in list_labs:
            if nume in lab.get_descriere():
                lista.append(lab)
        
        return lista
        
    def getAllLaboratoare(self):
        list = self.__repoLaborator.get_all_laboratoare()
        return list
        
class ServiceNota(object):
    def __init__(self, NotaValidator, repoNota, repoStudent, repoLaborator):
        self.__validNota = NotaValidator
        self.__repoNota = repoNota
        self.__repoStudent = repoStudent
        self.__repoLaborator = repoLaborator
        
    def addNota(self, idStudent, nrLab, nrPrb, mark):
        lab = self.__repoLaborator.searchById(nrLab, nrPrb)
        student = self.__repoStudent.searchById(idStudent)
        nota = Nota(mark, student, lab)
        self.__validNota.valideazaNota(nota)
        self.__repoNota.store_note(nota)
        
    def deleteStudent(self, id):
        st = Student(id, "george", 210)
        list = self.__repoNota.get_all_note()
        
        for x in list:
            if x.get_student() == id:
                self.__repoNota.delete_nota(st)
            
        self.__repoStudent.delete_student(st)
        
    def recDelStudent(self, id):
        st = Student(id, "george", 210)
        list = self.__repoNota.get_all_note()
        
        for x in list:
            if x.get_student() == id:
                self.__repoNota.delete_nota(st)
            
        n = len(self.__repoStudent.get_all_studenti())
        self.__repoStudent.recursiveDelete(st,0,n-1)
        
    def deleteLaborator(self, nrlab, nrprb):
        lab = Laborator(nrlab, nrprb, "descriere", "zz.ll.aaaa")
        list = self.__repoNota.get_all_note()
        for x in list:
            if x.get_laborator() == lab:
                self.__repoNota.delete_nota(lab)
            
        self.__repoLaborator.delete_laborator(lab)
        
        
    def updateStudent(self, id, newname, newgrupa):
        st = Student(id, newname, newgrupa)
        list = self.__repoNota.get_all_note()
        for x in list:
            if x.get_student() == id:
                self.__repoNota.update_nota_stud(st)
            
        self.__repoStudent.update_student(st)
        
    def updateLaborator(self, nrlab, nrprb, descriere, deadline):
        lab = Laborator(nrlab, nrprb, descriere, deadline)
        list = self.__repoNota.get_all_note()
        for x in list:
            if x.get_laborator() == lab:
                self.__repoNota.update_nota_laborator(lab)
            
        self.__repoLaborator.update_laborator(lab)
        
    def statistica1(self, nrlab, nrprb):
        lab = Laborator(nrlab, nrprb, "bla", "10.10.2010")
        lista_studenticunote = []
        list = self.getAllNote()
        for x in list:
            if x.get_laborator() == lab:
                lista_studenticunote.append((x.get_student(), x.get_mark()))
                
        #lista_studenticunote.sort(key = lambda x: x[0].get_nume())
        lista_studenticunote = sortMeuInsertion(lista_studenticunote[:], key = lambda x: x[0].get_nume())
        return lista_studenticunote
    
    def statistica2(self):
        # calcul complexitate
        studenti = {}
        
        note = self.__repoNota.get_all_note() # O(1)
        for nota in note: # O(N) - unde N - nr de note
            student_id = nota.get_student().get_id() # O(1)
            if student_id not in studenti: # O(M) - M - nr de studenti din lista, presupunem ca asta este o cautare liniara
                studenti[student_id] = [0,0,nota.get_student().get_nume()] # O(1)
                
            studenti[student_id][0] += 1 #O(1)
            studenti[student_id][1] += nota.get_mark() #O(1)
            
        rez = []
        
        for stud in studenti: #O(N) - unde N - e nr de studenti adaugati atnerior
            student = studenti[stud] #O(1)
            x = NoteAvgDTO(student[2], student[1]/ student[0]) #O(1)
            if x.get_avg() <= 5: 
                rez.append(x) #O(1)
        
        # omega(N)
        # teta(N*M)
        # complexitate finala max ( O(N*M), O(M) ) = O(N * M)
        return rez
    
    def statistica3(self):
        studenti = {}
        list = []
        
        note = self.__repoNota.get_all_note()
        for nota in note:
            student_id = nota.get_student().get_id()
            if student_id not in studenti:
                studenti[student_id] = 0
                
            studenti[student_id] += 1
            
        studs = self.__repoStudent.get_all_studenti()
        for student in studs:
            idstudent = student.get_id()
            if idstudent not in studenti:
                list.append(student)
                
        return list
                
        
    def getAllNote(self):
        note = self.__repoNota.get_all_note()
        return note

def sortMeuInsertion(l, *, key=None, reverse=False):
    if key == None:
        key = lambda x: x
        
    for i in range(1,len(l)):
        ind = i-1
        a = l[i]
        while ind>=0 and key(a)<key(l[ind]):
            l[ind+1] = l[ind]
            ind = ind-1
            l[ind+1] = a
            
    if(reverse == True):
        return l[::-1]
    
    return l

def getNextGap(gap): 
  
    gap = (gap * 10)//13
    if gap < 1: 
        return 1
    return gap

def sortMeuComb(l, *, key=None, reverse=False):
    if key == None:
        key = lambda x: x
    
    n = len(l)
    gap = n
    swapped = True
    while gap !=1 or swapped == 1:
        gap = getNextGap(gap)
        swapped = False
        for i in range(0, n-gap): 
            if key(l[i]) > key(l[i + gap]): 
                l[i], l[i + gap] = l[i + gap], l[i] 
                swapped = True
            
    if(reverse == True):
        return l[::-1]
    
    return l
            
def testSortInsert():
    l = [3,2,1,4]
    list = sortMeuInsertion(l[:])
    assert list == [1,2,3,4]
    assert l != [1,2,3,4]
    
    list = sortMeuInsertion(l[:], reverse=True)
    assert list == [4,3,2,1]

def testSortComb():
    l = [3,2,1,4]
    list = sortMeuComb(l[:])
    assert list == [1,2,3,4]
    assert l != [1,2,3,4]
    
    list = sortMeuComb(l[:], reverse=True)
    assert list == [4,3,2,1]
    
testSortInsert()
testSortComb()
        
def testAddStudent():
    repoSt = RepoStudent()
    valSt = StudentValidator()
    servSt = ServiceStudent(repoSt, valSt)
    servSt.addStudent(25, "mihai", 215)
    list = repoSt.get_all_studenti()
    assert len(list) == 1
    
def testAddNota():
    repoNota = RepoNota()
    repoStudent = RepoStudent()
    repoLaborator = RepoLaborator()
    validNota = NotaValidator()
    validStudent = StudentValidator()
    
    servNota = ServiceNota(validNota, repoNota, repoStudent, repoLaborator)
    student = Student(12, "Mihai", 215)
    lab = Laborator(1,2, "strings", "22.10.2015")
    repoStudent.store_studenti(student)
    repoLaborator.store_laboratoare(lab)
    servNota.addNota(12, 1, 2, 10)
    lista = repoNota.get_all_note()
    assert len(lista) == 1
    
    servStudent = ServiceStudent(repoStudent, validStudent)
    servNota.deleteStudent(12)
    list = repoStudent.get_all_studenti()
    assert len(list) == 0
    
def testDelStudent():
    pass
    
    
testDelStudent()
testAddStudent()
testAddNota()


