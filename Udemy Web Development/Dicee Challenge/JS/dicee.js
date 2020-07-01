var die = 0;
var dice1 = 6;
var dice2 = 6;

function randomDice() {
  die = Math.floor(Math.random() * 6) + 1;
  return die;
}

function winner(die1, die2) {
  if(die1 > die2){
    document.querySelector("h1").innerHTML = "🚩Player 1 Wins!";
  }
  else if(die1 < die2) {
    document.querySelector("h1").innerHTML = "Player 2 Wins!🚩";
  }
  else {
    document.querySelector("h1").innerHTML = "Draw!";
  }
}

function rollDice() {
  //Get two random dice rolls
  dice1 = randomDice();
  dice2 = randomDice();

  //Display Dice Rolled
  document.querySelector(".img1").setAttribute("src", "images/dice" + dice1 + ".png");
  document.querySelector(".img2").setAttribute("src", "images/dice" + dice2 + ".png");

  //Display Winner
  winner(dice1, dice2);
}

//Call rollDice when roll dice button is pushed
document.querySelector("button").addEventListener("click", rollDice);
