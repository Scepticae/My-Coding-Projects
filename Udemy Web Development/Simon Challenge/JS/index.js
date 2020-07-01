var buttonColors = ["red", "blue", "green", "yellow"];
var gamePattern = [];
var userClickedPattern = [];
var gameStarted = false;
var level = 0;


//Start Game
$(document).keydown(function(){
  if(gameStarted === false){
    $("h1").text("Level  " + level);
    allowClicks();
    nextSequence();
    gameStarted = true;
  }
});

//Detect User Click on Button
function allowClicks(){
  $(".btn").on("click", function(){
    var userChosenColor = this.id;
    userClickedPattern.push(userChosenColor);
    animatePress(userChosenColor);
    playSound(userChosenColor);

    //Check Answer
    checkAnswer((userClickedPattern.length - 1));
  });
}

//Random Number Generator
function nextSequence(){
  var randomNumber = Math.floor(Math.random() * 4);
  var randomChosenColor = buttonColors[randomNumber];

  gamePattern.push(randomChosenColor);

  flashButton(randomChosenColor);
  playSound(randomChosenColor);

  //Increment Level
  level++;

  //Update the Heading to reflect current level
  $("h1").text("Level  " + level);
}

//Create Button Flash
function flashButton(pattern){
  $("." + pattern).fadeOut(100).fadeIn(100);
}

//Play Game Sound
function playSound(color){
  switch(color){
    case "red":
      var redAudio = new Audio("sounds/red.mp3");
      redAudio.play();
      break;

    case "blue":
      var blueAudio = new Audio("sounds/blue.mp3");
      blueAudio.play();
      break;

    case "green":
      var greenAudio = new Audio("sounds/green.mp3");
      greenAudio.play();
      break;

    case "yellow":
      var yellowAudio = new Audio("sounds/yellow.mp3");
      yellowAudio.play();
      break;

    default:
      console.log("Error");
  }
}

//Button Press Animation
function animatePress(color){
  $("." + color).addClass("pressed");
  setTimeout(function(){
    $("." + color).removeClass("pressed");
  }, 100);
}

//Check the answer
function checkAnswer(currentLevel){
  if(userClickedPattern[currentLevel] === gamePattern[currentLevel]){
    if((currentLevel + 1) === gamePattern.length){
      $("h1").text("Level Success!");
      setTimeout(nextSequence, 1500);
      userClickedPattern = [];
    }
  }
  else{
    $("h1").text("Wrong!");
    $(".btn").off("click");
    var wrongAnswer = new Audio("sounds/wrong.mp3");
    wrongAnswer.play();
    $("body").addClass("game-over");
    setTimeout(function(){
      $("body").removeClass("game-over");
    }, 200);
    setTimeout(resetGame, 1000);
  }
}

//Reset Game
function resetGame(){
  gameStarted = false;
  level = 0;
  gamePattern = [];
  userClickedPattern = [];
  $("h1").text("Game Over, Press any Key to Restart");
}
