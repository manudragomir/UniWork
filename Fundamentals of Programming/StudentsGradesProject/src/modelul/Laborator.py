class Laborator(object):
    
    def __init__(self, nrLab, nrProb, descriere, deadline):
        self.__nrLab = nrLab
        self.__nrProb = nrProb
        self.__descriere = descriere
        self.__deadline = deadline
        
    def __str__(self):
        return str(self.__nrLab)  + " " + str(self.__nrProb) + " " + str(self.__descriere) + " " + str(self.__deadline)
    
    def __eq__(self, other):
        return self.__nrLab == other.__nrLab and self.__nrProb == other.__nrProb

    def get_nr_lab(self):
        return self.__nrLab
    

    def get_nr_prob(self):
        return self.__nrProb


    def get_descriere(self):
        return self.__descriere


    def get_deadline(self):
        return self.__deadline


    def set_descriere(self, value):
        self.__descriere = value 
        
    def set_deadline(self, value):
        self.__descriere = value