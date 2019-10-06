//Objects
var student = {
  firstname: "John",
  lastname: "Parker",
  age: 7
};

console.log(student);

var student1 = new Object();
student1.firstname = "John";
student1.lastname = "Parker";
student1.age = 7;

console.log(student1);

var student2 = {};
student2.firstname = "Sam";
student2.lastname = "Leonard";
student2.age = 43;

console.log(student2);

class students {
  constructor(firstname, lastname, age) {
    this.firstname = firstname;
    this.lastname = lastname;
    this.age = age;
  }
}

var jenny = new students("Jenny", "Loo", 5);

console.log(jenny);