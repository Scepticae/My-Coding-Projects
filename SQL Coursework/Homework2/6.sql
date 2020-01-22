/* 
	Samuel leonard
	sleonar5
	CS 465
	Homework II
	6.sql
*/

--Creates the table  CheckingOutToday
CREATE VIEW CheckingOutToday AS
	SELECT g.*, b.roomNo, DATEDIFF(b.dateTo, b.dateFrom) AS numDays,
			DATEDIFF(b.dateTo, b.dateFrom) * r.price AS totalCost
		FROM Guest g NATURAL JOIN Booking b NATURAL JOIN Room r
			WHERE curdate() = b.dateTo;
	
	
	
