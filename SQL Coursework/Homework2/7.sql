/* 
	Samuel leonard
	sleonar5
	CS 465
	Homework II
	7.sql
*/

-- a) VALID; View Resolution
SELECT b.hotelNo AS hotelNo, r.roomNo AS roomNo
	FROM Room r, Booking b
		WHERE r.roomNo = b.roomNo AND r.hotelNo = b.hotelNo AND b.hotelNo = 1
		GROUP BY b.hotelNo, r.roomNo;

--b) INVALID; Aggregate function cannot be an argument to an aggregate function


--c) VALID; View Resolution
SELECT b.hotelNo AS hotelNo, r.roomNo AS roomNo, COUNT(*) AS bookingCount
	FROM Room r, Booking b
		WHERE  r.roomNo = b.roomNo AND r.hotelNo = b.hotelNo
			GROUP BY b.hotelNo, r.roomNo
			ORDER BY COUNT(*);