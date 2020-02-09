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

def Solve(a):
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

def RunTestsProb11():
    assert Solve([-2,-3,4,-1,-2,1,5,-3]) == [4,-1,-2,1,5]
    assert Solve([-2,-3,4,-1,-2,1,5,-3]) == [4,-1,-2,1,5]
    assert Solve([-2,-3,-4,-5]) == [-2]
    assert Solve([-5, -4, -3, -2, -1]) == [-1]
    assert Solve([2, -1, 5, 6]) == [2, -1, 5, 6]
    assert Solve([2, -3, 5, 6]) == [5, 6]
    assert Solve([2, 0, 5, 6]) == [2, 0, 5, 6]
    assert Solve([1, 2, 3, 4, 5]) == [1, 2, 3, 4, 5]
    

RunTestsProb11()
a = []
Read_Data(a)
print(Solve(a))
