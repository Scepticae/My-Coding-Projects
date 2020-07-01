var number = "";
var numbers = [];
var operators = [];
var num1 = 0;
var num2 = 0;
var result = 0;
var opPressed = false;

//Put a pressed number in display
var buttons = document.querySelectorAll("button");
for(var i = 0; i < buttons.length; i++) {
  buttons[i].addEventListener("click", function(){
    var pressed = this.innerHTML;
    showNumber(pressed);
  });
}

function showNumber(pressed) {
  if(pressed === "C") {
    number = "0";
    numbers = [];
    operators = [];
    num1 = 0;
    num2 = 0;
    result = 0;
    opPressed = false;
  }
  else if(pressed === "+" || pressed === "-" || pressed === "*" || pressed === "/") {
    if(numbers.length < 1) {
      num1 = Number(number);
      numbers.push(num1);
      operators.push(pressed);
    }
    else {
      num2 = Number(number);
      numbers.push(num2);

      if(pressed === "+") {
        result = add(numbers);
      }
      else if(pressed === "-") {
        result = subtract(numbers);
      }
      else if(pressed === "*") {
        result = multiply(numbers);
      }
      else if(pressed === "/") {
        result = divide(numbers);
      }

      number = String(result);
      numbers.pop();
      numbers.pop();
      operators.pop();
      numbers.push(result);
    }

    opPressed = true;
  }
  else {
    if(opPressed === true){
      number = "";
      opPressed = false;
    }
    else if(number === "0"){
      number = "";
    }

    number += pressed;
  }

  document.querySelector(".result").innerHTML = number;
}

function add(nums) {
  return nums[0] + nums[1];
}

function subtract(nums) {
  return num[0] - nums[1];
}

function multiply(nums) {
  return nums[0] * nums[1];
}

function divide(nums) {
  return nums[0] / nums[1];
}
