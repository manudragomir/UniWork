from domain.DTOMobPret import DTOPret
from infrastructure.Repository import RepoMobila
from domain.mobila import Mobila

class ServMobila(object):
    def __init__(self, repoMobila):
        '''
        descriere:
            Creeaza o instanta de tip ServMobila care ia un obiect de tip RepoMobila
        args: 
            -
        return:
            -
        raises:
            -
        '''
        self.__repoMobila = repoMobila
        
    def getAll(self):
        '''
        descriere:
            Functie ce are rolul de a prelua din baza de date(repository)
            entitati de tip mobila
        args: 
            -
        return:
            list_of_mobila - o lista cu entitati de tip Mobila
        raises:
            -
        '''
        list_of_mobila = self.__repoMobila.getAllMobila()
        return list_of_mobila
    
    def checkSubstring(self, substring):
        '''
        descriere:
            Functie ce cauta un substring in descrierea sau denumirea unei
            entitati de tip mobila
        args: 
            substring - un parametru de tip string, nevid
        return:
            list_of_some_mobila - o lista cu entitati de tip mobila ce au 
                                  ca substring parametru dat
        raises:
            -
        '''
        list_of_mobila = self.__repoMobila.getAllMobila()
        list_of_some_mobila = []
        
        for mobila in list_of_mobila:
            string1 = mobila.get_denumire()
            string2 = mobila.get_descriere()
            if substring in string1 or substring in string2:
                list_of_some_mobila.append(mobila)
                
        return list_of_some_mobila
    
    def makeRaportPret(self):
        '''
        descriere:
            Functie ce face un raport: pentru fiecare model, calculeaza
            cate sunt strict mai ieftine
        args: 
            -
        return:
            list_of_DTO - o lista cu elemente de tip DTOPret, ce contin
                            o entitate de tip mobila si un nr - cate sunt 
                            strict mai ieftine
        raises:
            -
        '''
        list_of_mobila = self.__repoMobila.getAllMobila()
        
        list_of_DTO = []
        
        for mobila in list_of_mobila:
            cnt = 0
            for ot_mobila in list_of_mobila:
                if ot_mobila.get_pret() < mobila.get_pret():
                    cnt += 1
            list_of_DTO.append(DTOPret(mobila, cnt))     
        
        
        list_of_DTO = sorted(list_of_DTO, key = lambda x: x.get_mobila().get_denumire(), reverse=False)
            
        return list_of_DTO   
            

def TestService():
    repo = RepoMobila("test.txt")
    serv = ServMobila(repo)
    
    #test getAll
    list_of_mobila = serv.getAll()
    assert len(list_of_mobila) == 2
    
    #test checkSubstring   
    list_of_mobila = serv.checkSubstring("El")
    assert len(list_of_mobila) == 2
    
    #test makeRaportPret
    list_of_DTO = serv.makeRaportPret()
    
    el_mob = Mobila(133,"Dulap","dulap Elvilla cu 6 rafturi",299)
    el_mob2 = Mobila(17,"Canapea Ella","canapea extensibila de 3 persoane",2199)

    assert list_of_DTO[0].get_mobila() == el_mob2
    assert list_of_DTO[1].get_mobila() == el_mob
    
    assert list_of_DTO[0].get_nr() == 1
    assert list_of_DTO[1].get_nr() == 0
    
TestService()  