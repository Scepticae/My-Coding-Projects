//Required Packages
var bodyParser = require('body-parser');
var express = require('express');
var mongoose = require('mongoose');

//Variables
var app = express();

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({extended:false}));

//JSON Array of Ingredients
var Ingredients = [
  {
    "id":"3kfj4g",
    "text":"Eggs"
  },
  {
    "id":"2kcc5s",
    "text":"Strawberries"
  },
  {
    "id":"8hj92b",
    "text":"Bananas"
  },
  {
    "id":"3gx41a",
    "text":"Bacon"
  }
];

//GET Request
app.get('/', function(request, response){
  response.send('My Recipe API');
});

//GET Request
app.get('/ingredients', function(request, response){
  response.send(Ingredients);
});

//POST Request
app.post('/ingredients', function(req, res){
  var ingredient = req.body;

  //Error Checking
  if(!ingredient || ingredient.text === ""){
    res.status(500).send({error: "Ingredient must have text"});
  }
  else{
    Ingredients.push(ingredient);
    res.status(200).send({"Added":ingredient});
  }
});

//PUT Request
app.put('/ingredients/:ingredientId', function(req, res){
  var ingredientId = req.params.ingredientId;
  var newText = req.body.text;
  var found = false;

  //Error Handling for Missing Text
  if(!newText || newText === ""){
    res.status(500).send({error:"You must provide ingredient text"});
  }
  else{
    //Iterate through Ingredients
    for(var i = 0; i < Ingredients.length; i++){
      //Check Ingredient for a Match
      if(Ingredients[i].id === ingredientId){
        Ingredients[i].text = newText;
        found = true;
        break;
      }
    }

    //Check if Item was Found
    if(found){
      //Send Updated Ingredients List
      res.send(Ingredients);
    }
    else {
      res.status(500).send({error: "Ingredient id not found"});
    }
  }
});

app.listen(3000, function(){
  console.log("SwagShop API Running on Port: 3000...");
});