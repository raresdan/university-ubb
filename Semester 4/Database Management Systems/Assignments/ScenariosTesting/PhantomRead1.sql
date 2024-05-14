-- The phantom read problem occurs when a transaction reads a variable once but when it tries to read that same 
-- variable again, an error occurs saying that the variable does not exist.

-- transaction 1
--Phantom Reads Part 1

-- make sure to not have id = 10
DELETE FROM Students WHERE StudentID = 10
SELECT * FROM Students


BEGIN TRAN

EXEC addLogConcurrencyIssue 'phantom read - before insert'

WAITFOR DELAY '00:00:06'
INSERT INTO Students(StudentID, FirstName, LastName) VALUES(10,'Phantom','Read')

EXEC addLogConcurrencyIssue 'phantom read - after insert'

COMMIT TRAN