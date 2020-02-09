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
        mesaj = input("Alegeti problema 14 sau 15, sau dati exit: ")
        if mesaj == '14':
            Read_Data(a)
            print(Solve_14(a))
        elif mesaj == '15':
            Read_Data(a)
            print(Solve_15(a))
        elif mesaj == 'exit':
            return
        else:
            print("Nu exista aceasta comanda")
        

def Construct_Vector(a, maxstart, maxseq):
    list = []
    
    for i in range(maxstart, maxstart+maxseq):
        list.append(a[i])

    return list

def Solve_14(a):
    actstart = 0
    actseq = 0
    maxseq = 0
    maxstart = 0
    start = 1

    for i in range(1,len(a)):
        cif1 = [0] * 10
        cif2 = [0] * 10
        x1 = a[i]
        x2 = a[i-1]
        
        while x1 != 0:
            cif_act = x1 % 10
            cif1[cif_act] = 1
            x1 = int(x1/10)
        
        while x2 != 0:
            cif_act = x2 % 10
            cif2[cif_act] = 1
            x2 = int(x2/10)

        count = 0

        for j in range (10):
            if cif1[j] != 0 and cif2[j] != 0:
                count += 1

        if count >= 2:
            actseq += 1
            if start == 1:
                actseq += 1
                start = 0
                actstart = i-1
        else:
            actseq = 0
            start = 1
            
        if actseq > maxseq:
            maxseq = actseq
            maxstart = actstart

    #print(maxseq) lungimea secventei maxime
    return Construct_Vector(a, maxstart, maxseq)

def Solve_15(a):
    pass

def RunTestsProb14():
    assert Solve_14([23, 23, 23, 34, 48, 84, 484, 484845]) == [48,84,484,484845]
    assert Solve_14([1,1,1,1]) == []
    assert Solve_14([12,23,31]) == []
    assert Solve_14([23,23]) == [23,23]
    assert Solve_14([23,223,22233]) == [23,223,22233]
    assert Solve_14([]) == []
    assert Solve_14([120,102]) == [120,102]
    assert Solve_14([23,320,230]) == [23,320,230]

def RunTestsProb15():
    pass

def RunTests():
    RunTestsProb14()
    RunTestsProb15()    

RunTests()
UI_Read()
    
