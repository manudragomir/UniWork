from domain.JucatorCls import Jucator
from errors.Erori import RepoError

class RepoJucator(object):
    def __init__(self, filename):
        '''
        descriere:
            - creeaza o entitate de tip RepoJucator
        args:
            - filename - string ce reprezinta numele unui fisier
        return:
            -
        raises:
            -
        '''
        self.__filename = filename
        
    def storeJucator(self, jucator):
        '''
        descriere:
            - adauga un jucator in fisier
        args:
            - jucator - entitate de tip Jucator
        return:
            -
        raises:
            - RepoError - daca jucatorul exista deja in fisier
        '''
        
        list_of_jucatori = self.__loadFromFile()
        for juc in list_of_jucatori:
            if juc == jucator:
                raise RepoError("jucatorul este deja")
        list_of_jucatori.append(jucator)
        self.__storeToFile(list_of_jucatori)
        
    def updateJucator(self, jucator):
        '''
        descriere:
            - modifica inaltimea unui jucator
        args:
            - jucator - entitate de tip Jucator
        return:
            -
        raises:
            - RepoError - daca jucatorul nu exista in fisier
        '''
        list_of_jucatori = self.__loadFromFile()
        
        ok = 0
        for juc in list_of_jucatori:
            if juc == jucator:
                juc.set_inaltime(jucator.get_inaltime())
                ok = 1
                break
                
        if ok == 1:
            self.__storeToFile(list_of_jucatori)
            
        else:
            raise RepoError("Jucatorul nu este in baza de date!")
        
    def __storeToFile(self, list_of_jucatori):
        '''
        descriere:
            - adauga in fisier o lista de jucatori
        args:
            - list_of_jucatori - o lista cu entitati de tip Jucator
        return:
            -
        raises:
            - IOError - daca fisierul nu se poate deschide
        '''
        try:
            f = open(self.__filename, "w")
            for juc in list_of_jucatori:
                line = juc.get_nume() + "," + juc.get_prenume() + "," + str(juc.get_inaltime()) + "," + juc.get_post() + "\n"
                f.write(line)
        except IOError:
            print("Nu s-a deschis fisierul")
        finally:
            f.close()
        
    def __loadFromFile(self):
        '''
        descriere:
            - creeaza o lista cu datele din fisier
        args:
            - 
        return:
            - o lista cu jucatorii din fisier
        raises:
            - IOError - daca fisierul nu s-a putut deschide
        '''
        list_of_jucatori = []
        try:
            f = open(self.__filename, "r")
            fileline = f.readline().strip()
            while fileline != "":
                attrs = fileline.split(",")
                jucator = Jucator(attrs[0], attrs[1], int(attrs[2]), attrs[3])
                list_of_jucatori.append(jucator)
                fileline = f.readline().strip()
        except IOError:
            print("Nu s-a deschis fisierul")
        finally:
            f.close()
            
        return list_of_jucatori[:]
        
    def getAll(self):
        '''
        descriere:
            - returneaza lista cu jucatorii din fisier
        args:
            - 
        return:
            - list_of_jucatori - lista cu jucatorii
        raises:
            -
        '''
        list_of_jucatori = self.__loadFromFile()
        return list_of_jucatori[:]

def TestRepo():
    try:
        f = open("testRepo.txt", "w")
    finally:
        f.close()
        
    repo = RepoJucator("testRepo.txt")
    juc = Jucator("dr", "ma", 190,"Fundas")
    # test Store
    repo.storeJucator(juc)
    #test getAll
    list = repo.getAll()
    
    
    assert len(list) == 1
    
    juc1 = Jucator("dr", "ma", 185, "Fundas")
    
    #test Update
    repo.updateJucator(juc1)
    
    list = repo.getAll()
    
    assert list[0].get_inaltime() == 185
        
TestRepo()
