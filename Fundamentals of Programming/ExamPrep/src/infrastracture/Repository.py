from entities.triunghi import Triunghi

class RepoError(Exception):
    pass

class RepoTriunghi(object):
    def __init__(self, filename): 
        self.__filename = filename
        
    def store(self, triunghi):
        '''
        Functie care primeste un triunghi de la tastatura si il adauga in baza de date
        args:
            - triunghi de tip Triunghi
            
        return:
            - 
            
        raises:
            - RepoError - daca elementul se afla deja in baza de date
        '''
        triangles = self.loadFromFile()
        
        if triunghi in triangles:
            raise RepoError("Triunghi existent")
        
        triangles.append(triunghi)
        self.storeToFile(triangles)
        
    def storeToFile(self, triangles):
        try:
            f = open(self.__filename, "w")
            for triunghi in triangles:
                linie_triunghi = str(triunghi.get_l1()) + "," + str(triunghi.get_l2()) + "," + str(triunghi.get_l3())
                linie_triunghi = linie_triunghi + "\n"
                f.write(linie_triunghi)
        except IOError:
            raise IOError
        finally: 
            f.close()
    
    def loadFromFile(self):
        triangles = []
        try:
            f = open(self.__filename, "r")
            line = f.readline().strip()
            while line != "":
                attrs = line.split(',')
                tr = Triunghi(int(attrs[0]), int(attrs[1]), int(attrs[2]))
                triangles.append(tr)
                line = f.readline().strip()
        except IOError:
            raise IOError
        finally:
            f.close()
            
        return triangles
        
    def getAllTriangles(self):
        triangles = self.loadFromFile()
        return triangles[:]
        

def testRepoTriunghi():
    repoTriunghi = RepoTriunghi("test.txt")
    list = repoTriunghi.getAllTriangles()
    assert len(list) == 3
    
testRepoTriunghi()

