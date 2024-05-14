CREATE TABLE LogConcurrencyIssues (
	currentTime DATETIME,
	info VARCHAR(100),
	resource_type VARCHAR(100),
	request_mode  VARCHAR(100), 
	request_type  VARCHAR(100), 
	request_status  VARCHAR(100),
	request_session_id INT 
)


CREATE TABLE LogConcurrencyIssuesTemp (
	currentTime DATETIME,
	info VARCHAR(100),
	resource_type VARCHAR(100),
	request_mode  VARCHAR(100), 
	request_type  VARCHAR(100), 
	request_status  VARCHAR(100),
	request_session_id INT 
)

GO

CREATE OR ALTER PROCEDURE addLogConcurrencyIssue(@info VARCHAR(100)) AS
	INSERT INTO LogConcurrencyIssues 
	SELECT GETDATE(), @info, resource_type, request_mode, request_type, request_status, request_session_id 
	FROM sys.dm_tran_locks
	WHERE request_owner_type='TRANSACTION'
GO

SELECT * FROM sys.dm_tran_locks
GO

CREATE OR ALTER PROCEDURE addLogConcurrencyIssueTemp(@info VARCHAR(100)) AS
	INSERT INTO LogConcurrencyIssuesTemp
	SELECT GETDATE(), @info, resource_type, request_mode, request_type, request_status, request_session_id 
	FROM sys.dm_tran_locks
	WHERE request_owner_type='TRANSACTION'
GO


CREATE OR ALTER PROCEDURE ClearLogs AS
	DROP TABLE LogConcurrencyIssues
	CREATE TABLE LogConcurrencyIssues (
	currentTime DATETIME,
	info VARCHAR(100),
	resource_type VARCHAR(100),
	request_mode  VARCHAR(100), 
	request_type  VARCHAR(100), 
	request_status  VARCHAR(100),
	request_session_id INT )
GO