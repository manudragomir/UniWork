CREATE DATABASE Biblio;
USE Biblio

CREATE TABLE Librarie
(
	Lid INT PRIMARY KEY IDENTITY,
	Nume VARCHAR(50),
	Adresa VARCHAR(50)
);

CREATE TABLE Carti
(
	Cid INT PRIMARY KEY IDENTITY,
	Titlu VARCHAR(50),
);

CREATE TABLE Achitizie
(
	Cid INT FOREIGN KEY REFERENCES Carti(Cid),
	Lid INT FOREIGN KEY REFERENCES Librarie(Lid),
	DataA DATE
	CONSTRAINT PK_A PRIMARY KEY (Cid, Lid)
);

CREATE TABLE Autor
(
	Aid INT PRIMARY KEY IDENTITY,
);

CREATE TABLE CartiAutor
(
	Cid INT FOREIGN KEY REFERENCES Carti(Cid),
	Aid INT FOREIGN KEY REFERENCES Autor(Aid),
	CONSTRAINT PK_CA PRIMARY KEY (Cid, Aid)
);

INSERT INTO Librarie (Nume, Adresa) VALUES ('Nume1', 'A');
INSERT INTO Librarie (Nume, Adresa) VALUES ('Nume2', 'A');

INSERT INTO Carti (Titlu) VALUES ('Carte1');
INSERT INTO Carti (Titlu) VALUES ('Carte2');

INSERT INTO Achitizie (Cid, Lid, DataA) VALUES (1,1,'10-20-2019');
INSERT INTO Achitizie (Cid, Lid, DataA) VALUES (1,2,'10-20-2019');
INSERT INTO Achitizie (Cid, Lid, DataA) VALUES (2,1,'10-20-2019');

--nume librarie si numar carti
SELECT L.Nume, COUNT(*)
FROM Achitizie A INNER JOIN Librarie L ON A.Lid = L.Lid
WHERE YEAR(A.DataA) > 2010
GROUP BY L.Lid, L.Nume

INSERT INTO CartiAutor (Cid, Aid) VALUES (1, 1);
INSERT INTO CartiAutor (Cid, Aid) VALUES (1, 2);
INSERT INTO CartiAutor (Cid, Aid) VALUES (2, 2);

SELECT L.Nume, L.Adresa, foo.Titlu, foo.numarAutori
FROM Librarie L INNER JOIN Achitizie A ON A.Lid = L.Lid 
				INNER JOIN (SELECT C.Titlu, COUNT(*) as numarAutori, C.Cid
							FROM Carti C INNER JOIN CartiAutor CA ON CA.Cid = C.Cid
							GROUP BY C.Cid, C.Titlu) as foo ON A.Cid = foo.Cid
WHERE foo.numarAutori = 2;
