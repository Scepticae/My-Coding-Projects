/* 
	Samuel leonard
	sleonar5
	CS 465
	Homework II
	2.sql
*/

--Check to see if tables exist and drop if they do
DROP TABLE IF EXISTS Room;
DROP TABLE IF EXISTS Booking;
DROP TABLE IF EXISTS Guest;

--Create the Room Table
CREATE TABLE Room (
	roomNo int (3) DEFAULT NULL
		CHECK (roomNo BETWEEN 1 AND 100),
	hotelNo int (4) DEFAULT NULL,
	type varchar(9) DEFAULT NULL
		CHECK (type IN('single', 'double', 'family')),
	price decimal(5,2) DEFAULT NULL
		CHECK (price BETWEEN 10 AND 100)
);

--Create the Booking Table
CREATE TABLE Booking (
	hotelNo int (4) DEFAULT NULL,
	guestNo int (7) DEFAULT NULL,
	dateFrom date DEFAULT NULL
		CHECK (dateFrom > CURDATE()),
	dateTo date DEFAULT NULL
		CHECK (dateTo > CURDATE()),
	roomNo int (3) DEFAULT NULL
		CHECK (roomNo BETWEEN 1 AND 100)
	/*
	CHECK (NOT EXISTS(SELECT r.roomNo FROM Booking r NATURAL JOIN Booking m
		WHERE r.dateFrom BETWEEN m.dateFrom AND m.dateTo - INTERVAL 1 DAY
			OR r.dateTo - INTERVAL 1 DAY BETWEEN m.dateFrom AND m.dateTo - INTERVAL 1 DAY))
	
	CHECK (NOT EXISTS (SELECT r.guestNo FROM Booking r NATURAL JOIN Booking m
		WHERE r.guestNo = m.guestNo))
	*/
);

--Create the Guest Table
CREATE TABLE Guest (
	guestNo int (7) DEFAULT NULL,
	guestName varchar (30) DEFAULT NULL,
	guestAddress varchar (50) DEFAULT NULL
);