/*
Samuel Leonard
sleonar5
8.sql
*/

SELECT hotelName, COUNT(Room.hotelNo) AS count FROM Room, Hotel
	WHERE Hotel.city = 'London' AND Hotel.hotelNo = Room.hotelNo 
	GROUP BY Room.hotelNo;
