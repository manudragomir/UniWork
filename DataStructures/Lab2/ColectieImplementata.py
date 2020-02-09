'''
Created on Mar 18, 2019

@author: Manuel
'''

from Pereche import *

class Colectie:
    
    #construieste o colectie noua
    def __init__(self):
        self.__elems = []
        self.__dim = 0
    
    #adauga un element in colectie
    def adauga(self, e):
        if self.cauta(e) == True:
            for pair in self.__elems:
                if e == pair:
                    pair.set_frecventa(pair.get_frecventa() + 1)
        else:
            self.__elems.append(Pereche(e,1))
            
        self.__dim += 1
    
    #sterge o aparitie a elementului e din colectie
    #returneaza True daca elementul a fost sters, False altfel (daca e nu era in colectie)
    def sterge(self, e):
        if self.cauta(e) == True:
            for i in range(len(self.__elems)):
                if e == self.__elems[i]:
                    frecv = self.__elems[i].get_frecventa()
                    if frecv == 1:
                        self.__dim -= 1
                        self.__elems.pop(i)
                    else:
                        self.__elems[i].set_frecventa(frecv - 1)
                        self.__dim -= 1
                    return True
            
        else:
            return False
        
        
    
    #cauta un element e in colectie
    #returneaza True daca e apartine colectiei, False altfel
    def cauta(self, e):
        if e in self.__elems:
            return True
        return False
    
    #numara de cate ori apare un element e in colectie
    #returneaza numarul de aparitii pentru e
    def nrAparitii(self, e):
        for pair in self.__elems:
            if e == pair:
                return pair.get_frecventa()
            
        return 0    
    #returneaza dimensiunea colectiei (numarul de elemente)
    def dim(self):
        return self.__dim
    
    #returneaza True daca colectia e vida, False altfel
    def vida(self):
        if self.__dim == 0:
            return True
        return False
    
    #returneaza un IteratorColectie pentru colectie
    def iterator(self):
        return IteratorColectie(self)
    
    
class IteratorColectie:
    
    #creeaza un iterator pentru colectia c
    def __init__(self, c):
        self.__c = c
        self.__index = 0
        self.__frecv = 1
    
    #returneaza True daca iteratorul este valid, False altfel
    def valid(self):
        if self.__index < len(self.__c._Colectie__elems):
            return True
        return False
    
    #returneaza elementul curent din iterator
    def element(self):
        if self.valid() == False:
            raise ValueError()
        return self.__c._Colectie__elems[self.__index].get_valoare()
    
    #muta iteratorul la urmatorul element
    def urmator(self):
        if self.valid() == False:
            raise ValueError()
        
        if self.__frecv == self.__c._Colectie__elems[self.__index].get_frecventa():
            self.__index += 1
            self.__frecv = 1
            
        else:
            self.__frecv += 1
            
        
    
    #seteaza iteratorul la primul element
    def prim(self):
        self.__index = 0
        self.__frecv = 1