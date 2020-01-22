//Samuel Leonard
//sleonar5
//CS 465
//Homework 8.2

//Get References
$(document).ready(function() {
	$("#submit").click(function() {
		//Get the Username and Password
		var username = $("#username").val();
		var pwd = $("#pwd").val();

		//Send Data to Ajax
		$.post("login.php", {username: username, pwd: pwd}, function(response) {
			var msg = "";
			if(response == true){
				$("#error-msg").hide();
				window.location.href = "results.html";
			}
			else {
				$("#error-msg").html("Incorrect Username/Password!");
				$("#error-msg").show();
			}
		});

		//alert("User: " + username + " Password: " + pwd);
	});
});