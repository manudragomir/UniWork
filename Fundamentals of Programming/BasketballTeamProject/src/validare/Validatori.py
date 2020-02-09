from errors.Erori import ValidError
from domain.JucatorCls import Jucator
class ValidatorJucator(object):
    def valideazaJucator(self, jucator):
        '''
        descriere:
            - functia verifica daca un jucator indeplineste conditiile de a fi valid
        args: 
            - o entitate de tip Jucator
        return:
            - 
        raises:
            - ValidError cu erorile pe care le are jucatorul creat
        '''
        errori = ""
        if jucator.get_nume() == "":
            errori += "nume nu poate fi vid\n"
        if jucator.get_prenume() == "":
            errori += "prenume nu poate fi vid\n"
        if jucator.get_inaltime() < 0:
            errori += "inaltimea trebuie sa fie pozitiva\n"
        if jucator.get_post() not in ["Fundas", "Extrema", "Pivot"]:
            errori += "Postul poate fi doar Fundas, Extrema si Pivot\n"
            
        if len(errori) != 0:
            raise ValidError(errori)
        
def TestValidator():
    juc = Jucator("dr", "ma", 120, "Fundas")
    valid = ValidatorJucator()
    try:
        valid.valideazaJucator(juc)
        assert True
    except:
        assert False
        
    juc1 = Jucator("", "", -5, "Atacant")
    try:
        valid.valideazaJucator(juc1)
        assert False
    except ValidError as ve:
        assert True
        
TestValidator()


