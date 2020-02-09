from domain.JucatorCls import Jucator
from errors.Erori import TeamError, RepoError
import random
from infrastructure.Repository import RepoJucator
from validare.Validatori import ValidatorJucator

class ServJucator(object):
    def __init__(self, repoJucator, validJucator):
        '''
        descriere:
            - creeaza o entitate de tip ServJucator
        args:
            - repoJucator - o entitate de tip RepoJucator
            - validJucator - o entitate de tip ValidatorJucator
        return:
            -
        raises:
            -
        '''
        self.__repoJucator = repoJucator
        self.__validJucator = validJucator
        
    def addJucator(self, nume, prenume, inaltime, post):
        '''
        descriere:
            - creeaza o entitate de tip Jucator pe care incearca apoi
            sa o adauge in RepoJucator
        args:
            - nume - string nevid
            - prenume - string nevid
            - inaltime - nr natural
            - post - Fundas, Extrema sau Pivot
        return:
            -
        raises:
            -
        '''
        jucator = Jucator(nume, prenume, inaltime, post)
        self.__validJucator.valideazaJucator(jucator)
        self.__repoJucator.storeJucator(jucator)
        
    def modificaInaltimea(self, nume, prenume, inaltime):
        '''
        descriere:
            - modifica inaltimea unui jucator
        args:
            - nume - string nevid
            - prenume - string nevid
            -inaltime - nr natural
        return:
            -
        raises:
            -
        '''
        jucator = Jucator(nume, prenume, inaltime, "Fundas")
        self.__validJucator.valideazaJucator(jucator)
        self.__repoJucator.updateJucator(jucator)
        
    def greatTeam(self):
        '''
        descriere:
            - determina o echipa formata din 2 extreme, 2 fundasi si un pivot
            cei mai inalti din fisier
        args:
            - 
        return:
            - o lista cu echipa formata din elemente de tip Jucator
        raises:
            - TeamError - daca nu se poate forma o echipa
        '''
        list_of_jucatori = self.__repoJucator.getAll()
        
        list_of_jucatori = sorted(list_of_jucatori, key = lambda x: x.get_inaltime(), reverse = True)
        
        extreme = []
        pivoti = []
        fundasi = []
        
        for juc in list_of_jucatori:
            if juc.get_post() == "Extrema":
                extreme.append(juc)
            elif juc.get_post() == "Pivot":
                pivoti.append(juc)
            elif juc.get_post() == "Fundas":
                fundasi.append(juc)
        
        if len(pivoti) < 1 or len(extreme) < 2 or len(fundasi) < 2:
            raise TeamError("NU se poate forma o echipa")
        
        else:
            list = []
            list.append(fundasi[0])
            list.append(fundasi[1])
            list.append(pivoti[0])
            list.append(extreme[0])
            list.append(extreme[1])
            return list
        
    def importaJucs(self, nume_fisier):
        '''
        descriere:
            - importa jucatori dintr-un fisier
        args:
            - nume_fisier - un string nevid
        return:
            - numarul de jucator importati
        raises:
            - IOError daca nu se poate deschide fisierul
        '''
        number = 0
        list_of_jucatori = self.__repoJucator.getAll()
        try:
            fisi = open(nume_fisier, "r")
            fileline = fisi.readline().strip()
            while fileline != "":
                attrs = fileline.split(" ")
                jucator = Jucator(attrs[0], attrs[1], random.randint(180,200), random.choice(["Fundas", "Extrema", "Pivot"]))
                if jucator not in list_of_jucatori: 
                    number = number + 1
                    self.__repoJucator.storeJucator(jucator)
                fileline = fisi.readline().strip()
                    
        except IOError:
            print("Nu s-a putut deschide fisierul")
        finally:
            fisi.close()
        
        return number
        
    def getAllJucatori(self):
        '''
        descriere:
            - returneaza lista cu jucatorii din fisier
        args:
            - 
        return:
            - list_of_jucatori - lista cu jucatorii, entitati de tip Jucator
        raises:
            -
        '''
        
        list_of_jucatori = self.__repoJucator.getAll()
        return list_of_jucatori

def TestServ():
    try:
        f = open("testServ.txt", "w")
    finally:
        f.close()
    repo = RepoJucator("testServ.txt")
    valid = ValidatorJucator()
    serv = ServJucator(repo,valid)
    
    #test add + getall
    serv.addJucator("a", "b", 180, "Fundas")
    serv.addJucator("c", "d", 181, "Fundas")
    serv.addJucator("e", "f", 182, "Pivot")
    serv.addJucator("g", "h", 183, "Extrema")
    serv.addJucator("i", "j", 184, "Extrema")
    serv.addJucator("k", "l", 185, "Extrema")
    
    list = serv.getAllJucatori()
    
    assert len(list) == 6
    
    #test team
    team = serv.greatTeam()
    assert team[4].get_inaltime() == 184
    
    #test modifica
    serv.modificaInaltimea("a", "b", 181)
    list = serv.getAllJucatori()
    
    assert list[0].get_inaltime() == 181
    
    #test importa
    nr = serv.importaJucs("testimp.txt")
    assert nr == 1
    
    
    
TestServ()