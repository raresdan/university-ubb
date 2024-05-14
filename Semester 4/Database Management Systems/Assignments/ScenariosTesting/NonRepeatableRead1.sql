-- transaction 1 - start this FIRST
-- A non-repeatable read is one in which data read twice inside the same transaction cannot be guaranteed 
-- to contain the same value.

USE UniversityDBMS

INSERT INTO Students(StudentID, FirstName, LastName) VALUES (8, 'Non-Repetable','Write')
DELETE FROM Students WHERE StudentID = 8 
SELECT * FROM Students

BEGIN TRAN
	EXEC addLogConcurrencyIssue 'non-repeatable read - before update'

	WAITFOR DELAY '00:00:05'
	UPDATE Students SET LastName = 'Read' WHERE StudentID = 8

	EXEC addLogConcurrencyIssue 'non-repeatable read - after update'
COMMIT TRAN

SELECT * FROM LogConcurrencyIssues