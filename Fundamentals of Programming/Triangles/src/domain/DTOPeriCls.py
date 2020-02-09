class DTOPeri():
    def __init__(self, nr, perim):
        self.__nr = nr
        self.__perim = perim

    def get_nr(self):
        return self.__nr


    def get_perim(self):
        return self.__perim

        
    def __str__(self):
        return "Numar triunghiuri cu perimetru " + str(self.__perim) + " este " + str(self.__nr)
    
    nr = property(get_nr, None, None, None)
    perim = property(get_perim, None, None, None)


