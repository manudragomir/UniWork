from lib2to3.pgen2.token import GREATER
def selectionSort(l):
    for i in range(0,len(l)-1):
        ind = i
        for j in range(i+1, len(l)):
            if l[j] < l[ind]:
                ind = j
                
        if ind > i:
            aux = l[i]
            l[i] = l[ind]
            l[ind] = aux
            
def insertionSort(l):
    for i in range(1, len(l)):
        a = l[i]
        ind = i - 1
        while ind >= 0 and a < l[ind]:
            l[ind + 1] = l[i]
            ind = ind - 1
            
        l[ind + 1] = a
        
def qsort(list):
    if list == []:
        return []
    else:
        pivot = list[0]
        lesser = qsort([x for x in list[1:] if x < pivot])
        greater = qsort([x for x in list[1:] if x >= pivot])
        return lesser + [pivot] + greater
    
def binSearch(l, left, right, el):
    if left <= right:
        m = (left + right)//2
        
        if l[m] == el:
            return m
        
        if el <= l[m]:
            return binSearch(l, left, m - 1, el)
        
        return binSearch(l, m + 1, right, el)
    
    return -1

def searchSeq(el,l):
    if len(l) == 0:
        return 0
    
    poz = -1
    for i in range(0, len(l)):
        if el <= l[i]:
            poz = i
            
    if poz == -1:
        return len(l)
    
    return poz

searchSeq(5, [2,3,4,5,6,7,8,9])
            
            
                
                
            