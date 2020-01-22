/* 
	Samuel leonard
	sleonar5
	CS 465
	Homework II
	4.sql
*/

--Creat a view named CurrentGuestCount that counts number of guests at each hotel
CREATE VIEW CurrentGuestCount
	AS SELECT hotelNo, COUNT(guestNo) AS guestCount
		FROM Booking
			WHERE CURDATE() BETWEEN dateFrom AND dateTo - INTERVAL 1 DAY
			GROUP BY hotelNo;