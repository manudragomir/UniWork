def MultiplyMatrix(m1, m2):
    newMatrix = [[0,0],[0,0]]
    
    for i in range(2):
        for j in range(2):
            for k in range(2):
                newMatrix[i][j] = newMatrix[i][j] + m1[i][k] * m2[k][j] 
                
    return newMatrix
    
def RaiseMatrixToPower(unitMatrix, power):
    answerMatrix = [[0,1], [1,1]]
    
    while power != 0:
        if power & 1:
            newMatrix = MultiplyMatrix(answerMatrix, unitMatrix)
            answerMatrix = newMatrix
            
        newMatrix = MultiplyMatrix(unitMatrix, unitMatrix)
        unitMatrix = newMatrix
        
        power = power // 2
        
    return answerMatrix
    
def FindKFibo(n):
    matrix = [[0,1],[1,1]]
    finalmatrix = RaiseMatrixToPower(matrix, n)
    return finalmatrix[0][0]
    
def Read():
    n = int(input("Introdu al catelea termen fibo vrei afla: "))
    return n  

def Run():
    n = Read()
    x = FindKFibo(n)
    print(x)

def raiseToPowerLogaritmically(base, p):
    answer = 1
    
    while p != 0:
        if p & 1:
            answer = answer * base
            
        base = base * base        
        p = p // 2
        
    return answer

Run()
