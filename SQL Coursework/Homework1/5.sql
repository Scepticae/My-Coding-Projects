/*
Samuel Leonard
sleonar5
5.sql
*/

SELECT price, type FROM Room, Hotel
	WHERE hotelName = 'Grosvenor Hotel'
		AND Room.hotelNo = Hotel.hotelNo;