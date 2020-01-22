/*
Samuel Leonard
sleonar5
6.sql
*/

SELECT SUM(price) FROM Booking, Room, Hotel
	WHERE CURDATE() BETWEEN Booking.dateFrom AND Booking.dateTo - INTERVAL 1 DAY
		AND Booking.hotelNo = Room.hotelNo AND Booking.roomNo = Room.roomNo
		AND Hotel.hotelName = 'Grosvenor Hotel' AND Hotel.hotelNo = Room.hotelNo;