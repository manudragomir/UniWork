from validare.Validator import NotaValidator, LaboratorValidator, StudentValidator
from errors.erori import ValidError, RepoError, FileRepoError

class Console(object):
    def __init__(self, serviceStudent, serviceLaborator, serviceNota):
        self.__serviceStudent = serviceStudent
        self.__serviceLaborator = serviceLaborator
        self.__serviceNota = serviceNota
        self.__commands = {
            "addStudent": self.__uiAddStudent,
            "delStudent": self.__uiDelStudent,
            "updStudent": self.__uiUpdStudent,
            "srcStudent": self.__uiSrcStudent,
            
            "srcRec": self.__uiSrcRec,
            "delRec": self.__uiDelRec,
            
            "addLaborator": self.__uiAddLaborator,
            "delLaborator": self.__uiDelLaborator,
            "updLaborator": self.__uiUpdLaborator,
            "srcLaborator": self.__uiSrcLaborator,
            
            "addNota": self.__uiAddNota,
            
            "printStudenti": self.__uiPrintStudenti,
            "printLabs": self.__uiPrintLaboratoare,
            "printNote":  self.__uiPrintNote,
            
            "stat1" : self.__uiStat1,
            "stat2" : self.__uiStat2,
            "stat3" : self.__uiStat3
            }
        
    def __uiAddStudent(self):
        id = int(input("id: "))
        nume = input("nume: ")
        grupa = int(input("grupa: "))
        self.__serviceStudent.addStudent(id,nume,grupa)
        
    def __uiSrcRec(self):
        id = int(input("id: "))
        el = self.__serviceStudent.recSearchStudent(id)
        print(el)
        
    def __uiDelRec(self):
        id = int(input("id: "))
        self.__serviceNota.recDelStudent(id)
        
    def __uiAddLaborator(self):
        nrlab = int(input("nrLab: "))
        nrpb = int(input("nrProblema: "))
        descriere = input("descriere: ")
        deadline = input("deadline: ")
        self.__serviceLaborator.addLaborator(nrlab, nrpb, descriere, deadline)
    
    def __uiAddNota(self):
        idstud = int(input("id student: "))
        nrlab = int(input("nrLab: "))
        nrpb = int(input("nrProblema: "))
        nota = int(input("nota: "))
        self.__serviceNota.addNota(idstud, nrlab, nrpb, nota)
        
    def __uiPrintStudenti(self):
        list_students = self.__serviceStudent.getAllStudenti()
        print("ID     Nume     Grupa")
        for x in list_students:
            print(x)
            
            
    def __uiPrintLaboratoare(self):
        labs = self.__serviceLaborator.getAllLaboratoare()
        print("Lab Pb Descriere Deadline")
        for x in labs:
            print(x)
            
    def __uiPrintNote(self):
        note = self.__serviceNota.getAllNote()
        for x in note:
            print(x)
        
    def __uiSrcStudent(self):
        nume = input("numele cautat: ")
        studenti = self.__serviceStudent.searchStudent(nume)
        for x in studenti:
            print(x)
        
    def __uiSrcLaborator(self):
        nume = input("lab-ul cautat: ")
        laburi = self.__serviceLaborator.searchLaborator(nume)
        for x in laburi:
            print(x)
        
    def __uiDelStudent(self):
        id = int(input("id: "))
        self.__serviceNota.deleteStudent(id)
        
    def __uiDelLaborator(self):
        nrlab = int(input("nrlab: "))
        nrprb = int(input("nrprb: "))
        self.__serviceNota.deleteLaborator(nrlab, nrprb)
    
    def __uiUpdStudent(self):
        id = int(input("id: "))
        newname = input("nume: ")
        newgrupa = int(input("grupa: "))
        self.__serviceNota.updateStudent(id, newname, newgrupa)
    
    def __uiUpdLaborator(self):
        nrlab = int(input("nrLab: "))
        nrprb = int(input("nrProblema: "))
        descriere = input("descriere: ")
        deadline = input("deadline: ")
        self.__serviceNota.updateLaborator(nrlab,nrprb,descriere,deadline)
        
    def __uiStat1(self):
        nrlab = int(input("nrlab: "))
        nrprb = int(input("nrprb: "))
        lista = self.__serviceNota.statistica1(nrlab, nrprb)
        for x in lista:
            print(str(x[0].get_nume()) + " a luat nota " + str(x[1]))
            
    def __uiStat2(self):
        list = self.__serviceNota.statistica2()
        for x in list:
            print(x)
            
    def __uiStat3(self):
        list = self.__serviceNota.statistica3()
        for x in list:
            print(x)
        
    def run(self):
        menuString = ""
        menuString += "Lista comenzi:\n"
        
        menuString += "Adauga un student nou -> addStudent\n"
        menuString += "Adauga un laborator nou -> addLaborator\n"
        menuString += "Adauga o nota noua -> addNota\n"
        
        menuString += "Sterge un student -> delStudent\n"
        menuString += "Sterge un laborator -> delLaborator\n"
        
        menuString += "Actualizeaza un student -> updStudent\n"
        menuString += "Actualizeaza un laborator -> updLaborator\n"
        
        menuString += "Cauta un student -> srcStudent\n"
        menuString += "Cauta un laborator -> srcLaborator\n"
        
        menuString += "Printeaza studenti -> printStudenti\n"
        menuString += "Printeaza laboratoarele -> printLabs\n"
        menuString += "Printeaza notele -> printNote\n"
        
        menuString += "Notele stud la un lab -> stat1\n"
        menuString += "Media notelor de laborator mai mic decat 5 -> stat2\n"
        menuString += "toti X fara Y -> stat3\n"
        
        menuString += "recursiv1 - srcRec\n"
        menuString += "recursiv2 - delRec"
        
        while True:
            print("\n" + str(menuString))
            
            comanda = input(">> ")
            if comanda == 'exit':
                return
            elif comanda in self.__commands:
                try:
                    self.__commands[comanda]()
                    
                except ValueError:
                    print("tipul de date e invalid!")
                    
                except ValidError as ve:
                    print("Eroare de validare!")
                    print(ve)
                    
                except RepoError as ve:
                    print("Eroare in repository!")
                    print(ve)
                    
                except FileRepoError as ve:
                    print("Eroare la crearea fisierului!")
                    print(ve)
            else:
                print("Comanda invalida boss")


