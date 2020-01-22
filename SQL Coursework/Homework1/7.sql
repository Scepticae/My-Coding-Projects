/*
Samuel Leonard
sleonar5
7.sql
*/

SELECT DISTINCT hotelNo, COUNT(hotelNo) AS count FROM Room
	GROUP BY hotelNo;