from errors.Erori import ValidError, RepoError, UndoError

class Consola():    
    
    def __init__(self, servTriunghi):
        self.__servTriunghi = servTriunghi
        self.__comenzi = {
            "print": self.__PrintTriunghi,
            "add": self.__AddTriunghi,
            "pita": self.__TriunghiPitagoreice,
            "perimetre": self.__Perimetru,
            "asemenea": self.__Asemenea,
            "undo": self.__Undo
            }
        
    def __PrintTriunghi(self):
        list_of_triangles = self.__servTriunghi.getAll()
        for tr in list_of_triangles:
            print(tr)
    
    def __AddTriunghi(self):
        l1 = int(input("Latura1: "))
        l2 = int(input("Latura1: "))
        l3 = int(input("Latura1: "))
        self.__servTriunghi.adaugaTriunghi(l1,l2,l3)
      
    def __TriunghiPitagoreice(self):
        list_of_pita = self.__servTriunghi.getPitagoreice()
        print("Sunt " + str(len(list_of_pita)) + " triunghiuri pitagoreice. Acestea sunt: ")
        for el in list_of_pita:
            print(el)
    
    def __Perimetru(self):
        list_of_peri = self.__servTriunghi.getPerimetru()
        for el in list_of_peri:
            print(el)
    
    def __Asemenea(self):
        list_of_ase = self.__servTriunghi.getAsemenea()
        for el in list_of_ase:
            print(el)
    
    def __Undo(self):
        self.__servTriunghi.undoOp()
    
    def run(self):
        menuString = ""
        menuString += "print -> print\n"
        menuString += "add -> adauga triunghi\n"
        menuString += "pita -> print triunghirui pitagoreice\n"
        menuString += "perimetre -> toate perimetrele si nr de triunghi si care-s\n"
        menuString += "aria -> toate triunghiurile cu aria mai mica decat un nr citit\n"
        menuString += "asemenea -> cauta toate perechile de triunghiuri asemenea\n"
        menuString += "undo -> undo\n"
        
        while True:
            print(menuString)
            cmd = input(">> ")
            if cmd == 'exit':
                return
            elif cmd in self.__comenzi:
                try:
                    self.__comenzi[cmd]()
                except ValueError as ve:
                    print(ve)
                except ValidError as ve:
                    print(ve)
                except RepoError as re:
                    print(re)
                except UndoError as ue:
                    print(ue)
            else:
                print("Nema comanda")


