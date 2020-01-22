//Samuel Leonard
//sleonar5
//Homework 8 Part A
//deal.html, deal.css, deal.js

//Javascript to handle functionality of deal game
const money = [0.01, 1, 5, 10, 100, 1000, 10000, 100000, 500000, 1000000];

function startGame() {
	//Variables
	var num = 0;
	made = false;
	vals = [];
	pick = false;
	caseValue = 0;
	box = 0;
	
	//Reset the Variables since Globals
	amount = undefined;
	suitcases = undefined;
	sum = undefined;
	
	//Initialize the Game Board
	sum = 0;
	suitcases = 0;
	amount = 0;
	initBoard();
	
	//Set the Suitcases to their money values
	vals = setValues();
	
	//Calculate Total Case Value
	computeSum();
}

function initBoard() {
	//Enable Suitcases
	var name;
	for(var i = 1; i < 11; i++){
		name = 'button' + i;
		document.getElementById(name).style.backgroundColor = "lightblue";
		document.getElementById(name).style.color = "black";
		document.getElementById(name).style.fontWeight = "bold";
		document.getElementById(name).innerHTML = i;
		document.getElementById(name).disabled = false;
	}
	
	//Set Checkboxes Back to Unchecked
	for(var i = 1; i < 11; i++){
		name = 'b' + i;
		document.getElementById(name).checked = false;
	}
	
	//Set the Deal Box to Disabled
	document.getElementById("deal").disabled = true;
	
	//Set the Offer Box Value to ' '
	document.getElementById("offer").value = ' ';
	document.getElementById("offer").disabled = true;
	
	//Initialize all the Values
	for(var i = 0; i < 10; i++) {
		vals[i] = 0;
	}
}

function setValues() {
	var numVals = [];
	var temp = [];
	var indexedVals = [];
	
	//Set Random Values to numVals
	for(var i = 0; i < 10; i++){
		numVals[i] = Math.floor(Math.random() * 10000);
	}
	
	//Create Clone of Array
	temp = numVals.slice(0);
	
	//Sort the values of temp array
	temp = temp.sort();
	
	//Find the Index in Ascending Value
	for(var i = 0; i < 10; i++){
		for(var j = 0; j < 10; j++){
			if(temp[i] == numVals[j]){
				indexedVals[i] = money[j];
			}
		}
	}
	
	//Return the indexed array with money values
	return indexedVals;
}

//Functions for the Boxes
function button1(){
	var buttonOne = document.getElementById("button1");
	setPlay(buttonOne, 0);
}

function button2(){
	var buttonTwo = document.getElementById("button2");
	setPlay(buttonTwo, 1);
}

function button3(){
	var buttonThree = document.getElementById("button3");
	setPlay(buttonThree, 2);
}

function button4(){
	var buttonFour = document.getElementById("button4");
	setPlay(buttonFour, 3);
}

function button5(){
	var buttonFive = document.getElementById("button5");
	setPlay(buttonFive, 4);
}

function button6(){
	var buttonSix = document.getElementById("button6");
	setPlay(buttonSix, 5);
}

function button7(){
	var buttonSeven = document.getElementById("button7");
	setPlay(buttonSeven, 6);
}

function button8(){
	var buttonEight = document.getElementById("button8");
	setPlay(buttonEight, 7);
}

function button9(){
	var buttonNine = document.getElementById("button9");
	setPlay(buttonNine, 8);
}

function button10(){
	var buttonTen = document.getElementById("button10");
	setPlay(buttonTen, 9);
}

function setPlay(b, n){
	var tmp = 0;
	
	//Check if first pick
	if(pick == false){
		b.style.backgroundColor = "darkblue";
		b.style.color = "silver";
		b.style.fontWeight = "bold";
		caseValue = vals[n];
		box = b;
		pick = true;
	}
	else{
		//Change Button Color and Lock Suitcase Open
		b.innerHTML = vals[n];
		b.style.backgroundColor = "yellow";
		b.style.fontWeight = "bold";
		
		//Check the Checkbox associated with the suitcase
		for(var i = 1; i < 11; i++){
			name = 'b' + i;
			tmp = document.getElementById(name).value;
			
			if(tmp == vals[n]){
				document.getElementById(name).checked = true;
			}
		}
		
		//Check Number of cases
		checkCases();
		
		//Compute Offer
		computeOffer(n);
		
		//Enable Deal Button if more that one suitcase remains
		if(suitcases < 9){
			document.getElementById("deal").disabled = false;
		}
	}
	
	//Disable Button
	b.disabled = true;

	//Increment Cases
	suitcases++;
	
	//Checks if there is at least one other suitcase opened
	if(suitcases > 1 && suitcases < 10){
		//Send the Offer
		document.getElementById("offer").value = amount;
	}
}
	
function computeSum() {
	sum = 0;
	for (var i = 0; i < 10; i++){
		sum += vals[i];
	}
}

function computeOffer(n) {
	amount = 0;
	sum = sum - vals[n];
	amount = Math.floor(sum / (10 - suitcases) * 0.9);
}

function madeDeal() {
	//Check if Made Deal and Win the Offer
	alert("YOU TOOK THE DEAL\n   YOU WIN $" + amount);
	lockGame();
}

function checkCases() {
	if (suitcases == 9) {
		alert("You win $" + caseValue + " dollars!!!");
		
		//Lock Game
		lockGame();
		
		document.getElementById("offer").value = ' ';
		box.innerHTML = caseValue;
	}
}

function lockGame() {
	for(var i = 1; i < 11; i++){
		name = 'button' + i;
		document.getElementById(name).disabled = true;
	}
	
	//Lock out the Deal Button
	document.getElementById("deal").disabled = true;
	
	//Display Game Over
	alert("Game Over");
}