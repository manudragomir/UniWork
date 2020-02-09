class DTOAse(object):
    def __init__(self, cheie, contor):
        self.__cheie = cheie
        self.__contor = contor

    def get_cheie(self):
        return self.__cheie

    def get_contor(self):
        return self.__contor
    
    def __str__(self):
        return "Perechea de forma: " + str(self.__cheie) + " apare de " + str(self.__contor) + " ori!"

    cheie = property(get_cheie, None, None, None)
    contor = property(get_contor, None, None, None)
        
    


