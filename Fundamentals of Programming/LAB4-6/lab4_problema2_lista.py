def Taskuri_Posibile():
    print("Iata taskurile posibile si codurile lor")
    print("COD:   TASK")
    print("1a: Adauga scor pentru un nou participant\n")
    print("1b: Inserare scor pentru un participant\n")
    print("2a: Sterge scorul(toate scorurile) pentru un participant dat\n")
    print("2b: Sterge scorul(toate scorurile) pentru un interval dat\n")
    print("2c: Inlocuieste un scor unui participant la o proba data\n")
    print("3a: Tipareste participantii care au un scor mai mic decat un scor dat\n")
    print("3b: Tipareste participantii ordonat\n")
    print("3c: Tipareste participantii cu un scor mai mare decat un scor dat\n")
    print("4a: Media scorurilor pentru un interval dat\n")
    print("4b: Calculeaza scorul minim pentru un interval dat\n")
    print("4c: Tipareste participantii pentru un interval dat multiplu de 10\n")
    print("5a: Filtrare participanti care au scorul multiplu unui nr dat\n")
    print("5b: Filtrare participanti care au un un scor mai mic decat un scor dat\n")
    print("6a: Undo\n")
    print("exit: Iesi din aplicatie\n")
    print("print: Afiseaza baza de date\n\n")

def Get_Participant_By_Id(lista, id):
    
    """
    Preconditii: Primeste baza de date sub forma unei liste de liste si id-ul concurentului
    Rol: Cauta id-ul in baza de date, iar in cazul in care il gaseste va returneaza lista cu scoruri, altfel
         returneaza -1
    Postconditii: Returneaza lista cu scoruri, in cazul in care id-ul este regasit in baza de date,
                  in caz contrar returneaza -1
    """
    
    for i in range(1,len(lista)):
        if lista[i][0] == id:
            return lista[i][2]

    return -1

def Get_Index_Of_Participant_By_Id(lista, id):
    
    """
    Preconditii: Primeste baza de date sub forma unei liste de liste si id-ul concurentului
    Rol: Cauta id-ul in baza de date, iar in cazul in care il gaseste va returna indexul
         din baza de date, la care se regaseste acel concurent, altfel returneaza -1
    Postconditii: Returneaza un numar natural ce reprezinta indexul concurentului cautat dupa id,
                  in caz contrar returneaza -1
    """
    
    for i in range(1,len(lista)):
        if lista[i][0] == id:
            return i

    return -1

def Calc_Media(lista):
    """
    Preconditii: Primeste o lista de numere intregi
    Rol: Se calculeaza media aritmetica a elementelor din lista
    Postconditii: Returneaza un numar real ce reprezinta media
    """
    numar = len(lista)
    sum = 0
    
    for i in range(len(lista)):
        sum = sum + lista[i]
        
    return round((1.0 * sum / numar),2)

def Printing(lista):
    """
    Preconditii: Primeste baza de date
    Rol: Are rolul de a transmite utilizatorul informatii despre baza de date, intr-un mod
         user-friendly
    Postconditii: Returneaza toate datele incluse in baza de date, ID, numar de concurs sau id
                  Media probelor si scoruririle de la toate probele la care a participat
    """
    
    if len(lista) == 1:
        print("Lista vida")
        
    for i in range(1,len(lista)):
        print("indexul:", i)
        print("numarul de concurs:", lista[i][0])
        print("media la probe:", lista[i][1])
        print("scorurile:", lista[i][2])
        print("\n")
  
def UI_Solve_1a(lista):
    """
    Preconditii: Primeste baza de date
    Rol: Are rolul de valida datele, id = numar natural nenul, scorul = numar natural si de
         a verifica daca id-ul nu este deja prezent in lista
    Postconditii: Returneaza un tuplu ce imperecheaza id-ul si scorul
    """
    
    while True:
        id = input("introdu numarul de concurs al noului concurent: ")
        try:
            id = int(id)
            if id <= 0:
                raise ValueError

            if Get_Participant_By_Id(lista,id) != -1:
                raise ValueError
            ' as vrea sa dau un alt mesaj de eroare aici '
                
            break
        except ValueError:
            print("Input gresit, introdu un numar natural ")

    while True:
        scor = input("introdu scorul noului concurent: ")
        try:            
            scor = int(scor)
            if scor < 0:
                raise ValueError
            break
        except ValueError:
            print("Input gresit, introdu un numar natural te rog ")

    return (id,scor)

def UI_Solve_1b(lista):

    """
    Preconditii: Primeste baza de date
    Rol: Are rolul de valida datele, id = numar natural nenul, scorul = numar natural si de
         a verifica daca id-ul este deja prezent in lista
    Postconditii: Returneaza un tuplu ce imperecheaza id-ul si scorul
    """
    
    while True:
        id = input("introdu numarul de concurs concurentului: ")
        try:
            id = int(id)
            if id <= 0:
                raise ValueError

            if Get_Participant_By_Id(lista,id) == -1:
                raise ValueError("Id-ul nu exista")
            ' as vrea sa dau un alt mesaj de eroare aici '
                
            break
        except ValueError as e:
            print(e.message)

    while True:
        scor = input("introdu scorul noului concurent: ")
        try:            
            scor = int(scor)
            if scor < 0:
                raise ValueError
            break
        except ValueError:
            print("Input gresit, introdu un numar natural te rog ")

    return (id,scor)

def UI_Solve_2a(lista):

    """
    Preconditii: Primeste baza de date
    Rol: Are rolul de a citi si a valida datele, id = numar natural nenul
    Postconditii: Returneaza id-ul
    """
    
    while True:
        id = input("introdu numarul de concurs al noului concurent: ")
        try:
            id = int(id)
            if id <= 0:
                raise ValueError

            if Get_Participant_By_Id(lista,id) == -1:
                raise ValueError
            ' as vrea sa dau un alt mesaj de eroare aici '
                
            break
        except ValueError:
            print("Input gresit, introdu un numar natural")

    return id

def UI_Solve_2b(lista):
    """
    Preconditii: Primeste baza de date
    Rol: Sa citeasca capete de interval valide
    Postconditii: Returneaza un tuplu ce imperecheaza capatul inferior si cel superior al intervalului
    """

    while True:
        start = input("introdu capatul din stanga al intervalului: ")
        try:
            start = int(start)
            if start <= 0 or start >= len(lista) - 1:
                raise ValueError
            break
        except ValueError:
            print("Input gresit, introdu un capat valid")

    while True:
        end = input("introdu capatul din dreapta al intervalului: ")
        try:
            end = int(end)
            if start >= end or end >= len(lista):
                raise ValueError
            break
        except ValueError:
            print("Input gresit, introdu un capat valid")

    return (start, end)

def UI_Solve_2c(lista):
    """
    Preconditii: Primeste baza de date
    Rol: Sa citeasca si valideze id, proba si scorul
    Postconditii: Returneaza un tuplu ce imperecheaza id-ul > 0, proba(posibila pentru acel participant)
                  si scorul >= 0
    """

    while True:
        id = input("introdu numarul de concurs al concurentului: ")
        try:
            id = int(id)
            if id <= 0:
                raise ValueError

            if Get_Participant_By_Id(lista,id) == -1:
                raise ValueError
            ' as vrea sa dau un alt mesaj de eroare aici '
                
            break
        except ValueError:
            print("Input gresit, introdu date valide")

    while True:
        proba = input("introdu numarul probei: ")
        try:
            proba = int(proba)
            if proba >= len(Get_Participant_By_Id(lista,id)):
                raise ValueError
            break
        except ValueError:
            print("Input gresit, introdu date valide")

    while True:
        noulScor = input("introdu noul scor: ")
        try:
            noulScor = int(noulScor)
            if noulScor < 0:
                raise ValueError
            break
        except ValueError:
            print("Input gresit, introdu date valide")

    return (id, proba, noulScor)

def UI_Solve_3(lista):
    """
    Preconditii: Primeste baza de date
    Rol: Sa citeasca si un scor
    Postconditii: Returneaza scorul
    """
    while True:
        Scor = input("introdu scor: ")
        try:
            Scor = int(Scor)
            if Scor < 0:
                raise ValueError
            break
        except ValueError:
            print("Input gresit, introdu date valide")
            
    return Scor

def Solve_4a():
    pass

def Solve_4b():
    pass

def Solve_4c():
    pass

def Solve_5a():
    pass

def Solve_5b():
    pass

def Solve_6a():
    pass

def UI_Read():
    '''
    Am un dictionar cu functiile necesare impartit in mai multe categorii in functie de numarul de parametri
    '''
    Participants_List = [0]
    Succes = "Operatia a fost realizata cu succes!\n"
    while True:
        mesaj = input("Introdu codul dorit: ")
        
        list3 = {"1a": Solve_1a, "1b": Solve_1b} 
        list3UI = {"1a": UI_Solve_1a, "1b": UI_Solve_1b}
        # dictionar in care folosesc 3 variabile lista + id + scor

        list2UI = {"2a": UI_Solve_2a}
        list2 = {"2a": Solve_2a}
        # dictionar in care folosesc 2 variabile lista + id

        list4UI = {"2b": UI_Solve_2b}
        list4 = {"2b": Solve_2b}
        # dictionar in care folosesc 3 variabile lista, stinterval, endinterval

        list5UI = {"2c": UI_Solve_2c}
        list5 = {"2c": Solve_2c}

        list6UI = {"3a": UI_Solve_3, "3c": UI_Solve_3}
        list6 = {"3a": Solve_3a, "3b": Solve_3b, "3c": Solve_3c}
        
        if mesaj in list3:
            ' as vrea sa selectez Solve_1a si sa fac si UI direct din el'
            id, scor = list3UI[mesaj](Participants_List)
            Participants_List = list3[mesaj](Participants_List, id, scor)
            print(Succes)

        elif mesaj in list2:
            id = list2UI[mesaj](Participants_List)
            Participants_List = list2[mesaj](Participants_List, id)
            print(Succes)

        elif mesaj in list4:
            start, end = list4UI[mesaj](Participants_List)
            Participants_List = list4[mesaj](Participants_List, start, end)
            print(Succes)

        elif mesaj in list5:
            id, proba, scorNou = list5UI[mesaj](Participants_List)
            Participants_List = list5[mesaj](Participants_List, id, proba, scorNou)
            print(Succes)

        elif mesaj in list6:
            if mesaj == '3a':
                scor = list6UI[mesaj](Participants_List)
                newlist = list6[mesaj](Participants_List, scor);
                print("Numerele de concurs ale concurentilor sunt:", newlist)

            elif mesaj == '3b':
                scor = 1 #as vrea sa citesc +- 1 la valoarea asta fara sa fac o functie separata
                newlist = list6[mesaj](Participants_List, scor);
                newlist.insert(0,0)
                Printing(newlist)

            elif mesaj == '3c':
                scor = list6UI[mesaj](Participants_List)
                newlist = list6[mesaj](Participants_List, scor);
                newlist.insert(0,0) #sa incep de la 1
                Printing(newlist)
                
            print(Succes)
            
        elif mesaj == 'exit':
            return

        elif mesaj == 'print':
            Printing(Participants_List)

        else:
            print("Introdu o comanda valida")

def Solve_1a(lista, id, scor):
    """
    Preconditii: Primeste baza de date, id-ul si scorul
    Rol: Adauga in baza de date, noul concurent
    Postconditii: Returneaza baza de date modificata
    """

    lista.append([])
    nr = len(lista)
    nr = nr - 1
    lista[nr].append(id);
    lista[nr].append(scor);
    lista[nr].append([scor]);
    return lista

def Solve_1b(lista, id, scor):
    """
    Preconditii: Primeste baza de date, id-ul si scorul
    Rol: Adauga in baza de date la un concurent, scorul de la o proba noua
    Postconditii: Returneaza baza de date modificata
    """
    
    index = Get_Index_Of_Participant_By_Id(lista, id)
    lista[index][2].append(scor);

    lista[index][1] = Calc_Media(Get_Participant_By_Id(lista,id))

    return lista

def Solve_2a(lista, id):
    """
    Preconditii: Primeste baza de date si un id
    Rol: Sterge toate scorurile acelui participant, eliminandu-l din baza de date
    Postconditii: Returneaza baza de date modificata
    """
    
    index = Get_Index_Of_Participant_By_Id(lista, id);
    del lista[index]
    return lista

def Solve_2b(lista,start,end):
    """
    Preconditii: Primeste baza de date si un interval
    Rol: Sterge toate scorurile participantilor din acel interval, eliminandu-i din baza de date
    Postconditii: Returneaza baza de date modificata
    """
    
    del lista[start:end+1]
    return lista

def Solve_2c(lista, id, proba, noulScor):
    """
    Preconditii: Primeste baza de date, id-ul concurentului, proba la care dorim sa facem modificarea
                 si noul scor pe care am vrea sa-l introducem
    Rol: Modifica scorul unui participant la o anumita proba, urmand sa-i modifice si media
    Postconditii: Returneaza baza de date modificata
    """
    
    index = Get_Index_Of_Participant_By_Id(lista, id)
    lista[index][2][proba] = noulScor
    lista[index][1] = Calc_Media(Get_Participant_By_Id(lista,id))
    return lista

def Solve_3a(lista, scor):
    """
    Preconditii: Primeste baza de date si un scor
    Rol: Creaza o lista noua cu toti participantii care au scorul strict mai mic decat scorul dat
    Postconditii: Returneaza lista noua
    """
    
    new_list = []
    
    for i in range(1,len(lista)):
        if lista[i][1] < scor:
            new_list.append(lista[i][0])

    return new_list

def Solve_3b(lista, val):
    """
    Preconditii: Primeste baza de date (implicit pe pozitia 0 e 0) si o valoarea
    Rol: Creaza o lista noua cu toti participantii in ordinea descrescatoare daca valoarea e pozitiva
         si in ordine descrescatoare daca valoarea e pozitiva
    Postconditii: Returneaza lista noua
    """
    
    n = len(lista)
    new_list = lista[1:n]
    if val >= 0:
        new_list = sorted(new_list, key = lambda x: x[1], reverse = True)
    else:
        new_list = sorted(new_list, key = lambda x: x[1], reverse = False)
    return new_list

def Solve_3c(lista, scor):
    """
    Preconditii: Primeste baza de date si un scor
    Rol: Creaza o lista noua cu toti participantii cu un scor mai mare decat scorul dat
         si apoi il sorteaza
    Postconditii: Returneaza lista noua ordonata
    """
    
    new_list = []
    new_list.append(0);
    
    for i in range(1,len(lista)):
        if lista[i][1] > scor:
            new_list.append(lista[i])

    return Solve_3b(new_list, 1)

def Test_Solve_1a():
    assert Solve_1a([0],25,250) == [0,[25,250,[250]]]
    assert Solve_1a([0],63,300) == [0,[63,300,[300]]]
    assert Solve_1a([0,[25,250,[250]]],27,250) == [0,[25,250,[250]], [27,250,[250]]]
    assert Solve_1a([0,[25,250,[250]], [27,250,[250]]],63,300) == [0,[25,250,[250]], [27,250,[250]], [63,300,[300]]]
    assert Solve_1a([0],1,1) == [0,[1,1,[1]]]

def Test_Solve_1b():
    assert Solve_1b([0,[25,250,[250]]],25,250) == [0,[25,250,[250,250]]]
    assert Solve_1b([0,[25,250,[250]], [63,150,[150]]], 63,250) == [0,[25,250,[250]], [63,200,[150,250]]]
    assert Solve_1b([0,[25,250,[250]], [63,200,[150,250]]], 63,250) == [0,[25,250,[250]], [63,216.67,[150,250,250]]]
    assert Solve_1b([0,[25,250,[250]], [63,216.67,[150,250,250]]], 25,250) == [0,[25,250,[250,250]], [63,216.67,[150,250,250]]]
    assert Solve_1b([0,[25,200,[250,150]], [63,150,[150]]], 25, 50) == [0,[25,150,[250,150,50]], [63,150,[150]]]

def Test_Solve_2a():
    assert Solve_2a([0,[25,250,[250]], [63,200,[150,250]]], 25) == [0,[63,200,[150,250]]]
    assert Solve_2a([0,[25,250,[250]]],25) == [0]
    assert Solve_2a([0,[25,250,[250]], [63,150,[150]]], 63) == [0,[25,250,[250]]]
    assert Solve_2a([0,[25,250,[250]], [63,216.67,[150,250,250]]], 63) == [0,[25,250,[250]]]
    assert Solve_2a([0,[25,200,[250,150]], [63,150,[150]]], 25) == [0, [63,150,[150]]]

def Test_Solve_2b():
    assert Solve_2b([0,[25,250,[250]], [63,200,[150,250]]], 1, 1) == [0,[63,200,[150,250]]]
    assert Solve_2b([0,[25,250,[250]]], 1, 1) == [0]
    assert Solve_2b([0,[25,250,[250]], [63,150,[150]]], 1,2) == [0]
    assert Solve_2b([0,[25,250,[250]], [63,216.67,[150,250,250]], [27,250,[250]], [65,216.67,[150,250,250]], [27,250,[250]], [65,216.67,[150,250,250]]], 3,5) == [0,[25,250,[250]], [63,216.67,[150,250,250]], [65,216.67,[150,250,250]]]
    assert Solve_2b([0,[25,200,[250,150]], [63,150,[150]]], 2,2) == [0, [25,200,[250,150]]]

def Test_Solve_2c():
    assert Solve_2c([0,[25,250,[250]]], 25, 0, 200) == [0, [25, 200, [200]]]
    assert Solve_2c([0,[25,250,[250,250,250,250]]], 25, 3, 200) == [0, [25, 237.5, [250,250,250,200]]]
    assert Solve_2c([0,[25,250,[250]], [35, 200, [200,200]]], 35, 1, 220) == [0,[25,250,[250]], [35, 210, [200,220]]]
    assert Solve_2c([0,[25,250,[250,275]]], 25, 1, 200) == [0, [25, 225, [250,200]]]
    assert Solve_2c([0,[25,250,[250]]], 25, 0, 40) == [0, [25, 40, [40]]]

def Test_Solve_3a():
    assert Solve_3a([0,[25,250,[250]], [63,216.67,[150,250,250]], [27,250,[250]], [65,216.67,[150,250,250]], [28,250,[250]], [69,216.67,[150,250,250]]], 240) == [63, 65, 69]
    assert Solve_3a([0,[25,250,[250]]], 250) == []
    assert Solve_3a([0,[25,250,[250]]], 300) == [25]
    assert Solve_3a([0,[25,250,[250]], [63,216.67,[150,250,250]], [27,250,[250]], [65,216.67,[150,250,250]], [28,250,[250]], [69,216.67,[150,250,250]]], 216) == []
    assert Solve_3a([0,[25,250,[250]]], 251) == [25]

def Test_Solve_3b():
    assert Solve_3b([0,[25,250,[250]]], -250) == [[25,250,[250]]]
    assert Solve_3b([0,[25,250,[250]], [25, 215, [250]]], -300) == [[25, 215, [250]], [25,250,[250]]]
    assert Solve_3b([0,[25,250,[250]], [63,216.67,[150,250,250]], [27,250,[250]], [65,216.67,[150,250,250]]], -1) == [[63,216.67,[150,250,250]], [65,216.67,[150,250,250]], [25,250,[250]], [27,250,[250]]]
    assert Solve_3b([0,[25,250,[250]], [27,215,[215]]], -21) == [[27,215,[215]], [25,250,[250]]]
    assert Solve_3b([0,[25,250,[250]]], 250) == [[25,250,[250]]]
    assert Solve_3b([0,[25,250,[250]], [25, 215, [250]]], 300) == [[25,250,[250]], [25, 215, [250]]]

def Test_Solve_3c():
    assert Solve_3c([0,[25,250,[250]], [63,216.67,[150,250,250]], [27,250,[250]], [65,216.67,[150,250,250]]], 220) == [[25,250,[250]], [27,250,[250]]]
    assert Solve_3c([0,[25,250,[250]]], 210) == [[25,250,[250]]]
    assert Solve_3c([0,[25,250,[250]], [25, 215, [250]]], 230) == [[25,250,[250]]]
    assert Solve_3c([0,[25,250,[250]], [27,215,[215]]], 200) == [[25,250,[250]], [27,215,[215]]]
    assert Solve_3c([0,[25,250,[250]]], 300) == []
    assert Solve_3c([0,[200,200,[200]], [80, 80, [80]], [100,100, [100]]], 50) == [[200,200,[200]], [100,100, [100]], [80, 80, [80]]]
    
def Test_Get_Participant_By_Id():
    lista_aux = [0,[25,250,[250]], [27,275,[250, 300]], [63,265,[300,250,245]]]
    assert Get_Participant_By_Id(lista_aux,25) == [250]
    assert Get_Participant_By_Id(lista_aux,27) == [250,300]
    assert Get_Participant_By_Id(lista_aux,81) == -1
    assert Get_Participant_By_Id(lista_aux,63) == [300,250,245]
    assert Get_Participant_By_Id([0],25) == -1

def Test_Get_Index_Of_Participant_By_Id():
    lista_aux = [0,[25,250,[250]], [27,250,[250]], [63,300,[300]]]
    assert Get_Index_Of_Participant_By_Id(lista_aux,25) == 1
    assert Get_Index_Of_Participant_By_Id(lista_aux,27) == 2
    assert Get_Index_Of_Participant_By_Id(lista_aux,63) == 3
    assert Get_Index_Of_Participant_By_Id([],25) == -1
    assert Get_Index_Of_Participant_By_Id(lista_aux,65) == -1

def Test_Calc_Media():
    assert Calc_Media([150,250,250]) == 216.67
    assert Calc_Media([1,2,3]) == 2.0
    assert Calc_Media([1,2,3,4]) == 2.5
    assert Calc_Media([6,5,8,9,15]) == 8.6
    assert Calc_Media([50,100,150]) == 100.0
    assert Calc_Media([7,8]) == 7.5

def Run_Tests():
    Test_Calc_Media()
    Test_Solve_1a()
    Test_Solve_1b()
    Test_Solve_2a()
    Test_Solve_2b()
    Test_Solve_2c()
    Test_Solve_3a()
    Test_Solve_3b()
    Test_Solve_3c()
    Test_Get_Participant_By_Id();
    Test_Get_Index_Of_Participant_By_Id();
    

Run_Tests()
Taskuri_Posibile()
UI_Read()
