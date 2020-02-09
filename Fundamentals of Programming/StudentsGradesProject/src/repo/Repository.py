from errors.Errors import RepoError

class Repository(object):
    '''
    Clasa ce are rolul de a stoca datele
    '''
    
    def __init__(self):
        self.__elems = []

    def __len__(self):
        '''
        Metoda ce returneaza nr de elemente din baza de date
        '''
        return len(self.__elems)
    
    
    def add(self, elem):
        '''
        Metoda ce adauga un element in baza de date
        '''
        if elem in self.__elems:
            raise RepoError("existing elem!")
        self.__elems.append(elem)
        
    def search(self, elem):
        '''
        Metoda ce cauta un element in baza de date
        '''
        if elem not in self.__elems:
            raise RepoError("inexisting elem!")
        
        for x in self.__elems:
            if x == elem:
                return x
            
    def searchStr(self, key, funct):
        rez = ''
        for x in self.__elems:
            if funct(x, key):
                rez += str(x)
                rez += "\n"
        return rez
            
    def update(self, elem):
        '''
        Metoda ce modifica un element din baza de date
        '''
        if elem not in self.__elems:
            raise RepoError("inexisting elem!")
        
        for i in range(len(self.__elems)):
            if self.__elems[i] == elem:
                self.__elems[i] = elem
                return
            
    def remove(self, elem):
        '''
        Metoda ce elimina un element din baza de date
        '''
        if elem not in self.__elems:
            raise RepoError("inexisting elem!")
        
        for i in range(len(self.__elems)):
            if self.__elems[i] == elem:
                del self.__elems[i]
                return
    
    def getAll(self):
        '''
        Metoda ce returneaza continutul bazei de date
        '''
        return self.__elems[:]