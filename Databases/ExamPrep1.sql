CREATE DATABASE Spatiu;

USE Spatiu;

CREATE TABLE RociPredominante
(
	rid INT PRIMARY KEY IDENTITY,
	denum VARCHAR(50),
	duritate VARCHAR(50),
	an INT,
);

INSERT INTO RociPredominante (denum, duritate, an) VALUES ('Magmatica', 'Duritate1', 1900); --5
INSERT INTO RociPredominante (denum, duritate, an) VALUES ('Metamorfica', 'Duritate2', 1950); --6
INSERT INTO RociPredominante (denum, duritate, an) VALUES ('Calcar', 'Duritate3', 1910); --7
INSERT INTO RociPredominante (denum, duritate, an) VALUES ('AltaRoca', 'Duritate4', 2000); --8

CREATE TABLE Planete
(
	pid INT PRIMARY KEY IDENTITY,
	nume VARCHAR(50),
	descr VARCHAR(50),
	dSoare INT,
	dPamant INT,
	rid INT FOREIGN KEY REFERENCES RociPredominante(rid)
);

INSERT INTO Planete (nume, descr, dSoare, dPamant, rid) VALUES ('Pamant', 'Apa', 1000, 0, 5);
INSERT INTO Planete (nume, descr, dSoare, dPamant, rid) VALUES ('Mercur', 'Mica', 10000, 100, 6);
INSERT INTO Planete (nume, descr, dSoare, dPamant, rid) VALUES ('Jupiter', 'Mare', 2000, 1000, 5);
INSERT INTO Planete (nume, descr, dSoare, dPamant, rid) VALUES ('Pluto', 'Descr', 3000, 50, 7);


CREATE TABLE Sateliti
(
	sid INT PRIMARY KEY IDENTITY,
	pid INT FOREIGN KEY REFERENCES Planete(pid),
	denum VARCHAR(50),
	marime INT,
	specific VARCHAR(50)
);

INSERT INTO Sateliti (pid, denum, marime, specific) VALUES (5, 'Luna', 100, 'Specif1');
INSERT INTO Sateliti (pid, denum, marime, specific) VALUES (7, 'Io', 100, 'Specif1');
INSERT INTO Sateliti (pid, denum, marime, specific) VALUES (7, 'Europa', 100, 'Specif2');
INSERT INTO Sateliti (pid, denum, marime, specific) VALUES (6, 'SatelitMercur', 100, 'Specif2');

CREATE TABLE Exploratori
(
	eid INT PRIMARY KEY IDENTITY,
	nume VARCHAR(50),
	gen INT,
	dataN DATE
);

INSERT INTO Exploratori (nume, gen, dataN) VALUES ('Prunariu', 1, '09-22-1967'); --2
INSERT INTO Exploratori (nume, gen, dataN) VALUES ('Armstrong', 1, '09-20-1928'); --3
INSERT INTO Exploratori (nume, gen, dataN) VALUES ('Laika', 2, '09-22-1960'); --4

CREATE TABLE Misiuni
(
	pid INT FOREIGN KEY REFERENCES Planete(pid),
	eid INT FOREIGN KEY REFERENCES Exploratori(eid),
	dataM DATE,
	descriere VARCHAR(50),
	CONSTRAINT PK_M PRIMARY KEY (pid, eid)
);

CREATE OR ALTER PROCEDURE usp_adaugaMisiune(@explorator INT, @planeta INT, @dataM DATE, @descriere VARCHAR(50))
AS BEGIN
	IF (EXISTS (SELECT 1 FROM Misiuni Where eid = @explorator AND pid = @planeta))
		UPDATE Misiuni SET dataM = @dataM, descriere = @descriere 
					   WHERE eid = @explorator AND pid = @planeta;
	ELSE
		INSERT INTO Misiuni (eid, pid, dataM, descriere) VALUES (@explorator, @planeta, @dataM, @descriere);
END;

EXEC usp_adaugaMisiune 2, 5, '01-07-1930', 'WOW';
EXEC usp_adaugaMisiune 2, 6, '05-05-2010', 'HEYA';
SELECT * FROM Misiuni;
EXEC usp_adaugaMisiune 2, 5, '02-02-1940', 'MEGAWOW';
EXEC usp_adaugaMisiune 3, 5, '01-01-2050', 'SF';

CREATE OR ALTER VIEW View1 AS
	SELECT P.nume, S.denum
	FROM Sateliti S INNER JOIN Planete P ON S.pid = P.pid;

GO
SELECT * FROM View1;

CREATE or ALTER FUNCTION MaxExploratori()
RETURNS INT AS
BEGIN
	DECLARE @maxi INT = 0;
	SELECT @maxi =  (SELECT MAX(foo.NumarExploratori)
					FROM (SELECT P.pid, COUNT(*) as NumarExploratori
						  FROM Misiuni M INNER JOIN Planete P ON M.pid = P.pid
						  GROUP BY P.pid) AS foo);
	RETURN @maxi;
END;

CREATE OR ALTER FUNCTION AfisPlanete(@roca INT)
RETURNS TABLE AS
	RETURN 
	        SELECT P.nume, COUNT(*) as NumarExploratori
			FROM Misiuni M INNER JOIN Planete P ON M.pid = P.pid
			WHERE P.rid = @roca
			GROUP BY P.pid, P.nume
			HAVING COUNT(*) =  (SELECT MAX(foo.NumarExploratori)
								FROM (SELECT P.pid, COUNT(*) as NumarExploratori
							 FROM Misiuni MM INNER JOIN Planete P ON MM.pid = P.pid
								GROUP BY P.pid) AS foo);

GO
SELECT P.nume, RP.rid FROM Planete P INNER JOIN Misiuni M ON M.pid = P.pid INNER JOIN RociPredominante RP ON RP.rid = P.pid;
SELECT * FROM AfisPlanete(5);