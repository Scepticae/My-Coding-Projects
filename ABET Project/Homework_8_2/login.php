<!DOCTYPE html>
<html>
<head>
		<meta charset="UTF-8">
		<link rel="stylesheet" href="login.css">
		<script src="login.js"></script>
		<title>Login Result</title>
</head>
<body class="logError">
<?php
		//Variables
		$found = false;

		//Get Username and Password from Login Screen
		$name = isset($_POST['username']) ? $_POST['username'] : '';
		$pwd = isset($_POST['pwd']) ? $_POST['pwd'] : '';

		//Connect to the Server
		include 'initDB.php';
		
		//Query Data from the Server
		$result = mysqli_query($conn, "SELECT * FROM Instructors");

		//Display for successful or unsuccessful login
		while($row = mysqli_fetch_array($result)){
				if(($name === $row['instructorId']) && ($pwd === $row['instructorPassword'])){
						$found = true;
						echo $found;
				}
		}

		//Display Login failed if not found
		if($found == false){
				echo $found;
		}
?>
</body>
</html>
