USE UniversityDBMS

--Dirty Reads: transaction 2 start this one LAST
--A dirty read occurs when a transaction reads data that has not yet been committed.

--What do we need to obtain? 
/* For id=7
-> for the FIRST SELECT, the language is romanian (because of the update from the first transaction). 
-> After  10 seconds, the first transaction has a rollback, so the update is cancelled. 
-> So, when the SECOND transaction SELECTS again from books, the language will be the initial one (english)
*/

SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED -- to allow dirty read
-- solution: 
-- SET TRANSACTION ISOLATION LEVEL READ COMMITTED -- to fix dirty read

BEGIN TRAN
	EXEC addLogConcurrencyIssue 'dirty read - before first select'
	SELECT * FROM Students
	EXEC addLogConcurrencyIssue 'dirty read - after first select'

	WAITFOR DELAY '00:00:15'

	EXEC addLogConcurrencyIssue 'dirty read - before second select'
	SELECT * FROM Students
	EXEC addLogConcurrencyIssue 'dirty read - after second select'
COMMIT TRAN