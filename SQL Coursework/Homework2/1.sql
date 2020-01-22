/* 
	Samuel leonard
	sleonar5
	CS 465
	Homework II
	1.sql
*/

--Create the View that shows all rooms for Grosvenor Hotel
CREATE VIEW hotelRooms AS SELECT r.*
	FROM Hotel h NATURAL JOIN Room r
	WHERE h.hotelName = 'Grosvenor Hotel';
	
--Create the View that shows all rooms that are currently occupied
CREATE VIEW roomInfo AS SELECT hotelNo, roomNo, guestName
	FROM Booking NATURAL JOIN Guest
	WHERE CURDATE() BETWEEN dateFrom
		AND dateTo - INTERVAL 1 DAY;
		
--Merge Views to show all room status of Grosvenor Hotel
SELECT h.*, r.guestName
	FROM hotelRooms h LEFT JOIN roomInfo r
	ON h.hotelNo = r.hotelNo AND h.roomNo = r.roomNo;