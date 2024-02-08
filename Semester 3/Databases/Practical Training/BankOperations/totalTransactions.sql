USE BankOperations
GO

CREATE OR ALTER FUNCTION totalTransactions (@sum INT)
RETURNS TABLE
AS
RETURN
    SELECT C.CardNumber, C.CVV
    FROM Cards C JOIN Transactions T ON C.CardID = T.CardID
    GROUP BY C.CardNumber, C.CVV
    HAVING SUM(T.SumWithdrawed) > @sum
GO

SELECT * FROM totalTransactions(100)