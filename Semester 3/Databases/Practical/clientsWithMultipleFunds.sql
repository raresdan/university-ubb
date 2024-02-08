USE Funds
GO

CREATE OR ALTER FUNCTION clientsWithMultipleFunds ()
RETURNS TABLE
AS
RETURN
	SELECT I.InvestorID, C.ClientID, C.ClientName, MF.FundType
	FROM Investors I JOIN Clients C ON I.ClientID = C.ClientID
	JOIN MutualFunds MF ON I.FundID = MF.FundID
GO

SELECT * FROM clientsWithMultipleFunds()


SELECT * FROM MutualFunds
SELECT * FROM Investors