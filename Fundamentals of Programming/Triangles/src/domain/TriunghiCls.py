class Triunghi():
    def __init__(self, a, b, c):
        self.__l1 = a
        self.__l2 = b
        self.__l3 = c
        
    def get_perim(self):
        return self.__l1 + self.__l2 + self.__l3

    def get_l1(self):
        return self.__l1


    def get_l2(self):
        return self.__l2


    def get_l3(self):
        return self.__l3
    
    def __eq__(self, ot):
        return self.__l1 == ot.get_l1() and self.__l2 == ot.get_l2() and self.__l3 == ot.get_l3()
    
    def __str__(self):
        return "Triunghiul cu laturile: " + str(self.__l1) + "," + str(self.__l2) + "," + str(self.__l3)

    l1 = property(get_l1, None, None, None)
    l2 = property(get_l2, None, None, None)
    l3 = property(get_l3, None, None, None)
    
def TestTriunghi():
    tr = Triunghi(2,3,4)
    assert tr.get_l1() == 2
    assert tr.get_l2() == 3
    assert tr.get_l3() == 4
    
    tr1 = Triunghi(2,3,4)
    assert tr == tr1
    
TestTriunghi()
        
    


