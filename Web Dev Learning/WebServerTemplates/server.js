//Required Packages
var bodyParser = require('body-parser');
var express = require('express');
var mongoose = require('mongoose');

//Variables
var app = express();

//Connect to Database
var db = mongoose.connect('mongodb://localhost/swag-shop');

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({extended:false}));

app.listen(3000, function(){
  console.log("SwagShop API Running on Port: 3000...");
});