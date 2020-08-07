var number = "0";
var numbers = [];
var num = 0;
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
    num = 0;
    result = 0;
    opPressed = false;
  }
  else if(pressed === "+" || pressed === "-" || pressed === "*" || pressed === "/" || pressed === "=") {
    if(numbers.length < 1) {
      num = Number(number);
      numbers.push(num);
    }
    else {
      num = Number(number);
      numbers.push(num);

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
    }
  }
  else {
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
