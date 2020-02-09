CREATE DATABASE Vanzari;

USE Vanzari;
GO

CREATE TABLE Clienti
(
	Cid INT PRIMARY KEY IDENTITY,
	Denum VARCHAR(50),
	CodF INT
);

CREATE TABLE Agenti
(
	Aid INT PRIMARY KEY IDENTITY,
	Nume VARCHAR(50),
	Prenume VARCHAR(50)
);

CREATE TABLE Produse
(
	Pid INT PRIMARY KEY IDENTITY,
	Denum VARCHAR(50),
	Unitate VARCHAR(50)
);

ALTER TABLE Facturi
ALTER COLUMN DataE DATE;


CREATE TABLE Facturi
(
	NumarF INT PRIMARY KEY,
	DataE DATE,
	Cid INT FOREIGN KEY REFERENCES Clienti(Cid),
	Aid INT FOREIGN KEY REFERENCES Agenti(Aid)
);

CREATE TABLE ProdFact
(
	NumarF INT FOREIGN KEY REFERENCES Facturi(NumarF),
	Pid INT FOREIGN KEY REFERENCES Produse(Pid),
	pret FLOAT,
	cantitate FLOAT,
	NrOrdine INT IDENTITY,
	CONSTRAINT PK_Prod_Fact PRIMARY KEY(NumarF, Pid, NrOrdine, cantitate)
);

ALTER PROCEDURE usp_addProdusToFactura @Factura INT, @Produs INT, @NrOrdine INT, @Cantitate FLOAT, @Pret FLOAT 
AS BEGIN
	DECLARE @canti FLOAT = @Cantitate;
	IF((SELECT COUNT(*) 
		FROM ProdFact 
		WHERE ProdFact.NumarF = @Factura AND ProdFact.Pid = @Produs) != 0)
		SET @canti = -@Cantitate;

	INSERT INTO ProdFact (NumarF, Pid, pret, cantitate, NrOrdine) VALUES (@Factura, @Produs, @Pret, @canti, @NrOrdine);
END;

SELECT * FROM ProdFact;
DROP Table ProdFact;
EXEC usp_addProdusToFactura 1, 3, 1, 20, 305;
EXEC usp_addProdusToFactura 1, 2, 1, 20, 25;
EXEC usp_addProdusToFactura 2, 3, 1, 20, 307;

SELECT * FROM Facturi;
SELECT * FROM ProdFact;

CREATE OR ALTER VIEW View1 AS
	SELECT PF.NumarF as nrFactura, SUM(PF.Pret) as pret
	FROM Facturi F INNER JOIN ProdFact PF ON F.NumarF = PF.NumarF
	GROUP BY PF.NumarF
	HAVING SUM(PF.pret) > 310
GO

SELECT * FROM View1;

CREATE OR ALTER FUNCTION ufNume()
RETURNS INT 
AS BEGIN
	DECLARE @id INT = 0;
	SELECT @id = (SELECT TOP 1 Produse.Pid 
						From Produse
						WHERE Produse.Denum = 'Shaorma');
	RETURN @id;
END;

SELECT * FROM CLIENTI;
CREATE OR ALTER VIEW View2 AS
	SELECT DISTINCT PF.NumarF
	FROM ProdFact PF INNER JOIN Facturi F ON PF.NumarF = F.NumarF
	WHERE PF.Pid = dbo.ufNume();
GO

SELECT * FROM View2;

CREATE OR ALTER VIEW View3 AS
	SELECT DISTINCT F.NumarF, C.Denum, F.DataE, foo.pret
	FROM ProdFact PF INNER JOIN Facturi F ON PF.NumarF = F.NumarF INNER JOIN Clienti C ON F.Cid = C.Cid 
		INNER JOIN (SELECT PF.NumarF as nrFactura, SUM(PF.Pret) as pret, C.Denum
					FROM Facturi F INNER JOIN ProdFact PF ON F.NumarF = PF.NumarF INNER JOIN Clienti C ON C.Cid = F.Cid
					GROUP BY PF.NumarF, F.DataE, C.Denum
					HAVING SUM(PF.pret) > 300) as foo ON foo.nrFactura = PF.NumarF
	WHERE PF.NumarF IN (SELECT * FROM View2)
GO
SELECT * FROM View3;

CREATE OR ALTER FUNCTION ufFunction(@an INT)
RETURNS TABLE AS
	RETURN  SELECT foo.luna as luna, AA.Nume, AA.Prenume, foo.suma
			FROM  ( SELECT MONTH(F.DataE) as luna, YEAR(F.DataE) as an, A.Aid, SUM(PF.Pret) as suma
					FROM ProdFact PF INNER JOIN Facturi F ON PF.NumarF = F.NumarF INNER JOIN Agenti A ON A.Aid = F.Aid
					GROUP BY MONTH(F.DataE), YEAR(F.DataE), A.Aid, PF.NumarF) as foo INNER JOIN Agenti AA ON
					foo.Aid = AA.Aid
			WHERE foo.an = @an;

GO
SELECT *
FROM dbo.ufFunction(2019)
ORDER BY luna, Nume;

SELECT * FROM ProdFact;

