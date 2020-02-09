USE Concurs;
GO

SELECT * FROM Student;
SELECT * FROM Liceu;
SELECT * FROM Profesor;
SELECT * FROM Pregatire;
SELECT * FROM Judet;

CREATE FUNCTION dbo.TestPunctaj(@pctTotal INT)
RETURNS INT
AS BEGIN
	IF(@pctTotal >= 0 AND @pctTotal <= 300)
		RETURN 1;
	RETURN 0;
END;

CREATE FUNCTION dbo.FindLiceu(@lid INT)
RETURNS INT
AS BEGIN
	IF(EXISTS(SELECT 1 FROM Liceu WHERE Liceu.lid = @lid))
		RETURN 1;
	RETURN 0;
END;

CREATE FUNCTION dbo.FindJudet(@jid INT)
RETURNS INT
AS BEGIN
	IF(EXISTS(SELECT 1 FROM Judet WHERE Judet.jid = @jid))
		RETURN 1;
	RETURN 0;
END;

CREATE OR ALTER PROCEDURE CRUDStudent
(@nume VARCHAR(50),
@pctTotal INT,
@clasa INT,
@liceu INT,
@judet INT,
@numberOfStudents INT OUTPUT)
AS BEGIN
	IF(dbo.TestPunctaj(@pctTotal) = 1 AND dbo.FindLiceu(@liceu) = 1 AND dbo.FindJudet(@judet) = 1)
		BEGIN
			SET NOCOUNT ON;
			DECLARE @id AS INT = (SELECT TOP 1 Student.sid FROM Student ORDER BY Student.sid DESC) + 1;

			--CREATE = INSERT
			INSERT INTO Student(sid,nume,pctTotal,clasa,liceu, judet) VALUES (@id, @nume, @pctTotal, @clasa, @liceu, @judet);

			--READ = SELECT
			SELECT * FROM Student;

			--UPDATE
			UPDATE Student SET Student.clasa = 10
			WHERE Student.clasa = 9;

			--DELETE
			DELETE FROM Student
			Where Student.pctTotal < 10;

			SET @numberOfStudents = (SELECT COUNT(*) FROM Student);
		END
	ELSE
		BEGIN 
			PRINT 'Date invalide'
			RETURN
		END
END;



--date invalide caci nu exista judetul cu jid 1
DECLARE @noStudents AS INT;
EXEC CRUDStudent 'TestName', 5, 9, 1, 1, @numberOfStudents = @noStudents OUTPUT;

--date corecte
DECLARE @noStudents AS INT;
EXEC CRUDStudent 'TestNameA', 5, 9, 1, 10, @numberOfStudents = @noStudents OUTPUT;
PRINT @noStudents;

CREATE FUNCTION dbo.numeValid(@nume VARCHAR(50))
RETURNS INT AS
BEGIN
	IF(@nume IS NOT NULL)
		RETURN 1;
	RETURN 0;
END;


CREATE OR ALTER PROCEDURE CRUDLiceu
(@nume VARCHAR(50))
AS BEGIN
	IF(dbo.numeValid(@nume) = 1)
		BEGIN
			SET NOCOUNT ON;
			DECLARE @lid as INT = (SELECT MAX(Liceu.lid) FROM Liceu) + 1;

			--CREATE = INSERT
			INSERT INTO Liceu (lid, nume) VALUES (@lid, @nume);

			--READ = SELECT
			SELECT * FROM Liceu;

			--UPDATE
			UPDATE Liceu SET Liceu.nume = CONCAT(Liceu.nume,'nou')
			WHERE Liceu.nume LIKE 'A%';
			SELECT * FROM Liceu;

			--DELETE
			DELETE FROM Liceu
			WHERE Liceu.nume LIKE '%nou';
			SELECT * FROM Liceu;
		END;
	ELSE
		PRINT 'Date invalide'
END;

EXEC CRUDLiceu 'Antipa';

CREATE FUNCTION dbo.locuriValide(@locuri INT)
RETURNS BIT AS
BEGIN
	IF(@locuri BETWEEN 1 AND 5)
		RETURN 1;
	RETURN 0;
END;


CREATE OR ALTER PROCEDURE CRUDJudet
(@nume VARCHAR(50),
@locuri INT
)
AS BEGIN
	IF(dbo.numeValid(@nume) = 1 AND dbo.locuriValide(@locuri) = 1)
		BEGIN
			SET NOCOUNT ON;
			DECLARE @jid as INT = (SELECT MAX(Judet.jid) FROM Judet) + 1;

			--CREATE = INSERT
			INSERT INTO Judet(jid, nume, locuri) VALUES (@jid, @nume, @locuri);

			--READ = SELECT
			SELECT * FROM Judet;

			--UPDATE
			UPDATE Judet SET Judet.nume = CONCAT(Judet.nume,'nou')
			WHERE Judet.nume LIKE 'O%';
			SELECT * FROM Judet;

			--DELETE
			DELETE FROM Judet
			WHERE Judet.nume LIKE '%nou';
			SELECT * FROM Judet;
		END;
	ELSE
		PRINT 'Date invalide'
END;

--valida
EXEC CRUDJudet 'Oradea', 3;

--invalida
EXEC CRUDJudet 'Oradea', 10;

CREATE FUNCTION dbo.checkVarsta(@varsta AS INT)
RETURNS BIT AS 
BEGIN
	IF(@varsta BETWEEN 20 AND 65)
		RETURN 1;
	RETURN 0;
END;

CREATE FUNCTION dbo.getProfesori()
RETURNS TABLE
AS
	RETURN SELECT * FROM Profesor;

CREATE OR ALTER PROCEDURE CRUDProfesor
(@nume AS VARCHAR(50), 
@varsta AS INT)
AS BEGIN
	IF(dbo.numeValid(@nume) = 1 AND dbo.checkVarsta(@varsta) = 1)
		BEGIN
			SET NOCOUNT ON;
			DECLARE @ppid as INT = (SELECT MAX(Profesor.ppid) FROM Profesor) + 1;

			--CREATE = INSERT
			INSERT INTO Profesor (ppid, nume, varsta) VALUES (@ppid, @nume, @varsta);

			--READ = SELECT
			SELECT * FROM dbo.getProfesori();
			
			--UPDATE
			UPDATE Profesor SET Profesor.nume = CONCAT(Profesor.nume,'nou')
			WHERE Profesor.nume LIKE 'K%';
			SELECT * FROM Profesor;

			--DELETE
			DELETE FROM Profesor
			WHERE Profesor.nume LIKE '%nou';
			SELECT * FROM Profesor;
		END;
	ELSE
		PRINT 'ERROR';
END;

--valid
EXEC CRUDProfesor KProfesorNume, 36;

--invalid
EXEC CRUDProfesor KProfesor, 75;

CREATE FUNCTION dbo.checkExistingProfesor(@ppid INT)
RETURNS BIT 
AS BEGIN
	IF(@ppid IN (SELECT Profesor.ppid FROM Profesor))
		RETURN 1;
	RETURN 0;
END;

CREATE FUNCTION dbo.checkExistingStudent(@sid INT)
RETURNS BIT 
AS BEGIN
	IF(@sid IN (SELECT Student.sid FROM Student))
		RETURN 1;
	RETURN 0;
END;

CREATE OR ALTER PROCEDURE CRUDPregatire
(@ppid INT,
@sid INT,
@ore INT,
@numarPregatiri INT OUTPUT)
AS BEGIN
	SET NOCOUNT ON;
	IF(dbo.checkExistingProfesor(@ppid) = 1 AND dbo.checkExistingStudent(@sid) = 1)
		BEGIN
			--CREATE = INSERT
			BEGIN TRY
			INSERT INTO Pregatire (ppid, sid, ore) VALUES (@ppid, @sid, @ore);
			END TRY

			BEGIN CATCH
			UPDATE Pregatire SET Pregatire.ore = @ore
			WHERE Pregatire.ppid = @ppid AND Pregatire.sid = @sid;
			END CATCH;

			--READ = SELECT
			SELECT * FROM Pregatire;

			--UPDATE
			UPDATE Pregatire SET Pregatire.ore = @ore + 1
			WHERE Pregatire.ore > 10;
			SELECT * FROM Pregatire;

			--DELETE
			DELETE FROM Pregatire
			WHERE Pregatire.ore > 20;
			SELECT * FROM Pregatire;

			SET @numarPregatiri = (SELECT COUNT(*) FROM Pregatire);
		END;
	ELSE
		PRINT 'Nu exista profesorul sau studentul'	
END;

--invalida
DECLARE @nrOutput AS INT;
EXEC CRUDPregatire 1, 0, 0, @numarPregatiri = @nrOutput OUTPUT;
PRINT @nrOutput;

--valida dar existenta
DECLARE @nrOutput AS INT;
EXEC CRUDPregatire 1, 3, 20, @numarPregatiri = @nrOutput OUTPUT;
PRINT @nrOutput;

--valida si inexistenta
DECLARE @nrOutput AS INT;
EXEC CRUDPregatire 1, 1, 20, @numarPregatiri = @nrOutput OUTPUT;
PRINT @nrOutput;

SELECT * FROM Pregatire;

--VIEW-URI
ALTER VIEW View1 AS
	SELECT AVG(S.pctTotal) AS MediePeClasa FROM Student S INNER JOIN Pregatire P ON P.sid = S.sid INNER JOIN Profesor PR ON PR.ppid = P.ppid
	GROUP BY S.clasa;

SELECT * FROM View1;

DROP INDEX N_idx_Student_clasa ON Student;
CREATE NONCLUSTERED INDEX N_idx_Student_clasa ON Student(clasa ASC);

CREATE OR ALTER VIEW View2 AS
	SELECT Liceu.nume 
	FROM Liceu 
	WHERE Liceu.nume LIKE 'S%';
GO

DROP INDEX N_idx_Liceu_Nume ON Liceu;
CREATE NONCLUSTERED INDEX N_idx_Liceu_Nume ON Liceu(nume ASC);

SELECT * FROM View2;