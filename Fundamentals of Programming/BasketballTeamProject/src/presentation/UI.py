from errors.Erori import RepoError, ValidError, TeamError

class Consola():    
    
    def __init__(self, servJucator):
        self.__servJucator = servJucator
        self.__comenzi = {
            "add": self.__AdaugaJucator,
            "modi": self.__ModificaInaltime,
            "echipa": self.__EchipaMare,
            "importa": self.__ImportaJucatori,
            "print": self.__Afiseaza
            }
        
    def __AdaugaJucator(self):
        '''
        descriere:
            - citeste datele nume, prenume, inaltime, post
            de la tastatura si le paseaza in service
        '''
        nume = input("nume: ")
        prenume = input("prenume: ")
        inaltime = int(input("inaltime(cm): "))
        post = input("post: ")
        self.__servJucator.addJucator(nume,prenume,inaltime,post)
    
    
    def __ModificaInaltime(self):
        '''
        descriere:
            - citeste datele nume, prenume, inaltime
            de la tastatura si le paseaza in service
        '''
        nume = input("nume: ")
        prenume = input("prenume: ")
        inaltime = int(input("inaltime(cm): "))
        self.__servJucator.modificaInaltimea(nume, prenume, inaltime)
    
    
    def __EchipaMare(self):
        '''
        descriere:
            - afiseaza echipa cea mai "inalta"
        '''
        team = self.__servJucator.greatTeam()
        for pl in team:
            print(pl)
    
    
    def __ImportaJucatori(self):
        '''
        descriere:
            - citeste numele unui fisier, paseaza in service
            si apoi afiseaza cati jucatori au fost importati
        '''
        nume_fisier = input("fisier: ")
        nr = self.__servJucator.importaJucs(nume_fisier)
        print(nr)
    
    
    def __Afiseaza(self):
        '''
        descriere:
            - afiseaza toti jucatorii din fisier
        '''
        list_of_jucatori = self.__servJucator.getAllJucatori()
        for jucator in list_of_jucatori:
            print(jucator)
        
    def run(self):
        '''
        Consola aplicatiei
        '''
        menuString = ""
        menuString += "Adauga jucator -> add\n"
        menuString += "Modifica inaltimea -> modi\n"
        menuString += "Tipareste echipa -> echipa\n"
        menuString += "Importa jucatori -> importa\n"
        menuString += "Print -> print\n"
        while True:
            print(menuString)
            cmd = input(">> ")
            if cmd == 'exit':
                return
            elif cmd in self.__comenzi:
                try:
                    self.__comenzi[cmd]()
                except ValueError:
                    print("Date invalide")
                except ValidError as ve:
                    print(ve)
                except RepoError as re:
                    print(re)
                except TeamError as te:
                    print(te)
            else:
                print("Nu exista comanda")
        


