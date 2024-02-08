USE SocialMediaApp
GO

CREATE OR ALTER PROCEDURE selectView
	@view_name varchar(30)
AS
BEGIN
	IF @view_name = 'UsersAgeView'
	BEGIN
		SELECT * FROM UsersAgeView
	END

	IF @view_name = 'UsersPostsView'
	BEGIN
		SELECT * FROM UsersPostsView
	end

	if @view_name = 'GroupAdminsView'
	begin
		SELECT * FROM GroupAdminsView
	end
END

 