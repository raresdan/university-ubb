CREATE DATABASE WomenShoes
USE WomenShoes

CREATE TABLE PresentationShops(
	PresentationShopID INT PRIMARY KEY,
	ShopName VARCHAR(50),
	City VARCHAR(50));

CREATE TABLE Women(
	WomanID INT PRIMARY KEY,
	FullName VARCHAR(50),
	ToSpend INT);

CREATE TABLE ShoeModels(
	ModelID INT PRIMARY KEY,
	ModelName VARCHAR(50),
	Season VARCHAR(50));

CREATE TABLE Shoes(
	ShoeID INT PRIMARY KEY,
	Price INT,
	ModelID INT,
	FOREIGN KEY (ModelID) REFERENCES ShoeModels(ModelID));

CREATE TABLE Sales(
	WomanID INT,
	ShoeID INT,
	Quantity INT,
	Price INT,
	FOREIGN KEY(WomanID) REFERENCES Women(WomanID),
	FOREIGN KEY(ShoeID) REFERENCES Shoes(ShoeID));

CREATE TABLE AvaliableShoes(
	PresentationShopID INT,
	ShoeID INT,
	Quantity INT,
	PRIMARY KEY (PresentationShopID, ShoeID),
	FOREIGN KEY(PresentationShopID) REFERENCES PresentationShops(PresentationShopID),
	FOREIGN KEY(ShoeID) REFERENCES Shoes(ShoeID));


INSERT INTO PresentationShops VALUES
(1, 'Benvenuit', 'Milan'),
(2, 'Nike', 'Los Angeles'),
(3, 'New Balance', 'Paris');


INSERT INTO Women VALUES
(1, 'Andreea', 50000),
(2, 'Emiliy', 70000),
(3, 'Alexia', 60000);


INSERT INTO ShoeModels VALUES
(1, 'Summer Sandals', 'Summer'),
(2, 'Winter Boots', 'Winter'),
(3, 'Casual Sneakers', 'Spring');


INSERT INTO Shoes VALUES
(1, 49, 1),
(2, 89, 2),
(3, 39, 3);


INSERT INTO Sales VALUES
(1, 1, 2, 99),
(2, 2, 1, 89),
(3, 3, 3, 119);

INSERT INTO AvaliableShoes VALUES
(1, 1, 10),
(2, 2, 5),
(3, 3, 8);

SELECT * FROM PresentationShops;
SELECT * FROM Women;
SELECT * FROM ShoeModels;
SELECT * FROM Shoes;
SELECT * FROM Sales;
SELECT * FROM AvaliableShoes;