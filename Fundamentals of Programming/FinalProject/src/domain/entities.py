class Student(object):

    def __init__(self, id, nume, grupa):
        self.__id = id
        self.__nume = nume
        self.__grupa = grupa

    def __gt__(self, value):
        return self.__nume > value.get_nume()


    def get_id(self):
        return self.__id


    def get_nume(self):
        return self.__nume


    def get_grupa(self):
        return self.__grupa

        
    def __str__(self):
        return str(self.__id) + " " + self.__nume + " " + str(self.__grupa)

    def __eq__(self, value):
        if type(value) == int:
            return self.__id == value
        return self.__id == value.__id
    
    id = property(get_id, None, None, None)
    nume = property(get_nume, None, None, None)
    grupa = property(get_grupa, None, None, None)
    
class Laborator(object):
    
    def __init__(self, numarLaborator, numarProblema, descriere, deadline):
        self.__numarLaborator = numarLaborator
        self.__numarProblema = numarProblema
        self.__descriere = descriere
        self.__deadline = deadline

    def __str__(self):
        return str(self.__numarLaborator) + " " + str(self.__numarProblema) + " " + self.__descriere + " " + self.__deadline


    def __eq__(self, other):
        return self.__numarLaborator == other.__numarLaborator and self.__numarProblema == other.__numarProblema

    def get_numar_laborator(self):
        return self.__numarLaborator


    def get_numar_problema(self):
        return self.__numarProblema


    def get_descriere(self):
        return self.__descriere


    def get_deadline(self):
        return self.__deadline

    numarLaborator = property(get_numar_laborator, None, None, None)
    numarProblema = property(get_numar_problema, None, None, None)
    descriere = property(get_descriere, None, None, None)
    deadline = property(get_deadline, None, None, None)

class Nota(object):
    def __init__(self, mark, student, laborator):
        self.__mark = mark
        self.__student = student
        self.__laborator = laborator

    def __str__(self):
        return "Studentul " + str(self.__student.get_nume()) + " are la laboratorul " + str(self.__laborator.get_numar_laborator()) + " la problema " + str(self.__laborator.get_numar_problema()) + " nota: " + str(self.__mark)


    def __eq__(self, value):
        if type(value) == Student:
            return self.__student == value
        elif type(value) == Laborator:
            return self.__laborator == value
        else:
            return self.__student == value.__student and self.__laborator == value.__laborator


    def get_mark(self):
        return self.__mark


    def get_student(self):
        return self.__student


    def get_laborator(self):
        return self.__laborator
    
    def set_student(self, st):
        self.__student = st
        
    def set_laborator(self, lab):
        self.__laborator = lab   
    

    mark = property(get_mark, None, None, None)
    student = property(get_student, None, None, None)
    laborator = property(get_laborator, None, None, None)
    
class NoteAvgDTO(object):
    def __init__(self, name, avg):
        self.__name = name
        self.__avg = avg
        
    def get_avg(self):
        return self.__avg
    
    def __str__(self):
        return self.__name + " a luat media " + str(self.__avg)
    
def testCreateLaborator():
    lab = Laborator(1, 2, "Stringuri", "22.15.2017")
    lab1 = Laborator(1, 2, "Stringuri", "22.15.2017")
    assert lab.get_numar_laborator() == 1
    assert lab.get_numar_problema() == 2
    assert lab.get_descriere() == "Stringuri"
    assert lab.get_deadline() == "22.15.2017"
    assert lab == lab1
    
def testCreateNota():
    st = Student(25, "Mihai Georgescu", 215)
    lab = Laborator(1, 2, "Stringuri", "22.15.2017")
    nota = Nota(10, st, lab)
    nota1 = Nota(5, st, lab)
    assert nota.get_mark() == 10
    assert nota.get_student() == st
    assert nota.get_laborator() == lab
    assert nota == nota1
    
    assert nota == st
    assert nota == lab
    
testCreateLaborator()
testCreateNota()
