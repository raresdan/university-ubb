USE WomenShoes
GO

CREATE OR ALTER VIEW womanThatBoughtAtLeast2Shoes AS
	SELECT WomanID, SUM(Quantity) AS TotalQuantity
	FROM Sales
	GROUP BY WomanID
	HAVING SUM(Quantity) >= 2
GO

SELECT * FROM womanThatBoughtAtLeast2Shoes