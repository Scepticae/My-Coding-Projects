var valx = document.getElementById("valx");
var valy = document.getElementById("valy");
var results = document.getElementById("results");
var form = document.getElementById("formSubmit");

// Add Event Listener
form.addEventListener("submit", function(event){
  // Form Validation
  if(!valx.value || !valy.value){
    alert("Please Enter Numbers in the Fields");
  }else{
    var result = parseFloat(valx.value) / parseFloat(valy.value) * 100;
    results.innerText = "Result: " + result + "%";
    event.preventDefault();
  }
});