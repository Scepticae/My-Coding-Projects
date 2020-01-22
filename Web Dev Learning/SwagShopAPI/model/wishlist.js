var mongoose = require('mongoose');
var Schema = mongoose.Schema;
var ObjectId = mongoose.Schema.Types.ObjectId;

//Create Model
var wishlist = new Schema({
  title: {type: String, default: "Cool Wish List"},
  products: [{type: ObjectId, ref: 'Product'}]
});

//Export Module to Database
module.exports = mongoose.model('WishList', wishlist);