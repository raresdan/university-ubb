USE UniversityDBMS

--Dirty Reads: transaction 1 start this one FIRST
--A dirty read occurs when a transaction reads data that has not yet been committed.

SELECT * FROM Students

INSERT INTO Students VALUES (7, 'Dirty', 'Read')
DELETE FROM Students WHERE StudentID = 7
GO

-- select everything from here until the delete
DECLARE @tempTable TABLE (
	currentTime DATETIME,
	info VARCHAR(100),
	resource_type VARCHAR(100),
	request_mode  VARCHAR(100), 
	request_type  VARCHAR(100), 
	request_status  VARCHAR(100),
	request_session_id INT 
)

BEGIN TRANSACTION

	INSERT INTO @tempTable(currentTime, info, resource_type, request_mode, request_type, request_status, request_session_id)
	SELECT GETDATE(), 'dirty read - before update', resource_type, request_mode, request_type, request_status, request_session_id 
	FROM sys.dm_tran_locks
	WHERE request_owner_type='TRANSACTION'

	UPDATE Students SET LastName='Write'
	WHERE StudentID = 7

	INSERT INTO @tempTable(currentTime, info, resource_type, request_mode, request_type, request_status, request_session_id)
	SELECT GETDATE(), 'dirty read - after update', resource_type, request_mode, request_type, request_status, request_session_id 
	FROM sys.dm_tran_locks
	WHERE request_owner_type='TRANSACTION'

	WAITFOR DELAY '00:00:10'
ROLLBACK TRANSACTION

SELECT * FROM @tempTable INSERT INTO LogConcurrencyIssues
SELECT * FROM LogConcurrencyIssues

-- until here
DELETE LogConcurrencyIssues