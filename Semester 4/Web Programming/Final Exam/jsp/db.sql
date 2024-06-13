create database webexam;

use webexam;

create table Flights
(
	flightId int not null primary key AUTO_INCREMENT,
    date datetime not null,
    destinationCity VARCHAR(100) not null,
    availableSeats int not null
);

create table Hotels
(
	hotelId int not null primary key AUTO_INCREMENT,
    hotelName VARCHAR(100) not null,
    date datetime not null,
    city VARCHAR(100) not null,
	availableRooms int not null
);

create table  Reservations
(
	id int not null primary key AUTO_INCREMENT,
    person VARCHAR(100) not null,
    type VARCHAR(100) not null,
	idReservedResource int not null
);


insert into Flights 
values
		(1, '2024-06-15', 'New York', 150),
       (2, '2024-06-16', 'Los Angeles', 120),
       (3, '2024-06-17', 'Chicago', 200);


insert into Hotels 
values (1, 'Grand Hotel', '2024-06-15', 'New York', 50),
       (2, 'Sunset Inn', '2024-06-16', 'Los Angeles', 30),
       (3, 'Lakeside Resort', '2024-06-17', 'Chicago', 40);


insert into Reservations 
values (1, 'John', 'Flight', 1),
       (2, 'Dragos', 'Hotel', 2),
       (3, 'Rares Dan', 'Flight', 3);
       
       
select * from Flights;
select * from Hotels;
select * from Reservations;

drop table Reservations


    

