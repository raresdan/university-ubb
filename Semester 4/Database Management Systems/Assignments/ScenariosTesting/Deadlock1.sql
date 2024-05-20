USE UniversityDBMS

INSERT INTO Students VALUES (20, 'Dead', 'Lock')
INSERT INTO Courses VALUES (6, 'OS')
DELETE FROM Students WHERE StudentID = 20
DELETE FROM Courses WHERE CourseID = 6

SELECT * FROM Students
SELECT * FROM Courses

-- transaction 1
BEGIN TRAN
UPDATE Courses SET CourseName='Operating Systems' WHERE CourseID = 6

-- this transaction has exclusively lock on table Students
WAITFOR DELAY '00:00:10'
UPDATE Students SET FirstName='DeadLock' WHERE StudentID = 20
-- this transaction will be blocked because transaction 2 has already blocked our lock on table Courses
COMMIT TRAN
