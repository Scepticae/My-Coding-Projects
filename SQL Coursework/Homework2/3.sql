/* 
	Samuel leonard
	sleonar5
	CS 465
	Homework II
	3.sql
*/

--Create Table BookingOld
CREATE TABLE BookingOld (
	hotelNo int (4) DEFAULT NULL,
	guestNo int (7) DEFAULT NULL,
	dateFrom date DEFAULT NULL
		CHECK (dateFrom > CURDATE()),
	dateTo date DEFAULT NULL
		CHECK (dateTo > CURDATE()),
	roomNo int (3) DEFAULT NULL
		CHECK (roomNo BETWEEN 1 AND 100)
	/*
	CHECK (NOT EXISTS(SELECT r.roomNo FROM BookingOld r NATURAL JOIN BookingOld m
		WHERE r.dateFrom BETWEEN m.dateFrom AND m.dateTo - INTERVAL 1 DAY
			OR r.dateTo - INTERVAL 1 DAY BETWEEN m.dateFrom AND m.dateTo - INTERVAL 1 DAY))
	
	CHECK (NOT EXISTS (SELECT r.guestNo FROM BookingOld r NATURAL JOIN BookingOld m
		WHERE r.guestNo = m.guestNo))
	*/
);

--Insert all bookings before January 1st 2003 from Booking table
INSERT INTO BookingOld
	SELECT * FROM Booking
		WHERE dateTo < '2003-01-01';

--Delete all bookings before January 1st 2003 from Booking Table
DELETE FROM Booking
	WHERE dateTo < '2003-01-01';