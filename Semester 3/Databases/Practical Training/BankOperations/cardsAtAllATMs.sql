USE BankOperations
GO

CREATE OR ALTER VIEW cardsAtAllATMS
AS
	SELECT DISTINCT T.CardID, C.CardNumber
	FROM Transactions T JOIN Cards C 
	ON T.CardID = C.CardID
	WHERE NOT EXISTS (
		SELECT ATMID
		FROM ATMs
		WHERE ATMID NOT IN (
			SELECT ATMID 
			FROM Transactions 
			WHERE CardID = T.CardID)
);
GO

SELECT * FROM cardsAtAllATMS