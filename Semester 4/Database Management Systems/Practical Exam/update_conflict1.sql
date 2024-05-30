USE DBMSPractical

-- INSERT INTO StudentMember(studentid, name, role, teamid) VALUES (8, 'Dan','lead', 1)
-- DELETE FROM StudentMember WHERE studentid = 8 
-- SELECT * FROM StudentMember

BEGIN TRAN
	WAITFOR DELAY '00:00:05'
	UPDATE StudentMember SET role = 'data analyst' WHERE StudentID = 8
COMMIT TRAN
