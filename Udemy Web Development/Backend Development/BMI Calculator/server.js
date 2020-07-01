const express = require("express");
const bodyParser = require("body-parser");

const app = express();
const port = 3000;

//Use the body parser
app.use(bodyParser.urlencoded({extended: true}));

//Send the HTML file
app.get("/", function(req, res){
  res.sendFile(__dirname + "/bmiCalculator.html");
});

//Send the CSS file
app.get("/styles.css", function(req, res){
  res.sendFile(__dirname + "/styles.css");
});

//Obtain the inputs
app.post("/", function(req, res){
  var weight = parseFloat(req.body.weight);
  var height = parseFloat(req.body.height);
  var bmi = 703 * weight / (height * height);

  res.send("<body style='background-color: lightblue'><h1 style='color: red'>Your BMI is " + bmi + "</h1></body>");
});


//Creates a listener for port traffic
app.listen(port, function(){
  console.log("Server connected to port 3000");
});