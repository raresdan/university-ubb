USE SocialMediaApp
GO

CREATE TABLE Versions
(
	Number int PRIMARY KEY IDENTITY(1,1),
	Actions nvarchar(255)
);
DROP TABLE Versions
SELECT * FROM Versions ORDER BY Number DESC;
GO

-- Modify the type of a column
CREATE PROCEDURE modifyColumnType( @Table VARCHAR(50), @ColumnName VARCHAR(50), @NewType VARCHAR(50)) 
AS
	DECLARE @SQLStatement NVARCHAR(MAX);
	DECLARE @DataType VARCHAR(50);
	SELECT @DataType = DATA_TYPE FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = @Table and COLUMN_NAME = @ColumnName;
	SET @SQLStatement = 'ALTER TABLE ' + @Table + 
						' ALTER COLUMN ' + @ColumnName + ' ' + @NewType;
	EXEC sp_executesql @SQLStatement;
	INSERT INTO Versions values ('modifyColumnType '''+@Table + ''', '''+@ColumnName+''', '+@DataType);

GO


-- Add new column in the table
CREATE PROCEDURE addColumn( @Table VARCHAR(50), @ColumnName VARCHAR(50), @ColType VARCHAR(50)) 
AS
	DECLARE @SQLStatement NVARCHAR(MAX);

	SET @SQLStatement = 'ALTER TABLE ' + @Table + 
						' ADD ' + @ColumnName + ' ' + @ColType;
	EXEC sp_executesql @SQLStatement;
	INSERT INTO Versions values ('removeColumn '''+@Table + ''', '''+@ColumnName+''' ');

GO


-- Remove a column from a table
CREATE PROCEDURE removeColumn( @Table VARCHAR(50), @ColumnName VARCHAR(50)) 
AS
	DECLARE @SQLStatement NVARCHAR(MAX);
	DECLARE @DataType VARCHAR(50);
	SELECT @DataType = DATA_TYPE FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = @Table and COLUMN_NAME = @ColumnName;
	SET @SQLStatement = 'ALTER TABLE ' + @Table + 
						' DROP COLUMN ' + @ColumnName;
	EXEC sp_executesql @SQLStatement;
	INSERT INTO Versions values ('addColumn '''+@Table + ''', '''+@ColumnName+''', '+@DataType);

GO

-- Add a DEFAULT constraint
ALTER PROCEDURE addDefaultConstraint( @Table VARCHAR(50), @ColumnName VARCHAR(50), @DefaultConstraint VARCHAR(50), @DefaultValue VARCHAR(50)) 
AS
	DECLARE @SQLStatement NVARCHAR(MAX);
	SET @SQLStatement = 'ALTER TABLE ' + @Table + 
						' ADD CONSTRAINT ' + @DefaultConstraint + 
						' DEFAULT ' + @DefaultValue + ' FOR ' + @ColumnName;
	EXEC sp_executesql @SQLStatement;
	INSERT INTO Versions values ('removeConstraint '''+@Table + ''','''+@ColumnName+''', '''+@DefaultConstraint+'''');

GO

-- Add primary key to a column
ALTER PROCEDURE addPrimaryKey( @Table VARCHAR(50), @ColumnName VARCHAR(50), @DefaultConstraint VARCHAR(50)) 
AS
	DECLARE @SQLStatement NVARCHAR(MAX);
	SET @SQLStatement = 'ALTER TABLE ' + @Table + 
						' ADD CONSTRAINT ' + @DefaultConstraint + 
						' PRIMARY KEY (' + @ColumnName + ')';
	EXEC sp_executesql @SQLStatement;
	INSERT INTO Versions values ('removeConstraint '''+@Table + ''','''+@ColumnName+''', '''+@DefaultConstraint+'''');

GO

-- Add new candidate key to a group of columns
ALTER PROCEDURE addCandidateKey( @Table VARCHAR(50), @ColumnNames VARCHAR(50), @DefaultConstraint VARCHAR(50)) 
AS
	DECLARE @SQLStatement NVARCHAR(MAX);
	SET @SQLStatement = 'ALTER TABLE ' + @Table + 
						' ADD CONSTRAINT ' + @DefaultConstraint + 
						' UNIQUE (' + @ColumnNames + ')';
	EXEC sp_executesql @SQLStatement;
	INSERT INTO Versions values ('removeConstraint '''+@Table + ''','''+@ColumnNames+''', '''+@DefaultConstraint+'''');

GO

-- Add a new foreign key
ALTER PROCEDURE addForeignKey( @Table VARCHAR(50), @ForeignColumnName VARCHAR(50), @DefaultConstraint VARCHAR(50),
								@ReferenceTable VARCHAR(50), @ReferenceColumn VARCHAR(50)) 
AS
	DECLARE @SQLStatement NVARCHAR(MAX);
	SET @SQLStatement = 'ALTER TABLE ' + @Table + 
						' ADD CONSTRAINT ' + @DefaultConstraint + 
						' FOREIGN KEY (' + @ForeignColumnName + ')' +
						' REFERNCES ' + @ReferenceTable + '(' + @ReferenceColumn + ')';
	EXEC sp_executesql @SQLStatement;
	INSERT INTO Versions values ('removeConstraint '''+@Table + ''','''+@ForeignColumnName+''', '''+@DefaultConstraint+'''');

GO

-- remove a set constraint
ALTER PROCEDURE removeConstraint( @Table VARCHAR(50), @ColumnName VARCHAR(50), @DefaultConstraint VARCHAR(50)) 
AS
	DECLARE @SQLStatement NVARCHAR(MAX);
	SET @SQLStatement = 'ALTER TABLE ' + @Table + 
						' DROP CONSTRAINT ' + @DefaultConstraint;
	EXEC sp_executesql @SQLStatement;
	INSERT INTO Versions values ('removeConstraint '''+@Table + ''', '''+@ColumnName+''', '''+@DefaultConstraint+'''');

GO

-- create a new table
CREATE PROCEDURE createTable( @Name VARCHAR(50)) 
AS
	DECLARE @SQLStatement NVARCHAR(MAX);
	SET @SQLStatement = 'CREATE TABLE ' + @Name + 
						'(ID INT IDENTITY(1,1));';
	EXEC sp_executesql @SQLStatement;
	INSERT INTO Versions values ('dropTable '''+@Name + '''');

GO

-- drop a table
CREATE PROCEDURE dropTable( @Name VARCHAR(50)) 
AS
	DECLARE @SQLStatement NVARCHAR(MAX);
	SET @SQLStatement = 'DROP TABLE ' + @Name;
	EXEC sp_executesql @SQLStatement;
	INSERT INTO Versions values ('createTable '''+@Name + '''');

GO

CREATE PROCEDURE restoreVersion(@Version INT)
AS
	DECLARE @Number INT , @Action NVARCHAR(255)
	DECLARE VersionCursor CURSOR FOR 
		SELECT Number, Actions
		FROM Versions
		ORDER BY Number DESC
	OPEN VersionCursor

	FETCH VersionCursor INTO @Number, @Action;
	IF @Number >= @Version
	BEGIN
		EXEC sp_executesql @Action
	END

	WHILE @@FETCH_STATUS = 0
	BEGIN
		FETCH VersionCursor INTO @Number, @Action;
		IF @Number >= @Version
		BEGIN
			EXEC sp_executesql @Action
		END
	END

	CLOSE VersionCursor
	DEALLOCATE VersionCursor
GO

-- Test the procedures

createTable 'NewTable';
addPrimaryKey 'NewTable', 'ID', 'PK'
addColumn 'NewTable', 'NewColumn', 'INT'
modifyColumnType 'NewTable', 'NewColumn', 'VARCHAR(30)'
addDefaultConstraint 'NewTable', 'NewColumn', 'Constr', '''Empty message'''
removeConstraint 'NewTable', 'NewColumn', 'Constr'
removeColumn 'NewTable', 'NewColumn'
dropTable 'NewTable';

SELECT * FROM NewTable;

SELECT * FROM INFORMATION_SCHEMA.TABLE_CONSTRAINTS

DROP TABLE Versions;
CREATE TABLE Versions
(
	Number int PRIMARY KEY IDENTITY(1,1),
	Actions nvarchar(255)
);

SELECT * FROM Versions ORDER BY Number DESC;
restoreVersion 1;
 