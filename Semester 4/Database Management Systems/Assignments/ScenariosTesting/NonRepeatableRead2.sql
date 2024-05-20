-- transaction 2 -- start this LATER
-- A non-repeatable read is one in which data read twice inside the same transaction cannot be guaranteed 
-- to contain the same value.

use UniversityDBMS

-- Solution:
-- SET TRANSACTION ISOLATION LEVEL REPEATABLE READ

SET TRANSACTION ISOLATION LEVEL READ COMMITTED
BEGIN TRAN

	EXEC addLogConcurrencyIssue 'non-repeatable read - before select'

	SELECT * FROM Students

	EXEC addLogConcurrencyIssue 'non-repeatable read - between select'

	WAITFOR DELAY '00:00:05'

	SELECT * FROM Students

	EXEC addLogConcurrencyIssue 'non-repeatable read - after select'

COMMIT TRAN

SELECT * FROM LogConcurrencyIssues