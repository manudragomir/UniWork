from domain.mobila import Mobila

class RepoMobila(object):
    def __init__(self, filename):
        '''
        descriere:
            - cream o clasa care are ca parametru un nume de fisier
        args: 
            -
        return:
            -
        raises:
            -
        '''
        self.__filename = filename
        
    def __loadFromFile(self):
        '''
        descriere:
            - Functie care citeste linie cu linie ce se afla in fisier
              si returneaza sub forma unei liste
        args: 
            -
        return:
            - list_of_mobila - elemente de tip mobila gasite in fisier
        raises:
            -
        '''
        list_of_mobila = []
        try:
            f = open(self.__filename, "r")
            fileline = f.readline().strip()
            while fileline != "":
                attrs = fileline.split(",")
                ob_mobila = Mobila(int(attrs[0]), attrs[1], attrs[2], int(attrs[3]))
                list_of_mobila.append(ob_mobila)
                fileline = f.readline().strip()
        except IOError:
            print("fisierul nu a putut fi deschis")
        finally:
            f.close()
        return list_of_mobila[:]
    
    def getAllMobila(self):
        '''
        descriere:
            - Functie care preia entitatile de tip mobila citite din fisier
              si le returneaza
        args: 
            -
        return:
            - list_of_mobila - elemente de tip mobila
        raises:
            -
        '''
        list_of_mobila = self.__loadFromFile()
        return list_of_mobila[:]
    
def TestGetMobila():
    repoMobila = RepoMobila("test.txt")
    
    list = repoMobila.getAllMobila()
    assert len(list) == 2
    
TestGetMobila()

