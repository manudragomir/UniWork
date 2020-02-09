'''
Created on Jan 7, 2019

@author: Manuel
'''

N = int(input("N = "))

dim = int(input("nr elem = "))

list = []
for i in range(dim):
    x = int(input("element: "))
    list.append(x)
    
def solution(x, dim):
    sum = 0
    for i in range(len(x)):
        sum += list[x[i]]
        
    if sum % 3 == 0:
        return True
    
    return False

def solutionFound(x, dim):
    string = ""
    for i in range(len(x)):
        string += str(list[x[i]]) + " "
        
    print(string)
        
def consistent(x, dim):
    lun = len(x)
    if lun > dim:
        return False
    
    if lun > 1 and x[-1] - x[-2] != 1:
        return False
    
    return True
    
    
def backIter(dim):
    x=[-1]
    while len(x)>0:
        choosed = False
        while not choosed and x[-1]<dim-1:
            x[-1] = x[-1]+1 #increase the last component
            choosed = consistent(x, dim)
        if choosed:
            if solution(x, dim):
                solutionFound(x, dim)
            x.append(-1) # expand candidate solution
        else:
            x = x[:-1] #go back one component
            
backIter(dim)