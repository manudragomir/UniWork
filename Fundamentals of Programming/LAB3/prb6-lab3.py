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

def UI_Read():
    while True:
        a = []
        mesaj = input("Alegeti problema 6 sau 11, sau dati exit: ")
        if mesaj == '6':
            Read_Data(a)
            print(Solve_6(a))
        elif mesaj == '11':
            Read_Data(a)
            print(Solve_11(a))
        elif mesaj == 'exit':
            return
        else:
            print("Nu exista aceasta comanda")
        

def Construct_Vector(a, maxstart, maxseq):
    v = ""
    list = []
    
    for i in range(maxstart, maxstart+maxseq):
        v += str(a[i]) + " "
        list.append(a[i])

    return list

def Solve_6(a):
    l = [-1] * 10000000
    actstart = 0
    actseq = 0
    maxseq = 0
    maxstart = 0

    for i in range(0,len(a)):
        if l[a[i]] < actstart: # daca ultima aparitie a elementului este inaintea inceputului secventei actuale
            l[a[i]] = i
            actseq = actseq + 1 # il adaugam in secventa

        else:
            actseq = i - l[a[i]] # daca elementul apare in secventa actuala, reducem secventa, modificam inceputul ei
            actstart = l[a[i]] + 1 # la pozitia elementului duplicat + 1 
            l[a[i]] = i

        if actseq > maxseq: # daca am gasit o secventa mai buna
            maxseq = actseq
            maxstart = actstart

    #print(maxseq) lungimea secventei maxime
    return Construct_Vector(a, maxstart, maxseq)

def Solve_11(a):
    actstart = 0
    startseq = 0
    actlength = 0
    lengthseq = 0
    maxsum = 0
    actsum = 0
    check = 0
    maxi = a[0]

    for i in range(len(a)):
        if actsum + a[i] > a[i]:
            actsum = actsum + a[i]
            actlength = actlength + 1

        else:
            actstart = i
            actlength = 1
            actsum = a[i]

        if actsum > maxsum:
            maxsum = actsum
            startseq = actstart
            lengthseq = actlength

        if a[i] > 0: #marchez ca exista cel putin un numar pozitiv
            check = 1
            
        maxi = max(maxi, a[i]) #acest maxim ma va interesa doar daca sunt numai numere negative

#    print(maxsum, startseq, startseq + lengthseq - 1)        
    
    i = startseq
    li = []

    while i < startseq + lengthseq:
        li.append(a[i])
        i = i + 1

    if check == 0: #daca am doar numere negative
        li = []
        li.append(maxi)
    
    return li

def RunTestsProb6():
    assert Solve_6([1,2,2,3,4]) == [2,3,4]
    assert Solve_6([1,1,1,1]) == [1]
    assert Solve_6([1,2,3]) == [1,2,3]
    assert Solve_6([7,8,9,10,7,5]) == [8,9,10,7,5]
    assert Solve_6([6,5,1,2,3,2,1,4]) == [6,5,1,2,3]
    assert Solve_6([]) == []
    assert Solve_6([1]) == [1]
    assert Solve_6([1,2,3,4,1,2,3,5]) == [4,1,2,3,5]

def RunTestsProb11():
    assert Solve_11([-2,-3,4,-1,-2,1,5,-3]) == [4,-1,-2,1,5]
    assert Solve_11([-2,-3,4,-1,-2,1,5,-3]) == [4,-1,-2,1,5]
    assert Solve_11([-2,-3,-4,-5]) == [-2]
    assert Solve_11([-5, -4, -3, -2, -1]) == [-1]
    assert Solve_11([2, -1, 5, 6]) == [2, -1, 5, 6]
    assert Solve_11([2, -3, 5, 6]) == [5, 6]
    assert Solve_11([2, 0, 5, 6]) == [2, 0, 5, 6]
    assert Solve_11([1, 2, 3, 4, 5]) == [1, 2, 3, 4, 5]

def RunTests():
    RunTestsProb6()
    RunTestsProb11()    

RunTests()
UI_Read()
    



