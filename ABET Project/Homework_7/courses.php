<?php
	//Finds the current courses being taught by an instructor
	//Connect to the Server
	include 'initDB.php';
	
	//Query Data from the Server
	$result = mysqli_query($conn, "SELECT c.* FROM Courses c, Instructors i, SectionsCurrent s
		WHERE i.instructorId = s.instructorId AND s.courseId = c.courseId AND i.instructorId = '$argv[1]'");

	//Display list of courses for instructor
	echo $argv[1] . ":\n";
	while($row = mysqli_fetch_array($result)){
		echo "\t" . $row['courseId'] . "   " . $row['courseTitle'] . "\n";
	}
?>