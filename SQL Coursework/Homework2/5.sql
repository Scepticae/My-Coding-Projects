/* 
	Samuel leonard
	sleonar5
	CS 465
	Homework II
	5.sql
*/

--Create view HotelData
CREATE VIEW HotelData
	AS SELECT guestName, hotelName
		FROM Guest NATURAL JOIN Booking NATURAL JOIN HOTEL
			WHERE curdate() BETWEEN dateFrom AND dateTo - INTERVAL 1 DAY
			ORDER BY hotelName;