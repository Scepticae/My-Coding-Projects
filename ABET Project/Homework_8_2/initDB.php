<?php
	//Start Session
	session_start();
	
	//Connect to the Server
	$conn = mysqli_connect("dbs.eecs.utk.edu", "sleonar5", "Gordon#24", "cs465_sleonar5");
			
	//Test Connection
	if(mysqli_connect_errno()){
			echo "Failed to connect to Server: " . mysqli_connect_error();
	}
?>