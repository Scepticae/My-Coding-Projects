<?php
    //Displays the Outcomes associated with the Course and Major
	//Connect to the Server
	include 'initDB.php';
	
	//Query Data from the Server
	$result = mysqli_query($conn, "SELECT d.* FROM Outcomes d, Courses c, CourseMapping m
		WHERE d.outcomeId = m.outcomeId AND c.courseId = m.courseId AND d.outcomeMajor = m.outcomeMajor
			AND c.courseId = '$argv[1]' AND d.outcomeMajor = '$argv[2]'");
	
	$i = 1;
	
	//Display list of outcomes for course and major
	echo $argv[1] . "-" . $argv[2] . ":\n";
	while($row = mysqli_fetch_array($result)){
		echo "\t" . $i . ": " . $row['outcomeDescription'] . "\n";
		$i++;
	}
?>