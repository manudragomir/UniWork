from validators.Validare import ValidError
from infrastracture.Repository import RepoError

class Console(object):
    def __init__(self, servTriunghi):
        self.__servTriunghi = servTriunghi
        self.__comenzi = {
            "addTriunghi": self.__uiAddTriunghi,
            "trinotdeg": self.__uiFiltreazaTriunghiuriNedegenerate,
            "tripit": self.__uiFiltreazaTriunghiuriPitagoreice,
            "perimetru": self.__uiPerimTriunghi,
            "aria": self.__uiAriaTriunghi,
            "print": self.__uiPrintTriunghiuri
            }
        
    def __uiAddTriunghi(self):
        a = int(input("latura 1: "))
        b = int(input("latura 2: "))
        c = int(input("latura 3: "))
        self.__servTriunghi.addTriunghi(a,b,c)

    def __uiFiltreazaTriunghiuriNedegenerate(self):
        pass
    
    
    def __uiFiltreazaTriunghiuriPitagoreice(self):
        list_of_triangles = self.__servTriunghi.getTriunghiuriPitagoreice()
        for triangle in list_of_triangles:
            print(triangle)
            
        if len(list_of_triangles) == 0:
            print("Canci triunghiuri")
    
    
    def __uiPerimTriunghi(self):
        list_of_triangles = self.__servTriunghi.perimetru()
        
        for elems in list_of_triangles:
            print(elems)
            list = self.__servTriunghi.getAll()
            for triunghi in list:
                if triunghi.get_perimetru() == elems.get_perim():
                    print(triunghi)
            print("\n")
    
    
    def __uiAriaTriunghi(self):
        pass
    
    def __uiPrintTriunghiuri(self):
        list = self.__servTriunghi.getAll()
        cnt = 1
        for el in list:
            print(str(cnt) + " -> " + str(el))
            cnt += 1

    def run(self):
        while True:
            cmd = input("introdu comanda: ")
            if cmd == 'exit':
                return
            elif cmd in self.__comenzi:
                try:
                    self.__comenzi[cmd]()
                except ValueError as ve:
                    print("Date invalide")
                    print(ve)
                except ValidError as ve1:
                    print("Triunghiul este degenerat")
                    print(ve1)
                except RepoError as ve2:
                    print("Triunghiul se afla deja in baza noastra de date")
            else: 
                print("Comanda invalida")
            


