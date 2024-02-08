USE SocialMediaApp;
GO

CREATE TABLE Ta (
    aid int PRIMARY KEY,
    a2 int UNIQUE,
    x int
)

CREATE TABLE Tb (
    bid int PRIMARY KEY,
    b2 int,
    x int
)

CREATE TABLE Tc (
    cid int PRIMARY KEY,
    aid int REFERENCES Ta(aid),
    bid int REFERENCES Tb(bid)
)
GO

CREATE OR ALTER PROCEDURE insertIntoTa (@rows int) AS
    DECLARE @max int
    SET @max = @rows*2 + 100
    WHILE @rows > 0 
	BEGIN
        INSERT INTO Ta VALUES (@rows, @max, @rows%120)
        SET @rows = @rows-1
        SET @max = @max-2
    END
GO

CREATE OR ALTER PROCEDURE insertIntoTb (@rows int) AS
    WHILE @rows > 0 
	BEGIN
        INSERT INTO Tb VALUES (@rows, @rows%870, @rows%140)
        SET @rows = @rows-1
    END
GO

CREATE OR ALTER PROCEDURE insertIntoTc(@rows int) AS
    DECLARE @aid int
    DECLARE @bid int
    WHILE @rows > 0 
	BEGIN
        SET @aid = (SELECT TOP 1 aid FROM Ta ORDER BY NEWID())
        SET @bid = (SELECT TOP 1 bid FROM Tb ORDER BY NEWID())
        INSERT INTO Tc VALUES (@rows, @aid, @bid)
        SET @rows = @rows-1
    END
GO

EXEC insertIntoTa 90000
EXEC insertIntoTb 17000
EXEC insertIntoTc 5000

SELECT * FROM Ta
SELECT * FROM Tb
SELECT * FROM Tc

CREATE NONCLUSTERED INDEX index1 ON Ta(x)
DROP INDEX index1 ON Ta
    
SELECT * FROM Ta ORDER BY aid -- Clustered Index Scan
SELECT * FROM Ta WHERE aid = 1 -- Clustered Index Seek
SELECT x FROM Ta ORDER BY x -- Nonclustered Index Scan
SELECT a2 FROM Ta WHERE a2 = 1 -- Nonclustered Index Seek
SELECT x FROM Ta WHERE a2 = 21000 -- Key Lookup

SELECT * FROM Tb WHERE b2 = 55 -- Clustered Index Scan 0.03 cost

CREATE NONCLUSTERED INDEX index2 ON Tb(b2) INCLUDE (bid, x)
DROP INDEX index2 ON Tb

SELECT * FROM Tb WHERE b2 = 55 -- Nonclustered Index Seek 0.003 cost

GO
CREATE OR ALTER VIEW view1 AS
    SELECT TOP 1000 T1.x, T2.b2
    FROM Tc T3 join Ta T1 ON T3.aid = T1.aid join Tb T2 ON T3.bid = T2.bid
    WHERE T2.b2 > 500 and T1.x < 15
GO

SELECT * FROM view1

-- 0.24 total cost without indexes
-- 0.18 total cost with indexes	