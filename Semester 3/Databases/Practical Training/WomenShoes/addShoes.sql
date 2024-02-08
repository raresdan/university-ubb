USE WomenShoes
GO

CREATE OR ALTER PROCEDURE addShoes (@presentationShopID INT, @shoeID INT, @quantity INT)
AS
BEGIN
	DECLARE @currentQuantity INT,
			@newQuantity INT;
	IF EXISTS (SELECT PresentationShopID, ShoeID 
				FROM AvaliableShoes 
				WHERE PresentationShopID = @presentationShopID AND ShoeID = @shoeID)
	BEGIN	
		SELECT @currentQuantity = Quantity 
        FROM AvaliableShoes 
        WHERE PresentationShopID = @presentationShopID AND ShoeID = @shoeID;
		SET @newQuantity = @currentQuantity + @quantity;
		 UPDATE AvaliableShoes 
        SET Quantity = @newQuantity
        WHERE PresentationShopID = @presentationShopID AND ShoeID = @shoeID;
	END
	ELSE
	BEGIN
		INSERT INTO AvaliableShoes (PresentationShopID, ShoeID, Quantity)
		VALUES (@presentationShopID, @shoeID, @quantity)
	END
END

GO

SELECT * FROM AvaliableShoes
addShoes '1', '2', '15'
addShoes '2', '2', '5'