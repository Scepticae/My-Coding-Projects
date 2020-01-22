<?php
    //Displays all Past Sections for a Particular Course
	//Teacher made comment that we could just pass the courseId
	
	//Connect to the Server
	include 'initDB.php';
	
	//Query Data from the Server
	$result = mysqli_query($conn, "SELECT s.* FROM SectionsHistory s, Courses c
		WHERE s.courseId = c.courseId AND c.courseId = '$argv[1]'");
	
	//Display list of sections for given course
	echo $argv[1] . ":\n";
	while($row = mysqli_fetch_array($result)){
		echo "\tSection: " . $row['sectionId'] . " " . $row['sectionSemester'] . " " . $row['sectionYear'] . "\n";
	}
?>