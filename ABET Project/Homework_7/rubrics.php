<?php
    //Displays the Rubrics Associated with the Outcomes of a Course
	//Connect to the Server
	include 'initDB.php';
	
	//Query Data from the Server
	$result = mysqli_query($conn, "SELECT r.* FROM Outcomes d, Courses c, CourseMapping m, Rubrics r
		WHERE d.outcomeId = m.outcomeId AND c.courseId = m.courseId AND d.outcomeMajor = m.outcomeMajor
			AND d.outcomeRubric = r.rubricId AND c.courseId = '$argv[1]' AND d.outcomeMajor = '$argv[2]'
			AND d.outcomeId = '$argv[3]'");
	
	$i = 0;
	
	//Display list of rubrics for course, major, and outcome
	echo $argv[1] . "-" . $argv[2] . "-" . $argv[3] . ":\n";
	while($row = mysqli_fetch_array($result)){
		if(($i % 3) == 0){
			echo "\t" . $row['rubricId'] . ":\n";
		}
		echo "\t\t" . $row['performanceLevel'] . ": " . $row['description'] . "\n";
		$i++;
	}
?>