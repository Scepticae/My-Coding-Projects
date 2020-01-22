<!DOCTYPE html>
<html>
<head>
		<meta charset="UTF-8">
		<link rel="stylesheet" href="login.css">
		<title>Login Result</title>
</head>
<body class="logError">
<?php
		//Variables
		$found = 0;

		//Get Username and Password from Login Screen
		$name = $_POST['username'];
		$pwd = $_POST['pwd'];

		//Connect to the Server
		include 'initDB.php';
		
		//Query Data from the Server
		$result = mysqli_query($conn, "SELECT * FROM Instructors");

		//Display for successful or unsuccessful login
		while($row = mysqli_fetch_array($result)){
				if(($name === $row['instructorId']) && ($pwd === $row['instructorPassword'])){
						echo "<h1>Login Succeeded</h1>";
						$found = 1;
				}
		}

		//Display Login failed if not found
		if($found == 0){
				echo "<h1>Login Failed</h1>";
		}
?>
</body>
</html>
