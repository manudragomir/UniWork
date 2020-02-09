'''
Created on Jan 7, 2019

@author: Manuel
'''

    
def solution(x, lista, N):
    sum = 0
    for i in range(len(x)):
        sum += lista[x[i]]
        
    if sum % N == 0:
        return True
    
    return False

def solutionFound(x, lista):
        
    sol = []
    for i in range(len(x)):
        sol.append(lista[x[i]])
    
    return sol
        
def consistent(x, n):
    lun = len(x)
    if lun > n:
        return False
    
    if lun > 1 and x[-1] - x[-2] != 1:
        return False
    
    return True
    
def backRec(x, solutie, n, lista, N):
    x.append(0) #add a new component to the candidate solution    
    for i in range(n):
        x[-1] = i #set current component
        if consistent(x, n):
            if solution(x, lista, N):
                solutie.append(solutionFound(x, lista))
            backRec(x[:], solutie, n, lista, N) #recursive invocation to deal with next components
    x.pop()



def main():
    N = int(input("N = "))
    n = int(input("nr elem = "))
    list = []
    for i in range(n):
        x = int(input("element: "))
        list.append(x)
        
    solutie = []
    x = []
    backRec(x[:], solutie, n, list, N)
    print(solutie)
    

def testeBack():
    N = 3
    n = 6 
    lista = [1,2,3,4,6,12]
    x = []
    solutie_de_testat = []
    backRec(x, solutie_de_testat, n , lista, N)
    solutie_test = [[1, 2], [1, 2, 3], [2, 3, 4], [2, 3, 4, 6], [2, 3, 4, 6, 12], [3], [6], [6, 12], [12]]
    assert solutie_test == solutie_de_testat
    
    solutie_de_testat = []
    N = 1
    n = 1
    lista = [1]
    x = []
    backRec(x, solutie_de_testat, n, lista, N)
    print(solutie_de_testat)
    assert len(solutie_de_testat) == 1
    
main()    
testeBack()
    
    
    
    