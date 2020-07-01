//Required Modules
const express = require("express");
const bodyParser = require("body-parser");

const app = express();
const port = 3000;

app.use(bodyParser.urlencoded({extended: true}));

app.get("/", function(req, res){
  res.sendFile(__dirname + "/index.html");
});

app.get("/bmicalculator", function(req, res){
  res.sendFile(__dirname + "/bmicalculator.html");
});

app.post("/", function(req, res){
  var num1 = Number(req.body.num1);
  var num2 = Number(req.body.num2);
  var result = num1 + num2;
  res.send("<h1>Your total is " + result + "</h1>");
});

app.post("/bmicalculator", function(req, res){
  var weight = Number(req.body.weight);
  var height = Number(req.body.height);
  var bmi = Math.round((703 * weight) / (height * height));
  res.send("<h1>Your BMI is " + bmi + "</h1>");
});

app.listen(port, function(){
  console.log("Server started on port 3000");
});