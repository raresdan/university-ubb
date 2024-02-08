CREATE DATABASE BankOperations;

USE BankOperations;

CREATE TABLE Customers (
	CustomerID INT PRIMARY KEY,
	CustomerName VARCHAR(50),
	DateOfBirth DATE);

CREATE TABLE BankAccounts(
	BankAccountID INT PRIMARY KEY,
	IBAN VARCHAR(24),
	Balance INT,
	CustomerID INT,
	FOREIGN KEY (CustomerID) REFERENCES Customers(CustomerID));

CREATE TABLE Cards(
	CardID INT PRIMARY KEY,
	CardNumber INT,
	CVV INT,
	BankAccountID INT,
	FOREIGN KEY (BankAccountID) REFERENCES BankAccounts(BankAccountID));

CREATE TABLE ATMs(
	ATMID INT PRIMARY KEY,
	Address VARCHAR(50));


CREATE TABLE Transactions(
	TransactionID INT PRIMARY KEY,
	TimeOfWithdrawal DATETIME,
	SumWithdrawed INT,
	CardID INT,
	ATMID INT,
	FOREIGN KEY (CardID) REFERENCES Cards(CardID),
	FOREIGN KEY (ATMID) REFERENCES ATMs(ATMID));

INSERT INTO Customers VALUES
    (1, 'Gica', '2000-01-01'),
    (2, 'Gulin', '2003-05-27'),
    (3, 'Dragos', '2003-10-17');

INSERT INTO BankAccounts VALUES
	(1, 'RO54RZBR3858514268674891', 2000, 1),
	(2, 'RO04RZBR1711787311512738', 10000, 1),
	(3, 'RO85PORL5457812918323614', 30000, 2),
	(4, 'RO30PORL3617216244955489', 500, 3);

INSERT INTO Cards VALUES
	(1, '461742', 807, 1),
	(2, '476894', 070, 1),
	(3, '477989', 856, 2),
	(4, '463215', 451, 3),
	(5, '470341', 415, 4);

INSERT INTO ATMs VALUES
	(1, 'strada Horea'),
	(2, 'strada Zorilor');

INSERT INTO Transactions VALUES
    (1, '2020-05-01 13:00:00', 500, 1, 1),
    (2, '2020-05-01 15:15:00', 700, 2, 1),
    (3, '2020-05-01 17:23:00', 50, 4, 2),
    (4, '2020-05-01 19:42:00', 150, 3, 2),
    (5, '2020-06-01 20:24:00', 20, 2, 2),
    (6, '2020-04-01 12:36:00', 200, 1, 1);


SELECT * FROM Customers
SELECT * FROM BankAccounts
SELECT * FROM Cards
SELECT * FROM ATMs
SELECT * FROM Transactions

USE master
DROP DATABASE BankOperations;
