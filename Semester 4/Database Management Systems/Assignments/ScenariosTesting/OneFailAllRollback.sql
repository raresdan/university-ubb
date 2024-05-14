-- GRADE 3;
-- create a stored procedure that inserts data in tables that are in a m:n relationship; 
-- if one insert fails, all the operations performed by the procedure must be rolled back

USE UniversityDBMS;
GO

-- Procedure to add logging info
CREATE OR ALTER PROCEDURE addLog (@info VARCHAR(100), @error VARCHAR(100)) AS
	INSERT INTO LogTable VALUES (@info, @error, GETDATE())
GO

-- Procedure to add student
CREATE OR ALTER PROCEDURE addStudent(@FirstName varchar(50), @LastName varchar(50))
AS
	DECLARE @maxID int
	-- coalesce = returns the first non-null value in a list
	SET @maxID = (SELECT COALESCE(MAX(S.StudentID), 0) + 1 FROM Students s)

	IF (@FirstName is null OR @LastName is null)
	BEGIN
		RAISERROR('Student first and last name must not be null', 16, 1);
	END

	INSERT INTO Students(StudentID, FirstName, LastName) VALUES (@maxID, @FirstName, @LastName)
GO

-- Procedure to add course
CREATE OR ALTER PROCEDURE addCourse(@CourseName varchar(100))
AS
	DECLARE @maxID int
	-- coalesce = returns the first non-null value in a list
	SET @maxID = (SELECT COALESCE(MAX(c.CourseID), 0) + 1 FROM Courses c)

	IF (@CourseName is null)
	BEGIN
		RAISERROR('Course name must not be null', 16, 1);
	END

	IF EXISTS (SELECT 1 FROM Courses WHERE CourseName = @CourseName)
    BEGIN
        RAISERROR('Course name already exists in the database', 16, 1);
    END

	INSERT INTO Courses(CourseID, CourseName) VALUES (@maxID, @CourseName)
GO

-- Procedure to add enrollment of a student to a course
CREATE OR ALTER PROCEDURE addEnrollment(@StudentID INT , @CourseName VARCHAR(100))
AS
	DECLARE @CourseID INT
	SET @CourseID = (SELECT C.CourseID FROM Courses C WHERE C.CourseName = @CourseName)

	IF (@CourseID is null)
	BEGIN
		RAISERROR('Course does not exist', 16, 1);
	END
	IF (@StudentID is null)
	BEGIN
		RAISERROR('Student does not exist', 16, 1);
	END
	IF NOT EXISTS (SELECT 1 FROM Students WHERE StudentID = @StudentID)
    BEGIN
        RAISERROR('Student does not exist', 16, 1);
    END

	INSERT INTO Enrollments(StudentID, CourseID) VALUES (@StudentID, @CourseID);
GO

-- rollback scenario
CREATE OR ALTER PROCEDURE addRollbackScenario
AS
	BEGIN TRAN
	BEGIN TRY
		-- incorrect example
		/*
		EXEC addStudent 'Rares', 'Goia'
		EXEC addCourse 'Database Managing Systems'
		EXEC addEnrollment 1 ,'Economics'
		*/

		-- good example
		
		EXEC addStudent 'Rares', 'Goia'
		EXEC addCourse 'Database Managing Systems'
		EXEC addEnrollment 1 ,'Database Managing Systems'
		
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		EXEC addLog 'Transaction rollback', 'Something went wrong'
		RETURN
	END CATCH
	COMMIT TRAN
GO

-- Testing 
EXEC addRollbackScenario
GO
SELECT * FROM LogTable
GO

SELECT * FROM Students
SELECT * FROM Courses
SELECT * FROM Enrollments

-- Empty the tables 
DELETE Students
DELETE Courses
DELETE Enrollments
DELETE LogTable