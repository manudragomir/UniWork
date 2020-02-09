class Jucator():
    def __init__(self, nume, prenume, inaltime, post):
        '''
        descriere:
            - creeaza o entitate de tip Jucator
        args: 
            - nume - string
            - prenume - string
            - inaltime - nr natural
            - post - Fundas, Extrema, Pivot
        return:
            - 
        raises:
            - 
        '''
        self.__nume = nume
        self.__prenume = prenume
        self.__inaltime = inaltime
        self.__post = post
        
    def __eq__(self, other):
        '''
        descriere:
            - verifica daca doua entitati de tip jucator sunt egale
        args: 
            - self si other - de tip Jucator
        return:
            - True - daca sunt egale
            - False - altfel
        raises:
            - 
        '''
        return self.__nume == other.__nume and self.__prenume == other.__prenume
    
    def __str__(self):
        '''
        Modul de afisare
        '''
        return self.__prenume + " " + self.__nume + " " + self.__post + " " + str(self.__inaltime)

    def get_nume(self):
        '''
        returneaza numele Jucatorului
        '''
        return self.__nume


    def get_prenume(self):
        '''
        returneaza prenumele Jucatorului
        '''
        return self.__prenume


    def get_inaltime(self):
        '''
        returneaza inaltimea Jucatorului
        '''
        return self.__inaltime


    def get_post(self):
        '''
        returneaza postul Jucatorului
        '''
        return self.__post


    def set_inaltime(self, value):
        self.__inaltime = value

    nume = property(get_nume, None, None, None)
    prenume = property(get_prenume, None, None, None)
    inaltime = property(get_inaltime, set_inaltime, None, None)
    post = property(get_post, None, None, None)

def TestJucator():
    player = Jucator("dr", "ma", 180, "Fundas")
    assert player.get_nume() == "dr"
    assert player.get_prenume() == "ma"
    assert player.get_inaltime() == 180
    assert player.get_post() == "Fundas"
    
    player2 = Jucator("dr", "ma", 190, "Extrema")
    assert player == player2

TestJucator()

