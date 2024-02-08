USE SocialMediaApp
GO

CREATE OR ALTER PROCEDURE mainTest

AS
BEGIN
	
	DECLARE @all_start datetime
	SET @all_start = GETDATE();

	DECLARE @table_name varchar(30)
	DECLARE delete_cursor CURSOR FOR
	SELECT Name FROM Tables;
	OPEN delete_cursor;
	FETCH NEXT FROM delete_cursor INTO @table_name;

	while @@FETCH_STATUS = 0
	BEGIN
		EXECUTE deleteRows @table_name;
		FETCH NEXT FROM delete_cursor INTO @table_name;
	END

	CLOSE delete_cursor
    DEALLOCATE delete_cursor

	DECLARE @test_id int
	DECLARE @test_name varchar(30)
	DECLARE @table_id int
	DECLARE @no_of_rows int
	DECLARE @position int

	DECLARE insert_cursor CURSOR FOR
		SELECT TestTables.TestID, Tests.Name, TestTables.TableID, TestTables.NoOfRows, TestTables.Position, Tables.Name
		FROM TestTables
		INNER JOIN Tests on TestTables.TestId = Tests.TestId
		INNER JOIN Tables on TestTables.TableID = Tables.TableID
		ORDER BY TestTables.Position DESC;

	OPEN insert_cursor;
	FETCH NEXT FROM insert_cursor INTO @test_id, @test_name, @table_id, @no_of_rows, @position, @table_name;
	
	DECLARE @insert_start datetime
	DECLARE @insert_end datetime
	DECLARE @description varchar(50)
	DECLARE @testrun_id int


	WHILE @@FETCH_STATUS = 0
	BEGIN
		SET @insert_start = GETDATE();
		EXECUTE insertRows @no_of_rows, @table_name;
		SET @insert_end = GETDATE();
		SET @description = 'for the insert on ' + @test_name;

		INSERT INTO TestRuns(Description, StartAt, EndAt) VALUES (@description, @insert_start, @insert_end);
		SET @testrun_id = SCOPE_IDENTITY();
		INSERT INTO TestRunTables(TestRunID, TableID, StartAt, EndAt) VALUES (@testrun_id, @table_id, @insert_start, @insert_end);

		FETCH NEXT FROM insert_cursor INTO @test_id, @test_name, @table_id, @no_of_rows, @position, @table_name;
	END

	CLOSE insert_cursor;
    DEALLOCATE insert_cursor;

	DECLARE @view_id int;
	DECLARE @view_name varchar(30);

	DECLARE views_cursor cursor for
		SELECT TestViews.TestID, Tests.Name, TestViews.ViewID, Views.Name
		FROM TestViews
		INNER JOIN Tests on TestViews.TestId = Tests.TestId
		INNER JOIN Views on TestViews.ViewID = Views.ViewID

	OPEN views_cursor;
	FETCH NEXT FROM views_cursor INTO @test_id, @test_name,  @view_id, @view_name

	DECLARE @view_start datetime
	DECLARE @view_end datetime

	WHILE @@FETCH_STATUS = 0
	BEGIN
		SET @view_start = GETDATE();
		EXECUTE selectView @view_name;
		SET @view_end = GETDATE();
		SET @description = 'for the select on ' + @test_name;

		INSERT INTO TestRuns(Description, StartAt, EndAt) VALUES (@description, @view_start, @view_end)
		SET @testrun_id = SCOPE_IDENTITY()
		INSERT INTO TestRunViews(TestRunID, ViewID, StartAt, EndAt) VALUES (@testrun_id, @view_id, @view_start, @view_end)
		FETCH NEXT FROM views_cursor INTO @test_id, @test_name,  @view_id, @view_name
	END

	CLOSE views_cursor;
    DEALLOCATE views_cursor;

END

INSERT INTO Tables(Name) VALUES ('Users'), ('Posts'), ('Groups');
SELECT * FROM Tables;

INSERT INTO Tests(Name) VALUES ('T1'),('T2'),('T3');
INSERT INTO TestTables(TestID,TableID,NoOfRows,Position) VALUES (1,2,10000,1),(2,3,2000,2),(3,1,500,3);
SELECT * FROM Tests;
SELECT * FROM TestTables;

INSERT INTO Views (Name) VALUES ('UsersAgeView'), ('UsersPostsView'), ('GroupAdminsView');
SELECT * FROM Views;
INSERT INTO Tests(Name) Values('V1'),('V2'),('V3');
INSERT INTO TestViews(TestID, ViewID) VALUES (4,1), (5,2), (6,3);
SELECT * FROM TestViews;

SET IDENTITY_INSERT Users ON;
ALTER TABLE Users
ALTER COLUMN Email VARCHAR(255) NULL;
ALTER TABLE Users
ALTER COLUMN AGE INT NULL;

deleteRows Users;
deleteRows Posts;
deleteRows Groups;

EXECUTE mainTest;

SELECT * FROM TestRuns;
SELECT * FROM TestRunTables;
SELECT * FROM TestRunViews;

SELECT * FROM Users;
SELECT * FROM Posts;
SELECT * FROM Groups;

DELETE FROM TestTables;
DELETE FROM Tests WHERE TestID > 6;