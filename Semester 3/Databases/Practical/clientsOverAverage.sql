USE Funds
GO


CREATE OR ALTER PROCEDURE clientsOverAverage (@bankID INT, @clientID INT)
AS
BEGIN
	    SELECT C.ClientName ,C.salary, MF.FundType 
		FROM Clients C JOIN ClientBankRelationship CB ON C.ClientID = CB.ClientID
		JOIN Banks B ON CB.BankID = B.BankID
		LEFT JOIN Investors I ON C.ClientID = I.ClientID
		LEFT JOIN MutualFunds MF ON I.FundID = MF.FundID
    WHERE 
        B.BankID = @bankID
        -- AND C.ClientID = @clientID
        AND C.salary > 1800;
END
GO


clientsOverAverage '1', '3'