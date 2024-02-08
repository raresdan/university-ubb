USE BankOperations;
GO

CREATE OR ALTER PROCEDURE deleteTransactions @cardID INT
AS
BEGIN
	DELETE FROM Transactions
	WHERE CardID = @cardID;
END
GO

SELECT * FROM Transactions
deleteTransactions '2'