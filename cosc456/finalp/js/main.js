var numObjs = 4; //Number of obj files to load
var kmesh = [];
var dmesh = [];
var cmesh = [];
var cubemesh = [];
var objFiles = ["knight2.obj", "Dragon.obj", "Castle.obj", "cube.obj"];

function loadObjects(){
	//Send files to main loop
	for(var i = 0; i < objFiles.length; i++){
		executeMainLoop(objFiles[i], i);
	}
}

function executeMainLoop(filename, i){
    //jQuery ajax call to load the .obj file from the local directory
    $.ajax({
		async:true,
		url:"./"+filename,
		indexValue: i,
		success:function(data){
			numObjs--;
			objFiles[this.indexValue]=data;
			if(numObjs==0){
				processMesh();
			}
		}
	});
}

//function to load the mesh and setup the opengl rendering demo
function processMesh(){
	kmesh = {model: new modelLoader.Mesh(objFiles[0])}
	dmesh = {model: new modelLoader.Mesh(objFiles[1])}
	cmesh = {model: new modelLoader.Mesh(objFiles[2])}
	cubemesh = {model: new modelLoader.Mesh(objFiles[3])}
	
	//create a new model viewing demo
	var myDemo = new demo("glcanvas", cubemesh, kmesh, dmesh, cmesh);

	//setup the webgl context and initialize everything
	myDemo.init();

	//enter the event driven loop; ---- demo.js
	myDemo.MainLoop();
}
