class Student(object):
    
    def __init__(self, id, nume, grupa):
        self.__id = id
        self.__nume = nume
        self.__grupa = grupa
        
    def __eq__(self, other):
        return self.__id == other.__id

    def get_id(self):
        return self.__id


    def get_nume(self):
        return self.__nume

    def get_grupa(self):
        return self.__grupa


    def set_nume(self, value):
        self.__nume = value


    def set_grupa(self, value):
        self.__grupa = value
        
    def __str__(self):
        return str(str(self.__id) + " " + (str(self.__nume)) + " " + (str(self.__grupa)))