USE Concurs;
GO

--view-urile
ALTER VIEW View1 AS
	SELECT * FROM Profesor;
GO

ALTER VIEW View2 AS
	SELECT DISTINCT S.nume FROM Pregatire P INNER JOIN Student S ON S.sid = P.sid INNER JOIN Profesor Pr ON Pr.ppid = P.ppid;
GO

ALTER VIEW View3 AS
	SELECT COUNT(S.clasa) AS Ore FROM Pregatire P INNER JOIN Student S ON S.sid = P.sid INNER JOIN Profesor Pr ON Pr.ppid = P.ppid
	GROUP BY S.clasa;
GO

CREATE VIEW View4 AS
	SELECT AVG(Student.pctTotal) as Medie FROM Student;
GO

CREATE VIEW View5 AS
	SELECT COUNT(*) AS Contor FROM Student WHERE Student.pctTotal < 100;
GO

ALTER PROCEDURE StudentInsertion
AS
BEGIN
	SET NOCOUNT ON;
	declare @number INT; SET @number = (SELECT RAND()*(300));
	declare @clasa INT; SET @clasa = (SELECT RAND()*(13-9)+9);
	declare @id INT; SET @id = (SELECT TOP 1 MAX(Student.sid) FROM Student);
	declare @judet INT; SET @judet = (SELECT TOP 1 Judet.jid FROM Judet);
	declare @liceu INT; SET @liceu = (SELECT TOP 1 Liceu.lid FROM Liceu);
	declare @nume VARCHAR(50); SET @nume = CONCAT('Student', (SELECT CAST(@id as varchar(50))));

	if @id is NULL
		SET @id = 0;
	INSERT INTO Student (sid, nume, pctTotal, clasa, judet, liceu) VALUES (@id+1, @nume , @number, @clasa, @judet, @liceu);
END

ALTER PROCEDURE ProfesorInsertion
AS
BEGIN
	SET NOCOUNT ON;
	declare @varsta INT; SET @varsta = (SELECT RAND()*(50-20)+20);
	declare @id INT; SET @id = (SELECT TOP 1 MAX(Profesor.ppid) FROM Profesor);

	if @id is NULL
		SET @id = 0;
	declare @nume VARCHAR(50); SET @nume = CONCAT('Profesor', (SELECT CAST(@id as varchar(50))));
	INSERT INTO Profesor (ppid, nume, varsta) VALUES (@id+1, @nume, @varsta);
END

ALTER PROCEDURE PregatireInsertion
AS
BEGIN
	SET NOCOUNT ON;
	declare @ore INT; SET @ore = (SELECT RAND()*(10-1)+1);
	declare @sid INT; SET @sid = (SELECT TOP 1 MAX(Student.sid) FROM Student);
	declare @ppid INT; SET @ppid = (SELECT TOP 1 MAX(Profesor.ppid) FROM Profesor);
	INSERT INTO Pregatire (sid, ppid, ore) VALUES (@sid, @ppid, @ore);
END

SELECT * FROM Pregatire;

ALTER PROCEDURE StudentDeletion
AS
BEGIN
	DELETE from Proba;
	DELETE from Student;
END

ALTER PROCEDURE ProfesorDeletion
AS
BEGIN 
	SET NOCOUNT ON;
	DELETE from Profesor;
END

CREATE PROCEDURE PregatireDeletion
AS
BEGIN
	SET NOCOUNT ON;
	DELETE from Pregatire;
END


EXEC sp_help Tests;


INSERT INTO TestTables (TestID, TableID, NoOfRows, Position) VALUES
		(1,1,500,2), (2,2,1000,3), (3,2,1500,3), (4,3,200,1), (5,3,5000,1);

INSERT INTO TestViews (TestID, ViewID) Values (1,1), (2,2), (3,3), (4,2), (5,3);

ALTER PROCEDURE toPosition @position INT, @op VARCHAR(50) AS BEGIN
	IF @op = 'Deletion'
	BEGIN
		declare @i INT = 1;
		while @i <= @position
			BEGIN
				declare @currTableId INT = (SELECT TOP 1 TestTables.TableID FROM TestTables WHERE TestTables.Position = @i);
				declare @currTableToOperate VARCHAR(50) = (SELECT Tables.Name FROM Tables WHERE Tables.TableID = @currTableID);
				declare @currCmd VARCHAR(50) = (CONCAT(@currTableToOperate, 'Deletion'));
				EXEC(@currCmd);
				SET @i = @i + 1;
			END
	END
	ELSE
		BEGIN
			SET @i = (SELECT TOP 1 TestTables.Position FROM TestTables ORDER BY TestTables.Position DESC);
			while @i >= @position
				BEGIN
					SET @currTableId = (SELECT TOP 1 TestTables.TableID FROM TestTables WHERE TestTables.Position = @i);
					SET @currTableToOperate = (SELECT Tables.Name FROM Tables WHERE Tables.TableID = @currTableID);
					SET @currCmd = (CONCAT(@currTableToOperate, 'Insertion'));
					EXEC(@currCmd);
					SET @i = @i - 1;
				END
		END
END;
GO

ALTER PROCEDURE toExecute @currTest INT AS BEGIN
	DECLARE @t1 DATETIME;
	DECLARE @t2 DATETIME;
	DECLARE @t3 DATETIME;

	declare @tableID INT; declare @viewID INT;
	
	declare @tableName VARCHAR(50) = (SELECT Tests.Name FROM Tests WHERE Tests.TestID = @currTest);
	
	declare @tableIDString VARCHAR(50) = (SELECT SUBSTRING(@tableName, 2, 1));
	SET @tableID = (SELECT CAST(@tableIDString AS INT));
	
	declare @viewIDString VARCHAR(50) = (SELECT SUBSTRING(@tableName, 4, 1));
	SET @viewID = (SELECT CAST(@viewIDString AS INT));

	declare @noOfRows INT = (SELECT TestTables.NoOfRows FROM TestTables WHERE TestTables.TableID = @tableID AND TestTables.TestID = @currTest);
	declare @position INT = (SELECT TestTables.Position FROM TestTables WHERE TestTables.TableID = @tableID AND TestTables.TestID = @currTest);

	declare @i INT = 0

	--INCEPEM TESTUL
	SET @t1 = GETDATE();

	--stergerea
	WHILE @i < @noOfRows
		BEGIN
			EXEC toPosition @position, 'Deletion';
			SET @i = @i + 1;
		END

	--inserarea
	SET @i = 0;
	WHILE @i < @noOfRows
		BEGIN
			EXEC toPosition @position, 'Insertion';
			SET @i = @i + 1;
		END
	
	SET @t2 = GETDATE();
	
	--AM TERMINAT TESTUL PE TABEL
	--INCEPEM TESTUL PE VIEW-URI
	declare @viewName VARCHAR(50) = (CONCAT('View', @viewIDString));
	EXEC('select * from [' + @viewName + ']');

	SET @t3 = GETDATE();
	--S-A TERMINAT TESTUL

	--inserez in TestRuns valorile testului curent
	INSERT INTO TestRuns (Description, StartAt, EndAt) 
			VALUES (CONCAT('S-a executat testul ', (SELECT CAST(@currTest AS varchar(1)))), @t1, @t3);
	
	--iau cheia adaugata
	declare @rid INT; SET @rid = (SELECT TOP 1 MAX(TestRuns.TestRunID) FROM TestRuns);
	
	--inserez rezultatele testului pe tabel 
	INSERT INTO TestRunTables (TestRunID, TableID, StartAt, EndAt)
			VALUES(@rid ,@tableId, @t1, @t2);
			
	--inserez rezultatele testului pe view
	INSERT INTO TestRunViews(TestRunID, ViewID, StartAt, EndAt)
			VALUES(@rid, @viewId, @t2, @t3);
END;

DELETE FROM TestRuns;
DELETE FROM TestRunTables;
DELETE FROM TestRunViews;

EXEC toExecute 3;
SELECT * FROM TestRuns;
SELECT * FROM TestRunTables;
SELECT * FROM TestRunViews;

SELECT * FROM Tests;
SELECT * FROM TestViews;
SELECT * FROM TestTables;

SELECT * FROM Pregatire;