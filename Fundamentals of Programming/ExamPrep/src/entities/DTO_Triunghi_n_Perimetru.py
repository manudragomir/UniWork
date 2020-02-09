'''
Created on Dec 9, 2018

@author: Manuel
'''

class DTOTrPeri(object):
    def __init__(self, perim, nr):
        self.__perim = perim
        self.__nr = nr

    def get_perim(self):
        return self.__perim
    
    def get_nr(self):
        return self.__nr

    perim = property(get_perim, None, None, None)
    
    def __str__(self):
        return "Exista " + str(self.__nr) + " triunghiuri cu perimetrul " + str(self.__perim)
