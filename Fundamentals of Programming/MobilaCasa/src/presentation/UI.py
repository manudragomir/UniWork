class Consola(object):
    
    def __init__(self, servMobila):
        self.__servMobila = servMobila
        self.__comenzi = {
            "print": self.__PrintMobila,
            "task1": self.__AfisareSubsecventa,
            "task2": self.__RaportPret
            }
        
    def __PrintMobila(self):
        list_of_mobila = self.__servMobila.getAll()
        for mobila in list_of_mobila:
            print(mobila)
    
    
    def __AfisareSubsecventa(self):
        substring = input("introdu un substring: ")
        list_of_some_mobila = self.__servMobila.checkSubstring(substring)
        
        if len(list_of_some_mobila) == 0:
            print("Nu s-a gasit in niciun model!")
            return
            
        for mobila in list_of_some_mobila:
            print(mobila)
    
    
    def __RaportPret(self):
        list_of_elements = self.__servMobila.makeRaportPret()
        
        for el in list_of_elements:
            print(el)
    
        
    def run(self):
        menuString = ""
        #menuString += "print -> Printeaza baza de date\n"
        menuString += "task1 -> task1\n"
        menuString += "task2 -> task2"
        while True:
            print(menuString)
            cmd = input(">> ")
            if cmd == 'exit':
                return
            
            elif cmd in self.__comenzi:
                self.__comenzi[cmd]()
                
            else:
                print("Comanda nu e valida!")


