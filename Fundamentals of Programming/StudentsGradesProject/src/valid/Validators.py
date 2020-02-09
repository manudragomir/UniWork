from errors.Errors import ValidError
from modelul.Laborator import Laborator
from modelul.Student import Student
from modelul.Nota import Nota

class StudentValidator(object):
    '''
    Clasa care are rolul de a valida un student
    id - nr natural > 0
    nume - string nevid
    grupa - nr natural > 0
    '''
    def valideazaStudent(self, student):
        erori = ""
        if student.get_id() < 0:
            erori += "id invalid!\n"
            
        if student.get_nume() == "":
            erori += "nume invalid!\n"
            
        if student.get_grupa() < 0:
            erori += "grupa invalida!\n"
            
        if len(erori) > 0:
            raise ValidError(erori)

class LaboratorValidator(object):
    '''
    Clasa care are rolul de a valida un laborator
    numar - nr natural > 0
    problema - nr natural > 0
    descriere - string nevid
    deadline - format de tipul zz.ll.aaaa
    
    '''
    def valideazaLaborator(self, laborator):
        erori = ""
        if laborator.get_nr_lab() < 0:
            erori += "lab invalid!\n"
            
        if laborator.get_nr_prob() <= 0:
            erori += "problema invalid!\n"
            
        if laborator.get_descriere() == "":
            erori += "descriere invalida!\n"
            
        s = laborator.get_deadline()
        params = s.split(".")
        
        if(len(params) > 3):
            erori += "format invalid!\n"
        
        zi = int(params[0])
        luna = int(params[1])
        an = int(params[2])
        
        if zi < 1 or zi > 31:
            erori += "zi invalida!\n"
            
        if luna < 1 or luna > 12:
            erori += "luna invalida!\n"
            
        if an < 2000 or an > 2020:
            erori += "an invalid!\n"
            
            
        if len(erori) > 0:
            raise ValidError(erori)

class NotaValidator(object):
    def valideazaNota(self, nota):
        erori = ""
        if(nota.get_valoare() < 1 or nota.get_valoare > 10):
            erori += "nota invalida\n"
            
        if len(erori) > 0:
            raise ValidError(erori)


