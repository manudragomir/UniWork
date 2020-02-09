from domain.entities import Student
from errors.erori import ValidError

class StudentValidator(object):
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
    
    def valideazaLaborator(self, laborator):
        erori = ""
        if laborator.get_numar_laborator() < 0:
            erori += "lab invalid!\n"
            
        if laborator.get_numar_problema() <= 0:
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
        if(nota.get_mark() < 1 or nota.get_mark() > 10):
            erori += "nota invalida\n"
            
        if len(erori) > 0:
            raise ValidError(erori)

def testStudValid():
    validator = StudentValidator()
    st1 = Student(12, "Mircea", 215)
    try:
        validator.valideazaStudent(st1)
        assert True
    except ValidError as ve:
        assert False
        
    st2 = Student(-5, "", -1)
    
    try:
        validator.valideazaStudent(st2)
        assert False
    except ValidError as ve:
        assert str(ve) == "id invalid!\nnume invalid!\ngrupa invalida!\n"
        
    
testStudValid()