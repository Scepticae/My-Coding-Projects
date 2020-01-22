<?php
	//Connect to the Server
	include 'initDB.php';
	
	//Get Form Data
	$course = $_POST['Courses'];
	$major = $_POST['Major'];
	$outcomeId = $_POST['Outcomes'];
	$assType = $_POST['AssessTypes'];
	$description = $_POST['AssessmentDescription'];
	$weight = $_POST['Weight'];
	$rubricId = $_POST['Rubrics'];
	$notMeets = $_POST['NME'];
	$meets = $_POST['ME'];
	$exceeds = $_POST['EE'];
	
	//Find Section ID
	//Query Data from the Server
	$result = mysqli_query($conn, "SELECT s.* FROM SectionsHistory s, Courses c
	WHERE c.courseId = s.courseId AND c.courseId = '$course'");
	$row = mysqli_fetch_array($result);
	$sectionId = $row['sectionId'];
	
	//Insert Outcome Result Statements
	$outcomeResult1 = "INSERT INTO OutcomeResults VALUES($sectionId, '$outcomeId', '$major', 'NME', $notMeets)";
	$outcomeResult2 = "INSERT INTO OutcomeResults VALUES($sectionId, '$outcomeId', '$major', 'ME', $meets)";
	$outcomeResult3 = "INSERT INTO OutcomeResults VALUES($sectionId, '$outcomeId', '$major', 'EE', $exceeds)";

	//Send Outcome Result Data to DataBase
	if(mysqli_query($conn, $outcomeResult1)){
		echo "Outcome Result for Not Meets Expectations Saved.";
	}
	else{
		echo "Error: Outcome Result for Not Meets Expectations did not Save.\n";
		echo mysqli_error($conn);
	}
	if(mysqli_query($conn, $outcomeResult2)){
		echo "Outcome Result for Meets Expectations Saved.";
	}
	else{
		echo "Error: Outcome Result for Meets Expectations did not Save.\n";
		echo mysqli_error($conn);
	}
	if(mysqli_query($conn, $outcomeResult3)){
		echo "Outcome Result for Exceeds Expectations Saved.";
	}
	else{
		echo "Error: Outcome Result for Exceeds Expectations did not Save.\n";
		echo mysqli_error($conn);
	}

	//Saves the Assessment for the Outcome
	$assessmentResult = "INSERT INTO Assessments VALUES($sectionId, $assType, '$outcomeId', '$major', '$description', '$rubricId', $weight)";
	if(mysqli_query($conn, $assessmentResult)){
		echo "Assessment Saved.";
	}
	else{
		echo "Error: Assessment Result did not Save.\n";
		echo mysqli_error($conn);
	}
	
	mysqli_close($conn);
?>
