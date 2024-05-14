-- GRADE 5
-- create a stored procedure that inserts data in tables that are in a m:n relationship; 
-- if an insert fails, try to recover as much as possible from the entire operation: 
-- for example, if the user wants to add a book and its authors, succeeds creating the authors, 
-- but fails with the book, the authors should remain in the database

USE UniversityDBMS
GO

CREATE OR ALTER PROCEDURE addRecoveryPossible (@FirstName VARCHAR(50), @LastName VARCHAR(50), @CourseName varchar(100))
AS
	BEGIN TRAN

	DECLARE @error VARCHAR(100)

	BEGIN TRY
		EXEC addStudent @FirstName, @LastName
		EXEC addLog 'Student added successfully!', '-'
	END TRY
	BEGIN CATCH
		SELECT @error = ERROR_MESSAGE()
		EXEC addLog 'Student not added!', @error
		COMMIT TRAN
		RETURN
	END CATCH

	BEGIN TRY
		EXEC addCourse @CourseName
		EXEC addLog 'Course added successfully!', '-'
	END TRY
	BEGIN CATCH
		SELECT @error = ERROR_MESSAGE()
		EXEC addLog 'Course not added!', @error
		COMMIT TRAN
		RETURN
	END CATCH

	BEGIN TRY
		DECLARE @StudentID INT
		SELECT @StudentID = StudentID FROM Students WHERE FirstName = @FirstName AND LastName = @LastName
		EXEC addEnrollment @StudentID, @CourseName
		EXEC addLog 'Enrollment added succcessfully!', '-'
	END TRY
	BEGIN CATCH
		SELECT @error = ERROR_MESSAGE()
		EXEC addLog 'Enrolment not added!', @error
		COMMIT TRAN
		RETURN
	END CATCH
	EXEC addLog 'All actions executed!', '-'

	COMMIT TRAN
GO


EXEC addRecoveryPossible 'Rares', 'Goia', 'Artificial Intelligence'
EXEC addRecoveryPossible 'Rares', 'Goia', null
EXEC addRecoveryPossible null, null, 'Object Oriented Programming'

SELECT * FROM Students
SELECT * FROM Courses
SELECT * FROM Enrollments

DELETE Students 
DELETE Courses 
DELETE Enrollments
DELETE LogTable
GO

SELECT * FROM LogTable