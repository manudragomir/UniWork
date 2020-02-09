'''
Program ce calculeaza cea mai lunga subsecventa de elemente distincte
'''
def isPrime(x):
    if x < 2:
        return False
    
    if x > 2 and x % 2 == 0:
        return False

    d = 3
    while d * d <= x:
        if x % d == 0:
            return False
        d += 2

    return True
    

def Read_Data(a):
    while True:
        n = input("introdu numarul de numere: ")
        try:
            n = int(n)
            break
        except ValueError:
            input("Introdu un numar intreg")
    
    for i in range(n):
        x = int(input("Introdu un numar intreg "))
        a.append(x)

def Vec_Construct(a,maxstart, maxseq):
    
    v = ""
    list = []
    
    for i in range(maxstart, maxstart+maxseq):
        v += str(a[i]) + " "
        list.append(a[i])

    return list
    

def Solve1(a):
    actstart = 0
    actseq = 0
    maxseq = 0
    maxstart = 0
    lastel = a[0]

    for i in range(0,len(a)):        
        if a[i] > lastel:
            actseq += 1

        else:
            actstart = i
            actseq = 1            

        if actseq > maxseq: # daca am gasit o secventa mai buna
            maxseq = actseq
            maxstart = actstart
            
        lastel = a[i]

    #print(maxseq) lungimea secventei maxime

    return Vec_Construct(a, maxstart, maxseq)

def Solve2(a):
    actstart = 0
    actseq = 0
    maxseq = 0
    maxstart = 0
    la = [-1] * 10000000
    queue = []
    elinq = 0

    for i in range(len(a)):
        if elinq <= 2 and la[a[i]] < actstart:
            queue.append(a[i])
            elinq += 1
            la[a[i]] = i
            actseq += 1

        elif elinq <= 3 and la[a[i]] >= actstart:
            la[a[i]] = i
            actseq += 1

        elif elinq == 3 and la[a[i]] < actstart:
            x = queue[0]
            actstart = la[x] + 1
            actseq = i - actstart + 1
            queue.pop(0)
            queue.append(a[i])
            
        if actseq > maxseq: # daca am gasit o secventa mai buna
            maxseq = actseq
            maxstart = actstart

    #print(maxseq) lungimea secventei maxime

    return Vec_Construct(a, maxstart, maxseq)

def GCD(a, b):
    r = 0
    while b != 0:
        r = a % b
        a = b
        b = r
    return a

def Solve3(a):
    actstart = 0
    actseq = 0
    maxseq = 0
    maxstart = 0

    for i in range(len(a) - 1):        
        if GCD(a[i], a[i+1]) == 1: 
            actseq += 1

        else:
            actstart = i
            actseq = 1            

        if actseq > maxseq: # daca am gasit o secventa mai buna
            maxseq = actseq
            maxstart = actstart
            
    if GCD(a[len(a)-1], a[len(a)-2]) == 1:
        actseq += 1
        if actseq > maxseq: # daca am gasit o secventa mai buna
            maxseq = actseq
            maxstart = actstart

    #print(maxseq) lungimea secventei maxime

    return Vec_Construct(a, maxstart, maxseq)

def Solve4(a):
    actstart = 0
    actseq = 0
    maxseq = 0
    maxstart = 0

    for i in range(len(a)):        
        if isPrime(a[i]) == True:
            actseq += 1

        else:
            actstart = 0
            actseq = 0

        if i > 0 and isPrime(a[i-1]) == False:
            actstart = i

        if actseq > maxseq: # daca am gasit o secventa mai buna
            maxseq = actseq
            maxstart = actstart

    #print(maxseq) lungimea secventei maxime

    return Vec_Construct(a, maxstart, maxseq)

def Solve5(a):
    actstart = 0
    actseq = 0
    maxseq = 0
    maxstart = 0

    for i in range(1,len(a)):        
        if a[i-1] == a[i]:
            actseq += 1
            if i > 1 and a[i-1] != a[i-2]:
                actstart = i-1
                actseq = 2

        else:
            actstart = 0
            actseq = 0

        if actseq > maxseq: # daca am gasit o secventa mai buna
            maxseq = actseq
            maxstart = actstart

    #print(maxseq) lungimea secventei maxime

    if maxseq == 0:
        maxseq = 1
        
    return Vec_Construct(a, maxstart, maxseq)

def Solve_7(a):
    actstart = 0
    actseq = 0
    maxseq = 0
    maxstart = 0

    for i in range(1,len(a)):        
        if isPrime(cmmdc(a[i-1], a[i]))
            actseq += 1
            if i > 1:
                actstart = i-1
                actseq = 2

        else:
            actstart = 0
            actseq = 0

        if actseq > maxseq: # daca am gasit o secventa mai buna
            maxseq = actseq
            maxstart = actstart

    #print(maxseq) lungimea secventei maxime

    if maxseq == 0:
        maxseq = 1
        
    return Vec_Construct(a, maxstart, maxseq)
    
    
def Tests():
    assert Solve4([2,3,5,9,2,3,26,2,3,5,7]) == [2,3,5,7]
    assert Solve5([1,2,3]) == [1]
    assert Solve5([1,1,1,2,1,1,3,3,3,3,3]) == [3,3,3,3,3]
    assert Solve6([2,6,12,9]) == [2,6,12,9]
    
    
Tests()
mesaj = int(input("Problema nr: "))

a = []
Read_Data(a)


if mesaj == 1:
    print(Solve1(a))
elif mesaj == 2:
    print(Solve2(a))
elif mesaj == 3:
    print(Solve3(a))
elif mesaj == 4:
    print(Solve4(a))

    
    



