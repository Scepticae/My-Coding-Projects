<?php
	//Retreives prior assessement plans if there are any
	//I have only loaded the CS402 example from the web assignment into the database
	
	//Connect to the Server
	include 'initDB.php';
	
	//Query Outcome Data from the Server
	$result = mysqli_query($conn, "SELECT r.* FROM Courses c, SectionsHistory s, OutcomeResults r
		WHERE s.courseId = c.courseId AND s.sectionId = r.sectionId AND c.courseId = '$argv[1]' 
		AND r.outcomeMajor = '$argv[2]' AND r.outcomeId = '$argv[3]'");

	//Display list of results for an outcome
	echo "Course: " . $argv[1] . " Major: " . $argv[2] . " OutcomeId: " . $argv[3] . ":\n";
	echo "   Outcome Results:\n";
	while($row = mysqli_fetch_array($result)){
		echo "\t" . $row['performanceLevel'] . ":   " . $row['numberOfStudents'] . "\n";
	}
	
	//Query Assessment Data from the Server
	$result = mysqli_query($conn, "SELECT a.* FROM Courses c, SectionsHistory s, Assessments a
		WHERE s.courseId = c.courseId AND s.sectionId = a.sectionId AND c.courseId = '$argv[1]' 
		AND a.outcomeMajor = '$argv[2]' AND a.outcomeId = '$argv[3]'");

	//Display list of assessments and their weights for the course outcome
	echo "   Assessments:\n";
	while($row = mysqli_fetch_array($result)){
		echo "\t" . $row['assessmentDescription'] . ":   " . $row['weight'] . "\n";
	}
	
	//Query Narrative Data from the Server
	$result = mysqli_query($conn, "SELECT n.* FROM Courses c, SectionsHistory s, Narratives n
		WHERE s.courseId = c.courseId AND s.sectionId = n.sectionId AND c.courseId = '$argv[1]' 
		AND n.outcomeMajor = '$argv[2]' AND n.outcomeId = '$argv[3]'");

	//Display list of Narratives for course outcome
	echo "   Narratives:\n";
	$row = mysqli_fetch_array($result);
	echo "\tStrengths: " . $row['strengths'] . "\n\n";
	echo "\tWeaknesses: " . $row['weaknesses'] . "\n\n";
	echo "\tActions: " . $row['actions'] . "\n";
	
?>