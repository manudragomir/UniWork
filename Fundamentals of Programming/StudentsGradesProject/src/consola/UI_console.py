from errors.Errors import RepoError, ValidError
from modelul import Student

class Console(object):
    
    def __init__(self, __controlStudenti, __controlLaborator):
        self.__controlStudenti = __controlStudenti
        self.__controlLaborator = __controlLaborator
        
    def __uiAddStudent(self):
        id = int(input("id: "))
        nume = input("nume: ")
        grupa = int(input("grupa: "))
        self.__controlStudenti.addStudent(id,nume,grupa)
        
    def __uiAddLaborator(self):
        nrlab = int(input("nrLab: "))
        nrpb = int(input("nrProblema: "))
        descriere = input("descriere: ")
        deadline = input("deadline: ")
        self.__controlLaborator.addLaborator(nrlab, nrpb, descriere, deadline)
        
    def __uiPrintStudenti(self):
        l = self.__controlStudenti.getAllStud()
        print("ID Nume Grupa")
        for x in l:
            print(x)
            
    def __uiPrintLaboratoare(self):
        labs = self.__controlLaborator.getAllLabs()
        print("Lab Pb Descriere Deadline")
        for x in labs:
            print(x)
            
    def __uiDelStudent(self):
        id = int(input("id stud de sters: "))
        self.__controlStudenti.delStudent(id)
    
    def __uiDelLaborator(self):
        nrLab = int(input("nr laboratorului: "))
        nrProb = int(input("nr problemei: "))
        self.__controlLaborator.delLaborator(nrLab, nrProb)

    def __uiUpdStudent(self):
        id = int(input("Vei updata studentul cu id-ul: "))
        newname = input("Noul nume: ")
        newgrupa = int(input("Noua grupa: "))
        self.__controlStudenti.updStudent(id, newname, newgrupa)
    
    def __uiUpdLaborator(self):
        nrlab = int(input("Vei updata laboratorul cu nrLab: "))
        nrpb = int(input("si nrProblema: "))
        newdescriere = input("descriere noua: ")
        newdeadline = input("deadline nou: ")
        self.__controlLaborator.updLaborator(nrlab, nrpb, newdescriere, newdeadline)
        
    def __uiSearchStud(self):
        string = input("nume: ")
        print(self.__controlStudenti.src1Student(string))
        
    def __uiSearchLab(self):
        string = input("descriere: ")
        print(self.__controlLaborator.src1Laborator(string))
        
    def run(self):
        
        menuString = 'Lista comenzi:\n'
        menuString += 'addStud -> Adauga student nou\n'
        menuString += 'addLab -> Adauga un nou laborator\n'
        menuString += 'printStuds -> Afiseaza lista de studenti\n'
        menuString += 'printLabs -> Afiseaza toate lab-urile\n'
        menuString += 'delStud -> Sterge un student existent\n'
        menuString += 'delLab -> Sterge un laborator existent\n'
        menuString += 'updateStud -> Updateaza un student\n'
        menuString += 'updateLab -> Updateaza un laborator\n'
        menuString += 'searchStud -> Cauta un student dupa un id\n'
        menuString += 'searchLab -> Cauta un laborator dupa nrlab si nrprb\n'
        
        comenzi = {"addStud": self.__uiAddStudent, "addLab": self.__uiAddLaborator, "printStuds": self.__uiPrintStudenti, "printLabs": self.__uiPrintLaboratoare, "delStud": self.__uiDelStudent, "delLab": self.__uiDelLaborator, "updateStud": self.__uiUpdStudent, "updateLab": self.__uiUpdLaborator, "searchStud": self.__uiSearchStud, "searchLab": self.__uiSearchLab}
        
        while True:
            print(menuString)
            comanda = input(">> ")
            
            if comanda == "exit":
                return 
            
            elif comanda in comenzi:
                try:
                    comenzi[comanda]()
                    print("Operatia a fost realizata cu succes!\n")
                    
                except ValueError as ve:
                    print("Valoarea numerica invalida!")
                    
                except ValidError as ve:
                    print("Valid Error!")
                    print(ve)
                    
                except RepoError as re:
                    print("Repo Error!")
                    print(re)
                    
            else:
                print("Comanda invalida!")