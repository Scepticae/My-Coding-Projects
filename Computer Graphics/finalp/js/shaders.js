//initialize the shaders and grab the shader variable attributes
demo.prototype.initShaders = function(){
    //Load the shaders
    var shaders = [["VertexShaderKnight", "FragmentShaderKnight", "shaderProgramKnight"],
			["VertexShaderDragon", "FragmentShaderDragon", "shaderProgramDragon"],
			["VertexShaderCastle", "FragmentShaderCastle", "shaderProgramCastle"],
			["VertexShaderCube", "FragmentShaderCube", "shaderProgramCube"]];

		for(var i = 0; i < 4; i++){							
			var fragmentShader = this.getShader(shaders[i][1]);
			var vertexShader = this.getShader(shaders[i][0]);

			this[shaders[i][2]] = gl.createProgram();
			gl.attachShader(this[shaders[i][2]], vertexShader);
			gl.attachShader(this[shaders[i][2]], fragmentShader);
			gl.linkProgram(this[shaders[i][2]]);

			if(!gl.getProgramParameter(this[shaders[i][2]], gl.LINK_STATUS)){
					console.log("unable to init shader program");
			}

			GC[shaders[i][2]] = this[shaders[i][2]];
			
			//Set the Shader Programs
			if(i == 0){setShaderProgramKnight(GC);}
			else if(i == 1){setShaderProgramDragon(GC);}
			else if(i == 2){setShaderProgramCastle(GC);}
			else{setShaderProgramCube(GC);}
		}
}
//Build Shaders-------------------------------------------------------------------
//Pass the ModelView Matrix and the Projection matrix to the opengl shaders
var setShaderProgramCube = function(gContext) {
    var cube = gContext.shaderProgramCube;
	
    cube.pUniform = gl.getUniformLocation(gContext.shaderProgramCube, "uPMatrix");
		cube.mvUniform = gl.getUniformLocation(gContext.shaderProgramCube, "uMVMatrix");
		
    cube.front = gl.getUniformLocation(gContext.shaderProgramCube, "front");
		cube.top = gl.getUniformLocation(gContext.shaderProgramCube, "top");
    cube.bottom = gl.getUniformLocation(gContext.shaderProgramCube, "bottom");
    cube.left = gl.getUniformLocation(gContext.shaderProgramCube, "left");
		cube.right = gl.getUniformLocation(gContext.shaderProgramCube, "right");
    cube.back = gl.getUniformLocation(gContext.shaderProgramCube, "back");

	  cube.vertexPositionAttribute = gl.getAttribLocation(gContext.shaderProgramCube, "cubepos");
    gl.enableVertexAttribArray(cube.vertexPositionAttribute)

    cube.textureIndexAttribute = gl.getAttribLocation(gContext.shaderProgramCube, "cubeindex");
    gl.enableVertexAttribArray(cube.textureIndexAttribute);

    cube.textureCoordAttribute = gl.getAttribLocation(gContext.shaderProgramCube, "textureCoord");
    gl.enableVertexAttribArray(cube.textureCoordAttribute);
}

var setShaderProgramKnight = function(gContext) {
		var k = gContext.shaderProgramKnight;
		
    k.pUniform = gl.getUniformLocation(gContext.shaderProgramKnight, "uPMatrix");
    k.mvUniform = gl.getUniformLocation(gContext.shaderProgramKnight, "uMVMatrix");
    
		k.camPos = gl.getUniformLocation(GC.shaderProgramKnight, "camPos");
		
		//Set up the materials for Gold
		//Send the ambient light to the shader program
		k.ambLight = gl.getUniformLocation(GC.shaderProgramKnight, "ambLight");
	
		//Send the diffuse lighting to the shader program
		k.diffLight = gl.getUniformLocation(GC.shaderProgramKnight, "diffLight");

		//Send specular lighting to the shader program
		k.specLight = gl.getUniformLocation(GC.shaderProgramKnight, "specLight");

		//Send coefficients to the shader to hand light equation
	  k.coeff = gl.getUniformLocation(GC.shaderProgramKnight, "coeff");

		//Send surface light intensity to shader program
		k.intensity = gl.getUniformLocation(GC.shaderProgramKnight, "intensity");
		
		//Initialize the Attributes
		GC.vertexPositionAttribute = gl.getAttribLocation(gContext.shaderProgramKnight, "vPos");
		gl.enableVertexAttribArray(GC.vertexPositionAttribute);
			
		GC.normalAttribute = gl.getAttribLocation(gContext.shaderProgramKnight, "normalAttribute");
		gl.enableVertexAttribArray(GC.normalAttribute);
}

//Pass the ModelView Matrix and the Projection matrix to the opengl shaders
function setShaderProgramDragon(gContext) {
		var d = gContext.shaderProgramDragon;
		
    d.pUniform = gl.getUniformLocation(gContext.shaderProgramDragon, "uPMatrix");
    d.mvUniform = gl.getUniformLocation(gContext.shaderProgramDragon, "uMVMatrix");
    
		d.camPos = gl.getUniformLocation(GC.shaderProgramDragon, "camPos");
			
		//Set up the materials for Gold
		//Send the ambient light to the shader program
		d.ambLight = gl.getUniformLocation(GC.shaderProgramDragon, "ambLight");
	
		//Send the diffuse lighting to the shader program
		d.diffLight = gl.getUniformLocation(GC.shaderProgramDragon, "diffLight");

		//Send specular lighting to the shader program
		d.specLight = gl.getUniformLocation(GC.shaderProgramDragon, "specLight");
		

		//Send coefficients to the shader to hand light equation
		d.coeff = gl.getUniformLocation(GC.shaderProgramDragon, "coeff");

		//Send surface light intensity to shader program
		d.intensity = gl.getUniformLocation(GC.shaderProgramDragon, "intensity");
		
		//Initialize the Attributes
		GC.vertexPositionAttribute = gl.getAttribLocation(gContext.shaderProgramDragon, "vPos");
		gl.enableVertexAttribArray(GC.vertexPositionAttribute);
			
		GC.normalAttribute = gl.getAttribLocation(gContext.shaderProgramDragon, "normalAttribute");
		gl.enableVertexAttribArray(GC.normalAttribute);
}

//Pass the ModelView Matrix and the Projection matrix to the opengl shaders
function setShaderProgramCastle(gContext) {
		var c = gContext.shaderProgramCastle;
		
    c.pUniform = gl.getUniformLocation(gContext.shaderProgramCastle, "uPMatrix");
    c.mvUniform = gl.getUniformLocation(gContext.shaderProgramCastle, "uMVMatrix");
    
		c.camPos = gl.getUniformLocation(GC.shaderProgramCastle, "camPos");
		
		//Set up the materials for Gold
		//Send the ambient light to the shader program
		c.ambLight = gl.getUniformLocation(GC.shaderProgramCastle, "ambLight");
	
		//Send the diffuse lighting to the shader program
		c.diffLight = gl.getUniformLocation(GC.shaderProgramCastle, "diffLight");

		//Send specular lighting to the shader program
		c.specLight = gl.getUniformLocation(GC.shaderProgramCastle, "specLight");

		//Send coefficients to the shader to hand light equation
		c.coeff = gl.getUniformLocation(GC.shaderProgramCastle, "coeff");

		//Send surface light intensity to shader program
		c.intensity = gl.getUniformLocation(GC.shaderProgramCastle, "intensity");
		
		//Set the Uniform for the Texture Shader
		//c.texData = gl.getUniformLocation(GC.shaderProgramCastle, "sampler");
		
		//Initialize the Attributes
		GC.vertexPositionAttribute = gl.getAttribLocation(gContext.shaderProgramCastle, "vPos");
		gl.enableVertexAttribArray(GC.vertexPositionAttribute);
			
		GC.normalAttribute = gl.getAttribLocation(gContext.shaderProgramCastle, "normalAttribute");
		gl.enableVertexAttribArray(GC.normalAttribute);
}

//Get the Shaders for Drawing-----------------------------------------------------

//Get the Cube Map Shader
function getShaderProgramCube(gContext) {
    var m = gContext.meshCube.model;
    var cube = gContext.shaderProgramCube;

    gl.uniformMatrix4fv(cube.pUniform, false, new Float32Array(gContext.perspectiveMatrix.flatten()));
    gl.uniformMatrix4fv(cube.mvUniform, false, new Float32Array(gContext.mvMatrix.flatten()));
    gl.uniform1i(cube.textureLocation, 1.0);
    gl.uniform1i(cube.front, 1);
    gl.uniform1i(cube.left, 2);
    gl.uniform1i(cube.bottom, 3);
    gl.uniform1i(cube.right, 4);
    gl.uniform1i(cube.top, 5);
    gl.uniform1i(cube.back, 6);

    gl.bindBuffer(gl.ARRAY_BUFFER, m.textureIndexBuffer);
    gl.vertexAttribPointer(cube.textureIndexAttribute, 1, gl.FLOAT, false, 0, 0);

    gl.bindBuffer(gl.ARRAY_BUFFER, m.vertexBuffer);
    gl.vertexAttribPointer(cube.vertexPositionAttribute, 3, gl.FLOAT, false, 0, 0);

    gl.bindBuffer(gl.ARRAY_BUFFER, m.textureCoordsBuffer);
    gl.vertexAttribPointer(cube.textureCoordAttribute, 2, gl.FLOAT, false, 0, 0);
}

//Get Knight Shader
function getShaderProgramKnight(gContext){
	var m = gContext.meshKnight.model;
	var k = gContext.shaderProgramKnight;
	
	gl.uniformMatrix4fv(k.pUniform, false, new Float32Array(gContext.perspectiveMatrix.flatten()));
	gl.uniformMatrix4fv(k.mvUniform, false, new Float32Array(gContext.mvMatrix.flatten()));
	
	gl.uniform3fv(k.camPos, new Float32Array(camera.position));
	
	gl.uniform3fv(k.ambLight, new Float32Array([0.10225, 0.10225, 0.10225]));
	gl.uniform3fv(k.diffLight, new Float32Array([0.11754, 0.11754, 0.11754]));
	gl.uniform3fv(k.specLight, new Float32Array([1.0, 1.0, 1.0]));
	gl.uniform3fv(k.coeff, new Float32Array([1.0,1.0,1.0]));
	gl.uniform1f(k.intensity, 125.0);
	
	//pass the vertex buffer to the shader
  gl.bindBuffer(gl.ARRAY_BUFFER, m.vertexBuffer);
  gl.vertexAttribPointer(GC.vertexPositionAttribute, 3, gl.FLOAT, false, 0, 0);
		
	//pass the normals to the shader
  gl.bindBuffer(gl.ARRAY_BUFFER, m.normBuffer);
  gl.vertexAttribPointer(GC.normalAttribute, 3, gl.FLOAT, false, 0, 0);
}

//Get Dragon Shader
function getShaderProgramDragon(gContext){
	var m = gContext.meshDragon.model;
	var d = gContext.shaderProgramDragon;
	
	gl.uniformMatrix4fv(d.pUniform, false, new Float32Array(gContext.perspectiveMatrix.flatten()));
	gl.uniformMatrix4fv(d.mvUniform, false, new Float32Array(gContext.mvMatrix.flatten()));
	
	gl.uniform3fv(d.camPos, new Float32Array(camera.position));
	
	gl.uniform3fv(d.ambLight, new Float32Array([0.1745, 0.01175, 0.01175]));
	gl.uniform3fv(d.diffLight, new Float32Array([0.61424, 0.04136, 0.04136]));
	gl.uniform3fv(d.specLight, new Float32Array([0.727811, 0.626959, 0.626959]));
	gl.uniform3fv(d.coeff, new Float32Array([1.0,1.0,1.0]));
	gl.uniform1f(d.intensity, 15.8);
	
	//pass the vertex buffer to the shader
	gl.bindBuffer(gl.ARRAY_BUFFER, m.vertexBuffer);
	gl.vertexAttribPointer(GC.vertexPositionAttribute, 3, gl.FLOAT, false, 0, 0);
		
	//pass the normals to the shader
	gl.bindBuffer(gl.ARRAY_BUFFER, m.normBuffer);
	gl.vertexAttribPointer(GC.normalAttribute, 3, gl.FLOAT, false, 0, 0);
}

//Get Castle Shader
function getShaderProgramCastle(gContext){
	var m = gContext.meshCastle.model;
	var c = gContext.shaderProgramCastle;
	
	gl.uniformMatrix4fv(c.pUniform, false, new Float32Array(gContext.perspectiveMatrix.flatten()));
	gl.uniformMatrix4fv(c.mvUniform, false, new Float32Array(gContext.mvMatrix.flatten()));
	
	gl.uniform3fv(c.camPos, new Float32Array(camera.position));
	
	gl.uniform3fv(c.ambLight, new Float32Array([0.25, 0.25, 0.25]));
	gl.uniform3fv(c.diffLight, new Float32Array([0.4, 0.4, 0.4]));
	gl.uniform3fv(c.specLight, new Float32Array([0.374597, 0.374597, 0.374597]));
	gl.uniform3fv(c.coeff, new Float32Array([1.0,1.0,1.0]));
	gl.uniform1f(c.intensity, 22.8);
	//gl.uniform1i(c.texData, 0);
	
	//pass the vertex buffer to the shader
	gl.bindBuffer(gl.ARRAY_BUFFER, m.vertexBuffer);
	gl.vertexAttribPointer(GC.vertexPositionAttribute, 3, gl.FLOAT, false, 0, 0);
		
	//pass the normals to the shader
	gl.bindBuffer(gl.ARRAY_BUFFER, m.normBuffer);
	gl.vertexAttribPointer(GC.normalAttribute, 3, gl.FLOAT, false, 0, 0);
}
