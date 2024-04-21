create database EnterpriseWeb;

use EnterpriseWeb;

create table user
(
    userID   int          not null primary key AUTO_INCREMENT,
    name     varchar(100) not null,
    username varchar(100) not null,
    password varchar(100) not null,
    age      int          not null,
    role     varchar(100) not null,
    email    varchar(100) not null,
    webpage  varchar(100) not null
);


insert into user
VALUES ( 2, 'Goia Rares Dan', 'raresdan', '1234', 20, 'Data Scientist', 'goiararesdan@gmail.com', 'github.com/raresdan');


-- Test Users

INSERT INTO user (name, username, password, age, role, email, webpage) 
VALUES 
('John Doe', 'johndoe', 'password1', 30, 'Admin', 'john@example.com', 'https://www.example.com'),
('Jane Smith', 'janesmith', 'password2', 25, 'User', 'jane@example.com', 'https://www.example.com'),
('Alice Johnson', 'alicejohnson', 'password3', 35, 'Admin', 'alice@example.com', 'https://www.example.com'),
('Bob Brown', 'bobbrown', 'password4', 40, 'User', 'bob@example.com', 'https://www.example.com'),
('Emma Davis', 'emmadavis', 'password5', 27, 'Admin', 'emma@example.com', 'https://www.example.com'),
('Michael Wilson', 'michaelwilson', 'password6', 32, 'User', 'michael@example.com', 'https://www.example.com'),
('Sophia Martinez', 'sophiamartinez', 'password7', 38, 'Admin', 'sophia@example.com', 'https://www.example.com'),
('William Anderson', 'williamanderson', 'password8', 22, 'User', 'william@example.com', 'https://www.example.com'),
('Olivia Taylor', 'oliviataylor', 'password9', 29, 'Admin', 'olivia@example.com', 'https://www.example.com'),
('James Thomas', 'jamesthomas', 'password10', 34, 'User', 'james@example.com', 'https://www.example.com'),
('Emily White', 'emilywhite', 'password11', 26, 'Admin', 'emily@example.com', 'https://www.example.com'),
('Daniel Garcia', 'danielgarcia', 'password12', 31, 'User', 'daniel@example.com', 'https://www.example.com'),
('Charlotte Rodriguez', 'charlotterodriguez', 'password13', 33, 'Admin', 'charlotte@example.com', 'https://www.example.com'),
('Liam Martinez', 'liammartinez', 'password14', 28, 'User', 'liam@example.com', 'https://www.example.com'),
('Isabella Lee', 'isabellalee', 'password15', 37, 'Admin', 'isabella@example.com', 'https://www.example.com'),
('Benjamin Harris', 'benjaminharris', 'password16', 24, 'User', 'benjamin@example.com', 'https://www.example.com'),
('Mia Brown', 'miabrown', 'password17', 39, 'Admin', 'mia@example.com', 'https://www.example.com'),
('Ethan Wilson', 'ethanwilson', 'password18', 23, 'User', 'ethan@example.com', 'https://www.example.com'),
('Amelia Moore', 'ameliamoore', 'password19', 36, 'Admin', 'amelia@example.com', 'https://www.example.com'),
('Alexander Taylor', 'alexandertaylor', 'password20', 21, 'User', 'alexander@example.com', 'https://www.example.com');

select * from user