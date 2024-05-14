--transaction 2
USE UniversityDBMS
GO

SET TRANSACTION ISOLATION LEVEL SNAPSHOT
-- solution ALTER DATABASE DBMS_Lab3 SET ALLOW_SNAPSHOT_ISOLATION OFF

BEGIN TRAN
SELECT * FROM Students WHERE StudentID = 33
-- the value from the beginning of the transaction
WAITFOR DELAY '00:00:10'
SELECT * FROM Students WHERE StudentID = 1
-- the value from the beginning of the transaction
UPDATE Students set FirstName='Very Optimistic' where StudentID=33
-- process will block
-- Process will receive Error 3960.
COMMIT TRAN
