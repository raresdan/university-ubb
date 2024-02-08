USE SocialMediaApp
GO

CREATE OR ALTER PROCEDURE deleteRows
	@table_name varchar(30)

AS
BEGIN
	
	DECLARE @last_row int

	IF @table_name = 'Users'
	BEGIN
		DELETE FROM Users
	END

	IF @table_name = 'Posts'
	BEGIN

		DELETE FROM Posts 
	END

	IF @table_name = 'Groups'
	BEGIN
		DELETE FROM Groups
	END

END