const express = require("express");
const app = express();
const port = 3000;

//Request Response for my homepage
app.get("/", function(req, res){
  res.send("<h1>Hello World!</h1>");
});

//Request Response for contact page
app.get("/contact", function(req, res){
  res.send("<strong>Contact Me at scepticae@gmail.com</strong>");
});

//Req Res route for about page
app.get("/about", function(req, res){
  res.send("<p>My name is Samuel Leonard and I am a web developer.<br>I live in Knoxville, Tn and love riding my road bike.<br>I graduated from the University of Tennessee.</p>");
});

//Route for Hobbies page
app.get("/hobbies", function(req, res){
  res.send("<h1>My Hobbies</h1><ul><li>Coffee</li><li>Biking</li><li>Coding</li></ul>");
});

//Listening Port
app.listen(port, function(){
  console.log("Server started on port 3000");
});