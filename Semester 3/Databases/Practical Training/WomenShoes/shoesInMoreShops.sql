USE WomenShoes
GO

CREATE OR ALTER FUNCTION shoesInMoreShops (@numberOfShops INT)
RETURNS TABLE
AS
RETURN
	SELECT DISTINCT ShoeID, COUNT(PresentationShopID) as NumberOfShops
	FROM AvaliableShoes
	GROUP BY ShoeID
	HAVING COUNT(PresentationShopID) >= @numberOfShops
GO

SELECT * FROM AvaliableShoes
SELECT * FROM shoesInMoreShops(2)