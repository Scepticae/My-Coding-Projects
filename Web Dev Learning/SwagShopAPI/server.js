//Required Packages
var bodyParser = require('body-parser');
var express = require('express');
var mongoose = require('mongoose');

//Import Database Modules
var Product = require('./model/product');
var WishList = require('./model/wishlist');

//Variables
var app = express();

//Connect to Database
var db = mongoose.connect('mongodb://localhost/swag-shop');

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({extended:false}));

//POST API
app.post('/product', function(request, response){
  //Create New Product
  var product = new Product();
  product.title = request.body.title;
  product.price = request.body.price;
  product.save(function(err, savedProduct){
    //Error Handling
    if(err){
      response.status(500).send({error:"Could not save product"});
    }
    else{
      response.status(200).send(savedProduct);
    }
  });
});

//GET API to Fetch Product
app.get('/product', function(request, response){
  //Find Product
  Product.find({}, function(err, products){
    //Error Handling
    if(err){
      response.status(500).send({error:"Unable to find product"});
    }
    else{
      response.send(products);
    }
  });
});

//Fetch Wishlists
app.get('/wishlist', function(request, response){
  WishList.find({}).populate({path:'products', model:'Product'}).exec(function(err, wishlists){
    if(err){
      response.status(500).send({error:"Could not find wishlists"});
    }
    else{
      response.status(200).send(wishlists);
    }
  });
});

//Create Wishlist POST
app.post('/wishlist', function(request, response){
  var wishList = new WishList();
  wishList.title = request.body.title;

  //Save New WishList
  wishList.save(function(err, newWishList){
    //Error Handling
    if(err){
      response.status(500).send({error:"Could not create wishlist"});
    }
    else{
      response.send(newWishList);
    }
  });
});

//Add Products to WishList
app.put('/wishlist/product/add', function(request, response){
  Product.findOne({_id: request.body.productId}, function(err, product){
    //Error Handling
    if(err){
      response.status(500).send({error:"Could not add item to list"})
    }
    else{
      WishList.update({_id: request.body.wishListId}, {$addToSet:{products: product._id}}, function(err, wishlist){
        if(err){
          response.status(500).send({error:"Unable to find wishlist to add product"});
        }
        else{
          response.send("Item added to wishlist");
        }
      });
    }
  });
});

app.listen(3000, function(){
  console.log("SwagShop API Running on Port: 3000...");
});