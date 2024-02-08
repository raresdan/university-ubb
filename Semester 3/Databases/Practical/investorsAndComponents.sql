USE Funds
GO

CREATE OR ALTER VIEW investorsAndComponents
AS
	SELECT I.InvestorID, C.ClientName, FC.ComponentID
	FROM Investors I JOIN Clients C ON I.ClientID = C.ClientID
	JOIN MutualFunds MF ON I.FundID = MF.FundID
	JOIN FundComponents FC ON MF.FundID = FC.FundID;
GO

SELECT * FROM investorsAndComponents