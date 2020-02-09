USE Concurs;
GO

ALTER TABLE Profesor
ADD varsta VARCHAR(50) NOT NULL;

Select * from Profesor;

INSERT INTO Profesor (ppid, nume, varsta) VALUES (1, 'Adrian Marica', 25);
INSERT INTO Profesor (ppid, nume, varsta) VALUES (2, 'Gica Hagi', 45);
INSERT INTO Profesor (ppid, nume, varsta) VALUES (3, 'Brad Pitt', 53);
INSERT INTO Profesor (ppid, nume, varsta) VALUES (4, 'Terence Tao', 22);
INSERT INTO Profesor (ppid, nume, varsta) VALUES (5, 'Marius Onofras', 60);

Select * from Judet;

INSERT INTO Judet(jid, nume, locuri) VALUES (10, 'Brasov', 2);
INSERT INTO Judet(jid, nume, locuri) VALUES (20, 'Cluj', 1);
INSERT INTO Judet(jid, nume, locuri) VALUES (30, 'Braila', 1);
INSERT INTO Judet(jid, nume, locuri) VALUES (40, 'Arad', 1);

ALTER TABLE CodJudet
ADD eticheta VARCHAR(10) NOT NULL;

INSERT INTO Liceu(lid, nume) VALUES (1, 'Saguna');
INSERT INTO Liceu(lid, nume) VALUES(2, 'Mesota');
INSERT INTO Liceu(lid, nume) VALUES (3, 'Balcescu');
INSERT INTO Liceu(lid, nume) VALUES (4, 'EminescuBr');
INSERT INTO Liceu(lid, nume) VALUES (5, 'CaragialeAr');
INSERT INTO Liceu(lid, nume) VALUES (6, 'LiceuInPlus');

UPDATE Liceu Set nume='EminescuBr' WHERE lid = 4;

INSERT INTO Student(sid, nume, pctTotal, clasa, judet, liceu) VALUES (1, 'Dragomir Manuel', 300, 11, 10, 1);
INSERT INTO Student(sid, nume, pctTotal, clasa, judet, liceu) VALUES (2, 'Alex Baciu', 10, 11, 10, 2);
INSERT INTO Student(sid, nume, pctTotal, clasa, judet, liceu) VALUES (3, 'Berinde Mihai', 245, 12, 10, 2);
INSERT INTO Student(sid, nume, pctTotal, clasa, judet, liceu) VALUES (4, 'Ilie Oana', 280, 11, 30, 4);
INSERT INTO Student(sid, nume, pctTotal, clasa, judet, liceu) VALUES (5, 'George Cristian', 20, 10, 20, 3);
INSERT INTO Student(sid, nume, pctTotal, clasa, judet, liceu) VALUES (6, 'Vlad Mihai', 40, 10, 20, 3);
INSERT INTO Student(sid, nume, pctTotal, clasa, judet, liceu) VALUES (7, 'Alin Grigore', 150, 11, 30, 4);
INSERT INTO Student(sid, nume, pctTotal, clasa, judet, liceu) VALUES (8, 'Daniel Tan', 88, 10, 40, 5);

INSERT INTO Pregatire(sid, ppid, ore) VALUES (1, 4, 2);
INSERT INTO Pregatire(sid, ppid, ore) VALUES (1, 3, 3);
INSERT INTO Pregatire(sid, ppid, ore) VALUES (2, 4, 4);
INSERT INTO Pregatire(sid, ppid, ore) VALUES (2, 3, 1);
INSERT INTO Pregatire(sid, ppid, ore) VALUES (3, 1, 1);
INSERT INTO Pregatire(sid, ppid, ore) VALUES (5, 1, 1);
INSERT INTO Pregatire(sid, ppid, ore) VALUES (3, 4, 1);
INSERT INTO Pregatire(sid, ppid, ore) VALUES (8, 5, 1);

INSERT INTO Problema(nume, timp, memorie) VALUES ('ProblemaA', 10, 100);
INSERT INTO Problema(nume, timp, memorie) VALUES ('ProblemaB', 15, 100);
INSERT INTO Problema(nume, timp, memorie) VALUES ('ProblemaC', 20, 100);
INSERT INTO Problema(nume, timp, memorie) VALUES ('ProblemaD', 25, 100);
INSERT INTO Problema(nume, timp, memorie) VALUES ('ProblemaE', 30, 100);
INSERT INTO Problema(nume, timp, memorie) VALUES ('123', 30, 100);

INSERT INTO Proba(sid, pid, punctaj) VALUES (1, 2, 100);
INSERT INTO Proba(sid, pid, punctaj) VALUES (1, 3, 100);
INSERT INTO Proba(sid, pid, punctaj) VALUES (4, 3, 4);
INSERT INTO Proba(sid, pid, punctaj) VALUES (2, 2, 2);
INSERT INTO Proba(sid, pid, punctaj) VALUES (2, 3, 8);

INSERT INTO Tag(nume, clasa) VALUES ('Programare Dinamica', 11);
INSERT INTO Tag(nume, clasa) VALUES ('Cautare Binara', 10);
INSERT INTO Tag(nume, clasa) VALUES ('Grafuri', 11);
INSERT INTO Tag(nume, clasa) VALUES ('Mate', 11);
INSERT INTO Tag(nume, clasa) VALUES ('ad-hoc', 11);

INSERT INTO Sectiune(pid, tid, dific) VALUES (1, 2, 10);
INSERT INTO Sectiune(pid, tid, dific) VALUES (2, 2, 7);
INSERT INTO Sectiune(pid, tid, dific) VALUES (3, 2, 8);
INSERT INTO Sectiune(pid, tid, dific) VALUES (3, 3, 9);
INSERT INTO Sectiune(pid, tid, dific) VALUES (5, 3, 4);
INSERT INTO Sectiune(pid, tid, dific) VALUES (3, 1, 2);
INSERT INTO Sectiune(pid, tid, dific) VALUES (4, 1, 5);
INSERT INTO Sectiune(pid, tid, dific) VALUES (2, 4, 7);

SELECT * from Student;

--Query1 - selectez studentii de clasa a11a care au peste 200 de puncte
SELECT nume FROM Student
WHERE pctTotal >= 200 AND clasa = 11;

--Query2 - sortez studentii care s-au pregatit mai mult de o ora 
SELECT S.nume, SUM(P.Ore) AS [Ore de pregatire]
FROM Student S INNER JOIN Pregatire P ON S.sid = P.sid INNER JOIN Profesor R ON R.ppid = P.ppid
GROUP BY S.nume
HAVING SUM(P.Ore) > 1
ORDER BY SUM(P.Ore) DESC;

--Query3 - calculez media dificultatilor pentru fiecare tag exceptand mate si le afisez doar pe cele mai mari de 5
SELECT T.nume, AVG(Cast(S.dific as float)) AS [Grad mediu de dificultate]
FROM Tag T INNER JOIN Sectiune S on S.tid = T.tid INNER JOIN Problema P ON P.pid = S.pid
WHERE T.nume != 'Mate'
GROUP BY T.Nume
HAVING AVG(Cast(S.dific as float)) > 5.0;

--Query4 - calculez pentru fiecare judet, care contine litera a, cati au punctaj peste 100
SELECT J.nume AS [Judet], COUNT(*) AS [Contor]
FROM Student S INNER JOIN Judet J on S.judet = J.jid
WHERE J.nume LIKE '%a%'
GROUP BY J.nume;

--Query5 - selectez toate liceele care au avut elevi participanti la proba
SELECT L.lid as [Liceu participant]
FROM Liceu L 
INTERSECT
SELECT DISTINCT S.Liceu FROM Student S INNER JOIN Proba P on S.sid = P.sid;

--Query6 - afisez punctajul mediu obtinut pentru fiecare problema care se termina in C
SELECT P.nume as [Nume problema], AVG(PR.punctaj) AS [Punctaj mediu]
FROM Problema P INNER JOIN Proba PR ON P.pid = PR.pid
WHERE P.nume LIKE '%[C]'
GROUP BY P.nume;

SELECT * from Pregatire;
--Query7 - selectez profesorii care au elevi cu punctaje totale peste 200
SELECT DISTINCT P.nume
FROM Profesor P INNER JOIN Pregatire PR ON P.ppid = PR.ppid INNER JOIN Student S ON S.sid = PR.sid
WHERE S.pctTotal > 200

--Query8 - selectez toti studentii care nu au facut pregatire
SELECT S.nume 
FROM Student S
WHERE S.nume NOT IN (SELECT S.nume FROM Profesor P INNER JOIN Pregatire PR ON P.ppid = PR.ppid 
					 INNER JOIN Student S ON S.sid = PR.sid);

--Query9 - selectez toti studentii care s-au calificat la faza nationala si nu au facut ore de pregatire
SELECT S.nume
FROM
    (
    SELECT J.jid, MAX(S.pctTotal) AS First
    FROM Student S INNER JOIN Judet J on s.judet=j.jid
    GROUP BY J.jid
    ) foo
    JOIN
    Student S ON foo.jid = S.judet AND foo.First = S.pctTotal
WHERE S.nume NOT IN (SELECT S.nume FROM Profesor P INNER JOIN Pregatire PR ON P.ppid = PR.ppid 
					 INNER JOIN Student S ON S.sid = PR.sid);

--Query10 - selectez toti profesorii care au studenti calificati la faza nationala
SELECT PR.nume
FROM (SELECT S.sid
FROM
    (
    SELECT J.jid, MAX(S.pctTotal) AS First
    FROM Student S INNER JOIN Judet J on s.judet=j.jid
    GROUP BY J.jid
    ) foo
    JOIN
    Student S ON foo.jid = S.judet AND foo.First = S.pctTotal
	WHERE S.sid IN (SELECT S.sid FROM Profesor P INNER JOIN Pregatire PR ON P.ppid = PR.ppid 
					 INNER JOIN Student S ON S.sid = PR.sid)
) as fooo
JOIN 
Pregatire P ON P.sid = fooo.sid INNER JOIN Profesor PR ON PR.ppid = P.ppid;

