var gl = null; //our OpenGL handler

var GC = {};   //the graphics context

//initialize the graphics context variables
GC.shaderProgramKnight = null;             //our GLSL program
GC.shaderProgramDragon = null;             //our GLSL program
GC.shaderProgramCastle = null;             //our GLSL program
GC.shaderProgramCube = null;              //our GLSL program
GC.vertexPositionAttribute = null;  //location of vertex positions in GLSL program
GC.barycentricBuffer = null;          //array passed to shader to create wireframe display
GC.barycentricAttribute = null;      //location of barycentric coordinate array in GLSL program
GC.normalAttribute = null;
GC.perspectiveMatrix = null;          //the Perspective matrix
GC.mvMatrix = null;                      //the ModelView matrix
GC.mvMatrixStack = [];                 //the ModelView matrix stack
GC.meshCube = null;                    //The cube mesh
GC.meshKnight = null;                           //the knight mesh
GC.meshDragon = null;									//The dragon mesh
GC.meshCastle = null;                  //The castle mesh
GC.mouseDown = null;                 //boolean check for mouseDown
GC.width = 640;                           //render area width
GC.height = 480;                          //render area height

var camera = new ArcBall();              //create a new arcball camera
camera.setBounds(GC.width,GC.height);    //initialize camera with screen space dimensions


//demo constructor
function demo(canvasName, cubemesh, kmesh, dmesh, cmesh) {
    this.canvasName = canvasName;
		GC.meshCube = cubemesh;
    GC.meshKnight = kmesh;
		GC.meshDragon = dmesh;
		GC.meshCastle = cmesh;
}

//initialize webgl, populate all buffers, load shader programs, and start drawing
demo.prototype.init = function(){
    this.canvas = document.getElementById(this.canvasName);
    this.canvas.width = GC.width;
    this.canvas.height = GC.height;

    //Here we check to see if WebGL is supported 
    this.initWebGL(this.canvas);

    gl.clearColor(0.25,0.9,1.0,1.0);     //background to black
    gl.clearDepth(1.0);                 //set depth to yon plane
    gl.enable(gl.DEPTH_TEST);           //enable depth test
    gl.depthFunc(gl.LEQUAL);            //change depth test to use LEQUAL

    //set mouse event callbacks
    this.setMouseEventCallbacks();

    //set keyboard event callbacks
    this.setKeyboardEventCallbacks();

    //Get opengl derivative extension -- enables using fwidth in shader
    gl.getExtension("OES_standard_derivatives");
    
    //init the shader programs
    this.initShaders();

    //init the vertex buffer
    this.initGeometryBuffers();
		
		//Initialize the images
		this.initImages();
}

demo.prototype.MainLoop = function(){
    drawScene();
}

demo.prototype.setMouseEventCallbacks = function(){
    //-------- set callback functions
    this.canvas.onmousedown = this.mouseDown;
    this.canvas.onmousewheel = this.mouseWheel;

        //--Why set these to callbacks for the document object?
    document.onmouseup = this.mouseUp;          
    document.onmousemove = this.mouseMove;
    
        //--touch event callbacks
    this.canvas.ontouchstart = this.touchDown;
    this.canvas.ontouchend = this.touchUp;
    this.canvas.ontouchmove = this.touchMove;
    //-------- end set callback functions
}

demo.prototype.setKeyboardEventCallbacks = function(){
        //--Why set these to callbacks for the document object?
    document.onkeydown = this.keyDown;          
}

//the drawing function
function drawScene(){
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

		var m = GC.meshCube.model;
    var k = GC.meshKnight.model;
		var d = GC.meshDragon.model;
		var c = GC.meshCastle.model;
		
    //setup perspective and lookat matrices
    GC.perspectiveMatrix = makePerspective(45, GC.width/GC.height, 0.1, Math.max(9000.0, 9000.0));
    var lookAtMatrix = makeLookAt(camera.position[0],camera.position[1],camera.position[2],
                                  camera.lookAt[0],camera.lookAt[1],camera.lookAt[2],
                                  0,1,0);

    //set initial camera lookat matrix
    mvLoadIdentity(GC);

    //multiply by our lookAt matrix
    mvMultMatrix(lookAtMatrix,GC);

//--------- camera rotation matrix multiplicaton
    //translate to origin of model for rotation
    mvTranslate([(m.minX+m.maxX)/2.0,(m.minY+m.maxY)/2.0,(m.minZ+m.maxZ)/2.0],GC);

    mvMultMatrix(camera.Transform,GC);//multiply by the transformation

    //translate back to original origin
    mvTranslate([-(m.minX+m.maxX)/2.0,-(m.minY+m.maxY)/2.0,-(m.minZ+m.maxZ)/2.0],GC);
//---------

		mvPushMatrix(GC.mvMatrix, GC);
    //mvLoadIdentity(GC);
		
		mvTranslate([1000, -200, -2500], GC);
		mvRotate(-15, [0.0,1.0,0.0], GC);
		mvRotate(-90, [1.0,0.0,0.0], GC);
		
		//Draw the Knight
		gl.useProgram(GC.shaderProgramKnight);
		getShaderProgramKnight(GC); 
    gl.drawArrays(gl.TRIANGLES,0,k.indices.length);
		
		mvPopMatrix(GC);
		mvPushMatrix(GC.mvMatrix, GC);
    //mvLoadIdentity(GC);
		
		mvRotate(45, [0.0, 1.0, 0.0], GC);
		mvTranslate([1000,1000,-2000], GC);
		
		//Draw the Dragon
		gl.useProgram(GC.shaderProgramDragon);
		getShaderProgramDragon(GC);
    gl.drawArrays(gl.TRIANGLES,0,d.indices.length);
		
    mvPopMatrix(GC);
		mvPushMatrix(GC.mvMatrix, GC);
    //mvLoadIdentity(GC);
		
		//Set the Castle Postion
		
		mvRotate(-60, [0.0, 1.0, 0.0], GC);
		mvTranslate([-1800, 0, -4000], GC);
		
		//Draw the Castle
		gl.useProgram(GC.shaderProgramCastle);
		getShaderProgramCastle(GC);
    gl.drawArrays(gl.TRIANGLES,0,c.indices.length);
    
    mvPopMatrix(GC);
		mvPushMatrix(GC.mvMatrix, GC);
    mvRotate(180, [1.0,0.0,0.0], GC);

    //Draw the Cube
		gl.useProgram(GC.shaderProgramCube);
		getShaderProgramCube(GC); 
    gl.drawArrays(gl.TRIANGLES,0,m.indices.length);
		
		mvPopMatrix(GC);
}

//initialize webgl
demo.prototype.initWebGL = function(){
    gl = null;

    try {
        gl = this.canvas.getContext("experimental-webgl");
    }
    catch(e) {
        //pass through
    }

    // If we don't have a GL context, give up now
    if (!gl) {
        alert("Unable to initialize WebGL. Your browser may not support it.");
    }
}

//compile shader located within a script tag
demo.prototype.getShader = function(id){
    var shaderScript, theSource, currentChild, shader;

    shaderScript = document.getElementById(id);
    if(!shaderScript){
        return null;
    }

    //init the source code variable
    theSource = "";

    //begin reading the shader source from the beginning
    currentChild = shaderScript.firstChild;

    //read the shader source as text
    while(currentChild){
        if(currentChild.nodeType == currentChild.TEXT_NODE){
            theSource += currentChild.textContent;
        }
        currentChild = currentChild.nextSibling;
    }

    //check type of shader to give openGL the correct hint
    if(shaderScript.type == "x-shader/x-fragment"){
        shader = gl.createShader(gl.FRAGMENT_SHADER);
    } else if(shaderScript.type == "x-shader/x-vertex"){
        shader = gl.createShader(gl.VERTEX_SHADER);
    } else {
        return null;
    }
    
    //add the shader source code to the created shader object
    gl.shaderSource(shader, theSource);

    //compile the shader
    gl.compileShader(shader);

    if(!gl.getShaderParameter(shader, gl.COMPILE_STATUS)){
        console.log("error compiling shaders -- " + gl.getShaderInfoLog(shader));
        return null;
    }

    return shader;
}

//handle mousedown
demo.prototype.mouseDown = function(event){
    GC.mouseDown = true;

    //update the base rotation so model doesn't jerk around upon new clicks
    camera.LastRot = camera.ThisRot;
    camera.click(event.clientX,event.clientY);

    return false;
}

//handle mouseup
demo.prototype.mouseUp = function(event){
    GC.mouseDown = false;
    return false;
}

//handle mouse movement
demo.prototype.mouseMove = function(event){
    if(GC.mouseDown == true){
       X = event.clientX;
       Y = event.clientY;

       //call camera function for handling mouse movement
       camera.move(X,Y)

       drawScene();
    }
    return false;
}
/*
//handle mouse scroll event
demo.prototype.mouseWheel = function(event){
    //camera.zoomScale -= event.wheelDeltaY*0.0005;
    camera.Transform.elements[3][3] = 1.0;//camera.zoomScale;

    drawScene();
    return false;
}
*/

//--------- handle keyboard events
demo.prototype.keyDown = function(e){
    camera.LastRot = camera.ThisRot;
    var center = {x: GC.width/2, y:GC.height/2}; 
    var delta = 8;

    switch(e.keyCode){
        case 37: //Left arrow
            camera.click(center.x, center.y);
            camera.move(center.x - delta, center.y);
        break;
        case 38: //Up arrow
            camera.click(center.x, center.y);
            camera.move(center.x, center.y - delta);
        break;
        case 39: //Right arrow
            camera.click(center.x, center.y);
            camera.move(center.x + delta, center.y);
        break;
        case 40: //Down arrow
            camera.click(center.x, center.y);
            camera.move(center.x, center.y + delta);
        break;
    }

    //redraw
    drawScene();
}


// --------- handle touch events
demo.prototype.touchDown = function(event){
    GC.mouseDown = true;

    //update the base rotation so model doesn't jerk around upon new clicks
    camera.LastRot = camera.ThisRot;

    //tell the camera where the touch event happened
    camera.click(event.changedTouches[0].pageX,event.changedTouches[0].pageY);

    return false;
}

//handle touchEnd
demo.prototype.touchUp = function(event){
    GC.mouseDown = false;
    return false;
}

//handle touch movement
demo.prototype.touchMove = function(event){
    if(GC.mouseDown == true){
        X = event.changedTouches[0].pageX;
        Y = event.changedTouches[0].pageY;

       //call camera function for handling mouse movement
       camera.move(X,Y)

       drawScene();
    }
    return false;
}
// --------- end handle touch events
