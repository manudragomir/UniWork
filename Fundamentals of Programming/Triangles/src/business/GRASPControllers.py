from domain.TriunghiCls import Triunghi
from domain.DTOPeriCls import DTOPeri
from domain.DTOAseCls import DTOAse

class ServTriunghi(object):
    def __init__(self, repoTriunghi, validTriunghi):
        self.__repoTriunghi = repoTriunghi
        self.__validTriunghi = validTriunghi
        
    def undoOp(self):
        self.__repoTriunghi.undoStep()
        
    def getAll(self):
        list_of_triangles = self.__repoTriunghi.getAllTriunghi()
        return list_of_triangles[:]
    
    def adaugaTriunghi(self, l1, l2, l3):
        triunghi = Triunghi(l1,l2,l3)
        self.__validTriunghi.valideazaTriunghi(triunghi)
        self.__repoTriunghi.storeTriunghi(triunghi)
        
    def getPitagoreice(self):
        list_of_triangles = self.__repoTriunghi.getAllTriunghi()
        list_of_pita = []
        for triunghi in list_of_triangles:
            if self.__CheckPitagoreic(triunghi) == True:
                list_of_pita.append(triunghi)
                
        return list_of_pita[:]
                
                
    def __CheckPitagoreic(self, triunghi):
        a = triunghi.get_l1()
        b = triunghi.get_l2()
        c = triunghi.get_l3()
        
        if a > b:
            aux = a
            a = b
            b = aux
            
        if b > c:
            aux = b
            b = c
            c = aux
            
        if a > c:
            aux = a
            a = c
            c = aux
            
        if a * a + b * b == c * c:
            return True
        
        return False
    
    def getPerimetru(self):
        '''list = []
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
        '''
        list_of_triangles = self.__repoTriunghi.getAllTriunghi()
        perimetre = {}
        
        for triangle in list_of_triangles:
            perimetru_triunghi = triangle.get_perim()
            if perimetru_triunghi not in perimetre:
                perimetre[perimetru_triunghi] = 0
                
            perimetre[perimetru_triunghi] += 1
            
        list_of_DTOs = []

        for perimetru_actual in perimetre:
            contor_actual = perimetre[perimetru_actual]
            list_of_DTOs.append(DTOPeri(contor_actual,perimetru_actual))
            
        list_of_DTOs.sort(key = lambda x: x.get_nr(), reverse = True)
        
        return list_of_DTOs[:]
    
    def getAsemenea(self):
        
        list_of_triangles = self.__repoTriunghi.getAllTriunghi()
        asemenea = {}
        
        for tr in list_of_triangles:
            (l1, l2, l3) = (tr.get_l1(), tr.get_l2(), tr.get_l3())
            x = self.__cmmdc(l1,self.__cmmdc(l2,l3))
            (l1, l2, l3) = (l1/x, l2/x, l3/x)
            if (l1,l2,l3) not in asemenea:
                asemenea[(l1,l2,l3)] = 0
            asemenea[(l1,l2,l3)] += 1
            
        list = []
        for chei in asemenea:
            cnt = asemenea[chei]
            list.append(DTOAse(chei,cnt))
            
        return list[:]
            
    def __cmmdc(self, a, b):
        while b:
            r = a % b
            a = b
            b = r
            
        return a
            