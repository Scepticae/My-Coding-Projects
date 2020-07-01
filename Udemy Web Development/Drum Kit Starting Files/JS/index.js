for(var i = 0; i < document.querySelectorAll(".drum").length; i++){
  document.querySelectorAll(".drum")[i].addEventListener("click", function() {
    var buttonHTML = this.innerHTML;
    switchInstruments(buttonHTML);
    buttonAnimation(buttonHTML);
  });
}

document.addEventListener("keydown", function(event){
  switchInstruments(event.key);
  buttonAnimation(event.key);
});

function switchInstruments(selected){
  switch(selected){
    case "w":
      var tom1 = new Audio("sounds/tom-1.mp3");
      tom1.play();
      break;

    case "a":
      var tom2 = new Audio("sounds/tom-2.mp3");
      tom2.play();
      break;

    case "s":
      var tom3 = new Audio("sounds/tom-3.mp3");
      tom3.play();
      break;

    case "d":
      var tom4 = new Audio("sounds/tom-4.mp3");
      tom4.play();
      break;

    case "j":
      var bass = new Audio("sounds/kick-bass.mp3");
      bass.play();
      break;

    case "k":
      var snare = new Audio("sounds/snare.mp3");
      snare.play();
      break;

    case "l":
      var crash = new Audio("sounds/crash.mp3");
      crash.play();
      break;

    default:
      console.log("Error");
  }
}

function buttonAnimation(selected){
  document.querySelector("." + selected).classList.add("pressed");
  setTimeout(function(){
    document.querySelector("." + selected).classList.remove("pressed");
  }, 200);
}