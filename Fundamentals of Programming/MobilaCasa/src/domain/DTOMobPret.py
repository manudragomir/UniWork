'''
Created on Dec 10, 2018

@author: Manuel
'''
from domain.mobila import Mobila

class DTOPret(object):
    def __init__(self, mobila, nr):
        '''
        descriere: 
            - se creeaza o instanta de tip DTOPret, care va contine
            un element de tip mobila si un numar
        args:
            - mobila - un element de tip Mobila
        return:
            -
        raises:
            -
        '''
        self.__mobila = mobila
        self.__nr = nr
        
    def get_nr(self):
        return self.__nr
    
    def get_mobila(self):
        return self.__mobila
    
    def __str__(self):
        return self.__mobila.get_denumire() + " - Sunt " + str(self.__nr) + " modele mai ieftine"


def TestDTOPret():
    mob = Mobila(25,"dulap", "dulapior", 200)
    dtos = DTOPret(mob, 5)
    assert dtos.get_nr() == 5
    assert dtos.get_mobila() == mob


TestDTOPret()