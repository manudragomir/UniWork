from entities.triunghi import Triunghi

class ValidError(Exception):
    pass

class ValidTriunghi(object):
    def __init__(self):
        pass
    
    def valideazaTriunghi(self, triunghi):
        '''
        Functie care primeste 3 laturi intr-un triunghi si valideaza daca acela chiar
        este un triunghi
        
        args: 
            triunghi - un element de tip Triunghi
        
        return: 
            -
        
        raises: 
            ValidError - daca nu respecta inegalitatea triunghiului 
        '''
    
        a = triunghi.get_l1()
        b = triunghi.get_l2()
        c = triunghi.get_l3()
        
        if a + b <= c or  b + c <= a or a + c <= b:
            raise ValidError


def testValideazaTriunghi():
    validator = ValidTriunghi()
    
    tr = Triunghi(3,4,5)
    tr2 = Triunghi(1,2,7)
    
    try:
        validator.valideazaTriunghi(tr)
        assert True
    except:
        assert False
        
    try:
        validator.valideazaTriunghi(tr2)
        assert False
    except ValidError:
        assert True


testValideazaTriunghi()