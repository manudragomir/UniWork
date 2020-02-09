class Student(object):
    
    def __init__(self, id, nume, grupa):
        self.id = id
        self.nume = nume
        self.grupa = grupa

    def get_id(self):
        return self.id


    def get_nume(self):
        return self.nume


    def get_grupa(self):
        return self.grupa


    def set_nume(self, value):
        self.nume = value


    def set_grupa(self, value):
        self.grupa = value
        
    def __str__(self):
        return str(self.id + " " + self.nume + " " + self.grupa)

class ProblemaLab(object):
    
    def __init__(self, nrLab, nrProb, Descriere, Data):
        self.__nrLab = nrLab
        self.__nrProb = nrProb
        self.__Descriere = Descriere
        self.__Deadline = Data

    def get_nr_lab(self):
        return self.__nrLab


    def get_nr_prob(self):
        return self.__nrProb


    def get_descriere(self):
        return self.__Descriere


    def get_deadline(self):
        return self.__Deadline


    def set_nr_lab(self, value):
        self.__nrLab = value


    def set_nr_prob(self, value):
        self.__nrProb = value


    def set_descriere(self, value):
        self.__Descriere = value    