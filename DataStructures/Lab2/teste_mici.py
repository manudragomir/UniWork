from ColectieImplementata import Colectie, IteratorColectie

def testCreare():
    c = Colectie()
    assert(c.dim() == 0)
    assert(c.vida() == True)
    for i in range(-5,5):
        assert(c.cauta(i) == False)
    for i in range(-10,10):
        assert(c.sterge(i) == False)
    for i in range(-10,10):
        assert(c.nrAparitii(i) == 0)

    it = c.iterator()
    assert(it.valid() == False)

def testAdauga():

    c = Colectie()
    for i in range(10):
        c.adauga(i)
    assert(c.vida() == False)
    assert(c.dim() == 10)
    for i in range(-10, 20):
        c.adauga(i)

    assert(c.vida() == False)
    assert(c.dim() == 40)
    for i in range(-100, 100):
        c.adauga(i)

    assert(c.vida() == False)
    assert(c.dim() == 240)
    for i in range(-200,200):
        cont = c.nrAparitii(i)
        if i < -100:
            assert(cont == 0)
            assert(c.cauta(i) == False)
        elif i < -10:
            assert(cont == 1)
            assert(c.cauta(i) == True)
        elif i < 0:
            assert(cont == 2)
            assert(c.cauta(i) == True)
        elif i < 10:
            assert(cont == 3)
            assert(c.cauta(i) == True)
        elif i < 20:
            assert(cont == 2)
            assert(c.cauta(i) == True)
        elif i < 100:
            assert(cont == 1)
            assert(c.cauta(i) == True)
        else:
            assert(cont == 0)
            assert(c.cauta(i) == False)

    for i in range(10000, -10000, -1):
        c.adauga(i)

    assert(c.dim() == 20240)


def testSterge():
    c = Colectie()
    for i in range(-100,100):
        assert(c.sterge(i) == False)

    assert(c.dim() == 0)
    for i in range(-100,100, 2):
        c.adauga(i)

    for i in range (-100,100):
        if i % 2 == 0:
            assert(c.sterge(i) == True)
        else :
            assert(c.sterge(i) == False)

    assert(c.dim() == 0)
    for i in range(-100,101, 2):
        c.adauga(i)
    for i in range(100,-100, -1):
        if i % 2 == 0:
            assert(c.sterge(i) == True)
        else:
            assert(c.sterge(i) == False)
    assert(c.dim() == 1)
    c.sterge(-100)
    for i in range(-100, 100):
        c.adauga(i)
        c.adauga(i)
        c.adauga(i)
        c.adauga(i)
        c.adauga(i)

    assert(c.dim() == 1000)
    for i in range(-100,100):
        assert(c.nrAparitii(i) == 5)

    for i in range(-100, 100):
        assert(c.sterge(i) == True)

    assert(c.dim() == 800)
    for i in range(-100, 100):
        assert(c.nrAparitii(i) == 4)

    for i in range(-200, 200):
        if (i < -100) or (i >= 100):
            assert(c.sterge(i) == False)
            assert(c.sterge(i) == False)
            assert(c.sterge(i) == False)
            assert(c.sterge(i) == False)
            assert(c.sterge(i) == False)
        else:
            assert(c.sterge(i) == True)
            assert(c.sterge(i) == True)
            assert(c.sterge(i) == True)
            assert(c.sterge(i) == True)
            assert(c.sterge(i) == False)

    assert(c.dim() == 0)
    for i in range(-1000,1000):
        assert(c.nrAparitii(i) == 0)

    min = -200
    max = 200
    while min < max:
        c.adauga(min)
        c.adauga(max)
        min += 1
        max -= 1

    c.adauga(0)
    c.adauga(0)
    assert(c.dim() == 402)
    for i in range(-30, 30):
        assert(c.cauta(i) == True)
        assert(c.sterge(i) == True)
        if i != 0:
            assert(c.cauta(i) == False)
        else:
            assert(c.cauta(i) == True)

    assert(c.dim() == 342)

def testIterator():
    c = Colectie()
    it = c.iterator()
    assert(it.valid() == False)
    try:
        it.urmator()
        assert(False)
    except ValueError:
        assert (True)
    try:
        it.element()
        assert(False)
    except ValueError:
        assert(True)
    
    for i in range(0,100):
        c.adauga(33)
    
    it2 = c.iterator()
    assert(it2.valid() == True)
    for i in range(0, 100):
        elem = it2.element()
        assert(elem == 33)
        it2.urmator()
    
    assert(it2.valid() == False)
    it2.prim()
    assert(it2.valid() == True)
    for i in range(0,100):
        elem = it2.element()
        elem2 = it2.element()
        assert(elem == 33)
        assert(elem2 == 33)
        it2.urmator()
    
    assert(it2.valid() == False)
    try:
        it2.urmator()
        assert(False)
    except ValueError:
        assert(True)
    
    try:
        it2.element()
        assert(False)
    except ValueError:
        assert(True)
    c2 = Colectie()
    for i in range(-100, 100):
        c2.adauga(i)
        c2.adauga(i)
        c2.adauga(i)
    
    it3 = c2.iterator()
    assert(it3.valid() == True)
    for i in range(0, 600):
        e1 = it3.element()
        it3.urmator()
    
    assert(it3.valid() == False)
    it3.prim()
    assert(it3.valid() == True)
    c3 = Colectie()
    for i in range(0,200, 4):
        c3.adauga(i)
    
    it4 = c3.iterator()
    assert(it4.valid() == True)
    cont = 0
    while it4.valid(): 
        e = it4.element()
        assert(e % 4 == 0)
        it4.urmator()
        cont += 1

    assert(cont == 50)
    c4 = Colectie()
    for i in range(0, 100):
        c4.adauga(i)
        c4.adauga(i * (-2))
        c4.adauga(i * 2)
        c4.adauga(i / 2)
        c4.adauga(i / (-2))
    
    elemente = []
    it5 = c4.iterator()
    while it5.valid():
        e = it5.element()
        elemente.append(e)
        it5.urmator()
    
    assert(len(elemente) == c4.dim())
    for i in range(0, len(elemente)):
        ultimElem = elemente[len(elemente) - i - 1]
        assert(c4.cauta(ultimElem) == True)
        c4.sterge(ultimElem)
    
    c5 = Colectie()
    for i  in range(0, 100):
        c5.adauga(i)
        c5.adauga(i * (-2))
        c5.adauga(i * 2)
        c5.adauga(i / 2)
        c5.adauga(i / (-2))
    
    elemente2 = []
    it6 = c5.iterator()
    while it6.valid():
        e = it6.element()
        elemente2.append(e)
        it6.urmator()
    
    assert(len(elemente2) == c5.dim())
    for i in range(0, len(elemente2)):
        primElem = elemente2[i]
        assert(c5.cauta(primElem) == True)
        c5.sterge(primElem)
    

def testCantitate():
    c = Colectie()
    for i in range(10, 0, -1):
        print(i)
        for j in range(-30000, 30000, i):
            c.adauga(j)

    assert(c.dim() == 175739)
    assert(c.nrAparitii(-30000) == 10)
    it = c.iterator()
    assert(it.valid() == True)
    for i in range(0, c.dim()):
        it.urmator()
    
    it.prim()    
    while it.valid():            
        e = it.element()
        assert(c.cauta(e) == True)
        assert(c.nrAparitii(e) > 0)
        it.urmator()
    
    assert(it.valid() == False)
    for i in range(0, 10):
        print(i)
        for j in range(40000, -40000-1, -1):
            c.sterge(j)
    
    assert(c.dim() == 0)



def testAllLung():
   # testCreare()
   # testAdauga()
   # testSterge()
    testIterator()
    testCantitate()


testAllLung()