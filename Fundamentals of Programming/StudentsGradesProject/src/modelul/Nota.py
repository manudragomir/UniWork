class Nota:
    def __init__(self, valoare, student, laborator):
        self.__valoare = valoare
        self.__student = student
        self.__laborator = laborator
    
    def get_valoare(self):
        return self.__valoare
    
    def get_student(self):
        return self.__student
    
    def get_laborator(self):
        return self.__laborator
    
    def __str__(self):
        return str(self.__student) + " la " + str(self.__laborator) + " " + str(self.__valoare)