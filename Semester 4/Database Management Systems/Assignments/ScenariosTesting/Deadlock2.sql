USE UniversityDBMS

BEGIN TRAN
UPDATE Students SET FirstName='DeadLock' WHERE StudentID = 20
-- this transaction has exclusively lock on table Students
WAITFOR DELAY '00:00:10'
UPDATE Courses SET CourseName='Operating Systems' WHERE CourseID = 6
-- this transaction will be blocked because transaction 1 has exclusively lock on table Students, so, both of the transactions are blocked
COMMIT TRAN
-- after some seconds transaction 2 will be chosen as a deadlock victim and terminates with an error
-- in tables Students and Courses will be the values from transaction 1