USE SocialMediaApp
GO

CREATE OR ALTER PROCEDURE insertRows
	@nb_of_rows int,
	@table_name varchar(30)

AS
BEGIN

	SET @nb_of_rows = cast(@nb_of_rows as INT)

	DECLARE @counter int
	SET @counter = 1


	WHILE @counter <= @nb_of_rows
	BEGIN
		IF @table_name = 'Users'
		BEGIN
			DECLARE @username varchar(30)
			SET @username = 'user' + convert(varchar(6), @counter)
			INSERT INTO Users (UserID, Username) VALUES (@counter, @username)
		END

		IF @table_name = 'Posts'
		BEGIN
			DECLARE @post_id int
			SET @post_id = @counter + 200
			DECLARE @content varchar(30)
			SET @content = 'post' + CONVERT(varchar(6), (@counter + 200))
			INSERT INTO Posts (UserID, PostID, Content) VALUES (1, @post_id, @content)
		END

		IF @table_name = 'Groups'
		BEGIN
			DECLARE @group_name varchar(30)
			SET @group_name = 'Group' + CONVERT(varchar(6), @counter)
			INSERT INTO Groups(GroupID, GroupName, Description, CreatedByUserID) VALUES (1,@group_name, 'New Group', 1)
		END

		SET @counter = @counter + 1

	END
END

