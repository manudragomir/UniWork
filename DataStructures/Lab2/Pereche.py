'''
Created on Mar 18, 2019

@author: Manuel
'''

class Pereche(object):
    def __init__(self, valoare, frecventa):
        self.__valoare = valoare
        self.__frecventa = frecventa

    def get_valoare(self):
        return self.__valoare


    def get_frecventa(self):
        return self.__frecventa


    def set_valoare(self, value):
        self.__valoare = value


    def set_frecventa(self, value):
        self.__frecventa = value


    def __eq__(self, other):
        if type(other) == Pereche:
            return other.__valoare == self.__valoare
        else:
            return other == self.__valoare
        

    valoare = property(get_valoare, set_valoare, None, None)
    frecventa = property(get_frecventa, set_frecventa, None, None)
        

