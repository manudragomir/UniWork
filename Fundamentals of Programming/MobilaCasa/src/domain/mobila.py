'''
Created on Dec 10, 2018

@author: Manuel
'''

class Mobila(object):
    def __init__(self, id, denumire, descriere, pret):
        '''
        descriere:
            - Se creeaza o instanta mobila ce are 4 parametri
        args: 
            - id - nr natural nenul, unic identificabil
            - denumire - string nevid
            - descriere - string nevid
            - pret - nr natural nenul
        return:
            - 
        raises:
            -
        '''
        self.__id = id
        self.__denumire = denumire
        self.__descriere = descriere
        self.__pret = pret

    def __str__(self):
        return str(self.__id) + "," + self.__denumire + "," + self.__descriere + "," + str(self.__pret)


    def __eq__(self, other):
        return self.__id == other.__id


    def get_id(self):
        return self.__id


    def get_denumire(self):
        return self.__denumire


    def get_descriere(self):
        return self.__descriere


    def get_pret(self):
        return self.__pret
        

def TestObiectMobila():
    mob = Mobila(133, "dulap", "dulapior", 200)
    assert mob.get_id() == 133
    assert mob.get_denumire() == "dulap"
    assert mob.get_descriere() == "dulapior"
    assert mob.get_pret() == 200
    
    mob2 = Mobila(150, "dulapul", "dulapiorul", 215)
    assert mob2.get_id() == 150
    assert mob2.get_denumire() == "dulapul"
    assert mob2.get_descriere() == "dulapiorul"
    assert mob2.get_pret() == 215
    
    mob1 = Mobila(133, "lala", "lalalal", 205)
    assert mob == mob1


TestObiectMobila()

