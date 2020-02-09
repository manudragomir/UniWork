CREATE DATABASE Tenis

CREATE TABLE Jucatori
(
	Jid INT PRIMARY KEY IDENTITY,
	Puncte INT,
	Val INT,
	Nume VARCHAR(50)
);

CREATE TABLE Turnee
(
	Tid INT PRIMARY KEY IDENTITY,
	Loc VARCHAR(50),
);

CREATE TABLE Arene
(
	Aid INT PRIMARY KEY IDENTITY,
);

CREATE TABLE Partide
(
	J1 INT FOREIGN KEY REFERENCES Jucatori(Jid),
	J2 INT FOREIGN KEY REFERENCES Jucatori(Jid),
	pct1 INT,
	pct2 INT,
	val1 INT,
	val2 INT,
	castig INT FOREIGN KEY REFERENCES Jucatori(Jid)
	CONSTRAINT PK_P PRIMARY KEY(J1, J2)
);

CREATE OR ALTER PROCEDURE proced
@Turneu INT, @J1 INT, @J2 INT, @P1 INT, @P2 INT,
@V1 INT, @V2 INT, @JC INT 
AS BEGIN
	INSERT INTO Partide (J1, J2, pct1, pct2, val1, val2, castig) VALUES (@J1, @J2, @P1, @P2, @V1, @V2, @JC);
END;

INSERT INTO Jucatori (Nume, Puncte, Val) VALUES ('J1', 0, 0);
INSERT INTO Jucatori (Nume, Puncte, Val) VALUES ('J2', 0, 0);
INSERT INTO Jucatori (Nume, Puncte, Val) VALUES ('J3', 0, 0);
INSERT INTO Jucatori (Nume, Puncte, Val) VALUES ('J4', 0, 0);
INSERT INTO Jucatori (Nume, Puncte, Val) VALUES ('J5', 0, 0);


EXEC proced 0, 1, 2, 10, 5, 10, 5, 1;
EXEC proced 0, 1, 3, 10, 5, 10, 5, 1;
EXEC proced 0, 1, 4, 10, 5, 10, 5, 1;
EXEC proced 0, 1, 5, 10, 5, 10, 5, 1;
EXEC proced 0, 2, 3, 10, 5, 10, 5, 2;
EXEC proced 0, 2, 4, 10, 5, 10, 5, 2;
EXEC proced 0, 2, 5, 10, 5, 10, 5, 2;
EXEC proced 0, 3, 4, 10, 5, 10, 5, 3;
		

CREATE OR ALTER FUNCTION calc(@Jucator INT)
RETURNS INT AS
BEGIN

	DECLARE @contor INT=0;
	SELECT @contor = COUNT(*)
					 FROM Jucatori J INNER JOIN Partide P ON J.Jid = P.castig
					 WHERE J.Jid = @Jucator;
	RETURN @contor; 
END;




CREATE OR ALTER VIEW View1 AS
	SELECT JJ.Nume, dbo.calc(JJ.jid) as numarPartide
	FROM Jucatori JJ
GO

SELECT * FROM View1
ORDER BY numarPartide DESC;

CREATE OR ALTER FUNCTION usf_Function(@Jucator INT)
RETURNS @puncteSiValoare TABLE
(
	Puncte INT,
	Valoare INT
)
AS BEGIN
	DECLARE
		@Puncte INT = 0,
		@Valoare INT = 0;

	DECLARE @Puncte1 INT =   (SELECT SUM(P.pct1)
							  FROM Partide P
							  WHERE P.J1 = @Jucator
							  GROUP BY P.J1, P.pct1);

	IF @Puncte1 IS NULL
		SET @Puncte1 = 0;
	
	DECLARE @Puncte2 INT =   (SELECT SUM(P.pct2)
							  FROM Partide P
							  WHERE P.J2 = @Jucator
							  GROUP BY P.J2, P.pct2);
	
	IF @Puncte2 IS NULL
		SET @Puncte2 = 0;

	SET @Puncte = @Puncte1 + @Puncte2;

	DECLARE @Valoare1 INT =   ( SELECT SUM(P.val1)
								FROM Partide P
								WHERE P.J1 = @Jucator
								GROUP BY P.J1, P.val1);

	IF @Valoare1 IS NULL
		SET @Valoare1 = 0;
	
	DECLARE @Valoare2 INT =   (SELECT SUM(P.val2)
								FROM Partide P
								WHERE P.J2 = @Jucator
								GROUP BY P.J2, P.val2);

	IF @Valoare2 IS NULL
		SET @Valoare2 = 0;

	SET @Valoare = @Valoare1 + @Valoare2;

	BEGIN
        INSERT @puncteSiValoare
        SELECT @Puncte, @Valoare
    END;
    RETURN;
END;
GO
SELECT * FROM usf_Function(2);




