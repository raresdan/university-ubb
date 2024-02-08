CREATE DATABASE Funds
USE Funds

CREATE TABLE Clients (
    ClientID INT PRIMARY KEY,
    ClientName VARCHAR(55) ,
    Salary INT
);

CREATE TABLE Banks (
    BankID INT PRIMARY KEY,
    BankName VARCHAR(55)
);

CREATE TABLE ClientBankRelationship (
    ClientID INT,
    BankID INT,
    PRIMARY KEY (ClientID, BankID),
    FOREIGN KEY (ClientID) REFERENCES Clients(ClientID),
    FOREIGN KEY (BankID) REFERENCES Banks(BankID)
);


CREATE TABLE MutualFunds (
    FundID INT PRIMARY KEY,
    FundType VARCHAR(55),
    BankID INT,
    FOREIGN KEY (BankID) REFERENCES Banks(BankID)
);


CREATE TABLE FundComponents (
    ComponentID INT PRIMARY KEY,
    FundID INT,
    ActivityType VARCHAR(55),
    FOREIGN KEY (FundID) REFERENCES MutualFunds(FundID)
);


CREATE TABLE Investors (
    InvestorID INT PRIMARY KEY,
    ClientID INT,
    FundID INT,
    FOREIGN KEY (ClientID) REFERENCES Clients(ClientID),
    FOREIGN KEY (FundID) REFERENCES MutualFunds(FundID)
);


INSERT INTO Clients VALUES
	(1, 'Dan', 2000),
	(2, 'Costin', 3000),
	(3, 'Razvan', 2700)

INSERT INTO Banks VALUES
	(1, 'BT'),
	(2, 'ING'),
	(3, 'BRD')

INSERT INTO ClientBankRelationship VALUES
	(3, 1),
	(1, 1),
	(1, 2),
	(2, 3)

INSERT INTO MutualFunds VALUES
	(1, 'Invest', 1),
	(2, 'Savings', 2),
	(3, 'Donations', 2)

INSERT INTO FundComponents VALUES
	(1,1,'Stocks'),
	(2,3,'NFTs'),
	(3,2,'ETFs')

INSERT INTO Investors VALUES
	(1, 1, 1),
	(2, 1, 3),
	(3, 2, 1),
	(4, 2, 2)

SELECT * FROM Clients
SELECT * FROM Banks
SELECT * FROM ClientBankRelationship
SELECT * FROM MutualFunds
SELECT * FROM FundComponents
SELECT * FROM Investors