from entities.triunghi import Triunghi
from infrastracture.Repository import RepoTriunghi
from validators.Validare import ValidTriunghi
from entities.DTO_Triunghi_n_Perimetru import DTOTrPeri
class ServTriunghi(object):
    def __init__(self, repoTriunghi, validTriunghi):
        self.__repoTriunghi = repoTriunghi
        self.__validTriunghi = validTriunghi
        
    def addTriunghi(self, a, b, c):
        '''
        Primeste laturile unui triunghi si construieste un triunghi
        
        args: a, b, c - numere intregi pozitive
        
        return: 
        
        raises: raise ValidError daca nu pot construi un triunghi cu aceste 3 laturi
        '''
        
        triunghi = Triunghi(a,b,c)
        self.__validTriunghi.valideazaTriunghi(triunghi)
        self.__repoTriunghi.store(triunghi)
        
    def getTriunghiuriPitagoreice(self):
        '''
        args: -
        
        return: returneaza o lista cu toate triunghiurile din baza de date
               care sunt pitagoreice, adica satisfac ecuatia
               a^2 + b^2 = c^2
        '''
        
        triunghiuri_pitagoreice = []
        list_of_triangles = self.getAll()
        for triangle in list_of_triangles:
            if self.__CheckPitagora(triangle):
                triunghiuri_pitagoreice.append(triangle)
                
        return triunghiuri_pitagoreice[:]
    
    def __CheckPitagora(self, triangle):
        
        '''
        Primeste un element de tip triunghi si verifica daca este pitagoreic
        
        args: triangle de tip Triunghi
        
        return:
        True -> daca e pitagoreic
        False -> daca nu e pitagoreic
        
        raises: -
        '''
        
        a = triangle.get_l1()
        b = triangle.get_l2()
        c = triangle.get_l3()
        
        if (a*a + b*b) == c*c:
            return True
        
        elif (b*b + c*c) == a*a:
            return True
       
        elif (c*c + a*a) == b*b:
            return True
        
        return False
    
    def perimetru(self):
        '''
        Preia un parametru si afiseaza toate triunghiurile din baza de date
        care au perimetru egal cu  accest parametru
        
        args:
            param - nr intreg pozitiv
            
        return: o lista de elemente de tip DTO_Triunghi_n_Perimetru
                cu perimetru egal cu param
                
        raises:
                -
        '''
        
        list = []
        list_of_triangles = self.getAll()
        
        perimetre = {}
        
        for triangle in list_of_triangles:
            perimetru_triunghi = triangle.get_perimetru()
            if perimetru_triunghi not in perimetre:
                perimetre[perimetru_triunghi] = 0
                
            perimetre[perimetru_triunghi] += 1
        
        rez = [] ; # o lista de DTO perimetru si nr de triunghiuri cu acel perimetru
        
        for contor_perimetru in perimetre:
            perimetru_actual = perimetre[contor_perimetru]
            rez.append(DTOTrPeri(contor_perimetru, perimetru_actual))
        
        rez.sort(key = lambda x: x.get_nr(), reverse = True)
        
        return rez
    
    def getAll(self):
        
        '''
        Preia lista din baza de date si o returneaza sub forma unei liste de elemente de tip Triunghi
        
        args: -
        
        return: o lista cu elemente de tip Triunghi
        
        raises: -
        '''
        list = self.__repoTriunghi.getAllTriangles()
        return list

def testAddTriunghi_and_getAll():
    '''
    repoTriunghi = RepoTriunghi("test.txt")
    validTriunghi = ValidTriunghi()
    service = ServTriunghi(repoTriunghi, validTriunghi)
    
    list = service.getAll()
    len1 = len(list)
    service.addTriunghi(8, 9, 10)
    
    list = service.getAll()
    len2 = len(list)
    assert len2 - len1 == 1
    '''
    
    
def testgetTriunghiuriPitagoreice():
    repoTriunghi = RepoTriunghi("test.txt")
    
    validTriunghi = ValidTriunghi()
    service = ServTriunghi(repoTriunghi, validTriunghi)
    
    list = service.getTriunghiuriPitagoreice()
    assert len(list) == 1

testAddTriunghi_and_getAll()
testgetTriunghiuriPitagoreice()
