from domain.TriunghiCls import Triunghi
from errors.Erori import RepoError, UndoError

class RepoTriunghi():
    def __init__(self, filename):
        self.__filename = filename
        self.__undo = []
        
    def undoStep(self):
        if len(self.__undo) == 0:
            raise UndoError("Nu mai se poate efectua undo")
        
        list_of_triangles = self.__undo.pop()
        self.__storeToFile(list_of_triangles)
        
    def storeTriunghi(self, triunghi):
        list_of_triangles = self.__loadFromFile()
        for tr in list_of_triangles:
            if triunghi == tr:
                raise RepoError("Triunghiul exista deja!")
        
        self.__undo.append(list_of_triangles[:])
        list_of_triangles.append(triunghi)
        self.__storeToFile(list_of_triangles[:])
    
    def __loadFromFile(self):
        list_of_triangles = []
        try:
            f = open(self.__filename, "r")
            fileline = f.readline().strip()
            while fileline != "":
                attrs = fileline.split(",")
                triunghiulet = Triunghi(int(attrs[0]), int(attrs[1]), int(attrs[2]))
                list_of_triangles.append(triunghiulet)
                fileline = f.readline().strip()
        except IOError:
            print("Nu s-a putut deschide")
            
        finally:
            f.close()
            
        return list_of_triangles[:]
    
    def __storeToFile(self, list_of_triangles):
        try:
            f = open(self.__filename, "w")
            for tr in list_of_triangles:
                line = str(tr.get_l1()) + "," + str(tr.get_l2()) + "," + str(tr.get_l3()) + "\n"
                f.write(line)
        except IOError:
            print("Nu s-a putut deschide")
            
        finally:
            f.close()
        
    def getAllTriunghi(self):
        list_of_triunghi = self.__loadFromFile()
        return list_of_triunghi[:]


