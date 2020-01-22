/*
Samuel Leonard
sleonar5
2.sql
*/

SELECT * FROM Room
	WHERE price < 40 AND type IN('double', 'family')
	ORDER BY price;
	