'''
Created on Dec 8, 2018

@author: Manuel
'''

class Triunghi(object):
    def __init__(self, l1, l2, l3):
        self.__l1 = l1
        self.__l2 = l2
        self.__l3 = l3
        
    def get_perimetru(self):
        return self.__l1 + self.__l2 + self.__l3

    def get_l1(self):
        return self.__l1


    def get_l2(self):
        return self.__l2


    def get_l3(self):
        return self.__l3


    def set_l1(self, value):
        self.__l1 = value


    def set_l2(self, value):
        self.__l2 = value


    def set_l3(self, value):
        self.__l3 = value

        
    def __str__(self):
        return str("Triunghiul cu laturile") + " " + str(self.__l1) + " " + str(self.__l2) + " " + str(self.__l3)

    def __eq__(self, other):
        return self.__l1 == other.__l1 and self.__l2 == other.__l2 and self.__l3 == other.__l3
    
def TestTriunghi():
    t1 = Triunghi(3,4,5)
    t2 = Triunghi(10,15,20)
    
    assert t1.get_l1() == 3
    assert t1.get_l2() == 4
    assert t1.get_l3() == 5
    
    t2.set_l1(3)
    t2.set_l2(4)
    t2.set_l3(5)
    
    assert t1 == t2
    
TestTriunghi()
