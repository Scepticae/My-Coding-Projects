//Creating an Object
var object1 = {
  name: "Sam",
  age: 43,
  job: "Software Developer"
};

var object2 = new Object();
object2.name = "John";
object2.age = 40;
object2.job = "Engineer";

var object3 = {};
object3.name = "Nicole";
object3.age = 40;
object3.job = "Instructor";

//Create Reusable Object
function Object4(name, age, job){
  this.name = name;
  this.age = age;
  this.job = job;
  //Create Function
  this.info = function(){
    return "Name: " + this.name + "Age: " + this.age + "Job: " + this.job;
  };
}

//Creating New Instance of Above
var newEmployee = new Object4("David", 13, "Kid");

//Binding
var infoObject = Object4.info; // Non-Binded
var bindedInfoBind = Object4.info.bind(Object4);