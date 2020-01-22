demo.prototype.initGeometryBuffers = function(){
	this.initGeometryBuffersCube();
	this.initGeometryBuffersKnight();
	this.initGeometryBuffersDragon();
	this.initGeometryBuffersCastle();
}

demo.prototype.initGeometryBuffersCube = function(){
    var m = GC.meshCube.model;
    //var temp = GC.mesh.model;
    //textures were read from the obj file
    var textureCoordinates = GC.meshCube.model.textures;
    var verts = [];
		var min = [90000,90000,90000];    //used for bounding box calculations
		var max = [-90000,-90000,-90000]; //used for bounding box calculations
	
    //creates a box around our object
    //if you notice that this box starts to have black holes its because it is out of the FOV
    var scalar = Math.min(m.minX,m.minY,m.minZ)
    scalar= Math.max(Math.abs(scalar),Math.abs(Math.max(m.maxX,m.maxY,m.maxZ)));
    scalar*= 100;

    m.indices.forEach(function(d,i){
        vx = (parseFloat(m.vertices[d*3+0]));
        vy = (parseFloat(m.vertices[d*3+1]));
        vz = (parseFloat(m.vertices[d*3+2]));

        verts.push(vx * 9000.0,vy * 9000.0,vz * 9000.0);

		if(vx < min[0]) min[0] = vx;
        if(vy < min[1]) min[1] = vy;
        if(vz < min[2]) min[2] = vz;
        if(vx > max[0]) max[0] = vx;
        if(vy > max[1]) max[1] = vy;
        if(vz > max[2]) max[2] = vz;	
    });

		m.minX = min[0]; m.minY = min[1]; m.minZ = min[2];
    m.maxX = max[0]; m.maxY = max[1]; m.maxZ = max[2];
		
		////calculate the largest range in x,y,z
		var s = Math.max( Math.abs(min[0]-max[0]),
											Math.abs(min[1]-max[1]),
											Math.abs(min[2]-max[2]))

  //calculate the distance to place camera from model
  var d = (s/2.0)/Math.tan(45/2.0);

  //place the camera at the calculated position
  //camera.position[2] = d * 5.0;

  //orient the camera to look at the center of the model
  //camera.lookAt = [(m.minX+m.maxX)/2.0,(m.minY+m.maxY)/2.0,(m.minZ+m.maxZ)/2.0];

    m.vertexBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, m.vertexBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(verts), gl.STATIC_DRAW);

    m.textureCoordsBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, m.textureCoordsBuffer);
    gl.bufferData(gl.ARRAY_BUFFER,new Float32Array(textureCoordinates),gl.STATIC_DRAW);

    //index the cube
    var textureIndex=[];
    for(var i=0; i < m.indices.length;i++){
        textureIndex.push(Math.floor(i/(m.indices.length/6))+1);
    }

    m.textureIndexBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, m.textureIndexBuffer);
    gl.bufferData(gl.ARRAY_BUFFER,new Float32Array(textureIndex),gl.STATIC_DRAW);
}

//initialize the buffers for drawing and the edge highlights
demo.prototype.initGeometryBuffersKnight = function(){
  var m = GC.meshKnight.model;
  
  var verts = [];                   //array to hold vertices laid out according to indices
  var normals = [];                    //array of 1s and 0s passed to GLSL to draw wireframe
  var min = [90000,90000,90000];    //used for bounding box calculations
  var max = [-90000,-90000,-90000]; //used for bounding box calculations

    // Loop through the indices array and create a vertices array (this means
    //     duplicating data) from the listed indices
    m.indices.forEach(function(d,i){
        //grab the x,y,z values for the current vertex
        vx = (parseFloat(m.vertices[d*3]));
        vy = (parseFloat(m.vertices[d*3+1]));
        vz = (parseFloat(m.vertices[d*3+2]));

        //add this vertex and normals to arrays
        verts.push(vx,vy,vz);
				normals.push(m.normals[d*3], m.normals[d*3+1], m.normals[d*3+2]);

        //check to see if we need to update the min/max
        if(vx < min[0]) min[0] = vx;
        if(vy < min[1]) min[1] = vy;
        if(vz < min[2]) min[2] = vz;
        if(vx > max[0]) max[0] = vx;
        if(vy > max[1]) max[1] = vy;
        if(vz > max[2]) max[2] = vz;
		});
		
    //set the min/max variables
  m.minX = min[0]; m.minY = min[1]; m.minZ = min[2];
  m.maxX = max[0]; m.maxY = max[1]; m.maxZ = max[2];

  //calculate the largest range in x,y,z
  var s = Math.max( Math.abs(min[0]-max[0]),
                    Math.abs(min[1]-max[1]),
                    Math.abs(min[2]-max[2]))
  
  //calculate the distance to place camera from model
  var d = (s/2.0)/Math.tan(45/2.0);

  //place the camera at the calculated position
  camera.position[2] = d * 10.0;

  //orient the camera to look at the center of the model
  camera.lookAt = [(m.minX+m.maxX)/2.0,(m.minY+m.maxY)/2.0,(m.minZ+m.maxZ)/2.0];

  m.vertexBuffer = gl.createBuffer();
  //bind the data we placed in the verts array to an OpenGL buffer
  gl.bindBuffer(gl.ARRAY_BUFFER, m.vertexBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(verts), gl.STATIC_DRAW);
	
	m.normBuffer = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, m.normBuffer);
	gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(normals), gl.STATIC_DRAW);
}

//initialize the buffers for drawing and the edge highlights
demo.prototype.initGeometryBuffersDragon = function(){
  var m = GC.meshDragon.model;
  
  var verts = [];                   //array to hold vertices laid out according to indices
  var normals = [];                    //array of 1s and 0s passed to GLSL to draw wireframe
  var min = [90000,90000,90000];    //used for bounding box calculations
  var max = [-90000,-90000,-90000]; //used for bounding box calculations

    // Loop through the indices array and create a vertices array (this means
    //     duplicating data) from the listed indices
    m.indices.forEach(function(d,i){
        //grab the x,y,z values for the current vertex
        vx = (parseFloat(m.vertices[d*3]));
        vy = (parseFloat(m.vertices[d*3+1]));
        vz = (parseFloat(m.vertices[d*3+2]));

        //add this vertex and normals to arrays
        verts.push(vx,vy,vz);
				normals.push(m.normals[d*3], m.normals[d*3+1], m.normals[d*3+2]);

        //check to see if we need to update the min/max
        if(vx < min[0]) min[0] = vx;
        if(vy < min[1]) min[1] = vy;
        if(vz < min[2]) min[2] = vz;
        if(vx > max[0]) max[0] = vx;
        if(vy > max[1]) max[1] = vy;
        if(vz > max[2]) max[2] = vz;
		});
		
    //set the min/max variables
  m.minX = min[0]; m.minY = min[1]; m.minZ = min[2];
  m.maxX = max[0]; m.maxY = max[1]; m.maxZ = max[2];

  //calculate the largest range in x,y,z
  var s = Math.max( Math.abs(min[0]-max[0]),
                    Math.abs(min[1]-max[1]),
                    Math.abs(min[2]-max[2]))
  
  //calculate the distance to place camera from model
  var d = (s/2.0)/Math.tan(45/2.0);

  //place the camera at the calculated position
  camera.position[2] = d * 10.0;

  //orient the camera to look at the center of the model
  camera.lookAt = [(m.minX+m.maxX)/2.0,(m.minY+m.maxY)/2.0,(m.minZ+m.maxZ)/2.0];

  m.vertexBuffer = gl.createBuffer();
  //bind the data we placed in the verts array to an OpenGL buffer
  gl.bindBuffer(gl.ARRAY_BUFFER, m.vertexBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(verts), gl.STATIC_DRAW);
	
	m.normBuffer = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, m.normBuffer);
	gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(normals), gl.STATIC_DRAW);
}

//initialize the buffers for drawing and the edge highlights
demo.prototype.initGeometryBuffersCastle = function(){
  var m = GC.meshCastle.model;
  
  var verts = [];                   //array to hold vertices laid out according to indices
  var normals = [];                    //array of 1s and 0s passed to GLSL to draw wireframe
  var min = [90000,90000,90000];    //used for bounding box calculations
  var max = [-90000,-90000,-90000]; //used for bounding box calculations

    // Loop through the indices array and create a vertices array (this means
    //     duplicating data) from the listed indices
    m.indices.forEach(function(d,i){
        //grab the x,y,z values for the current vertex
        vx = (parseFloat(m.vertices[d*3]));
        vy = (parseFloat(m.vertices[d*3+1]));
        vz = (parseFloat(m.vertices[d*3+2]));

        //add this vertex and normals to arrays
        verts.push(vx,vy,vz);
				normals.push(m.normals[d*3], m.normals[d*3+1], m.normals[d*3+2]);

        //check to see if we need to update the min/max
        if(vx < min[0]) min[0] = vx;
        if(vy < min[1]) min[1] = vy;
        if(vz < min[2]) min[2] = vz;
        if(vx > max[0]) max[0] = vx;
        if(vy > max[1]) max[1] = vy;
        if(vz > max[2]) max[2] = vz;
		});
		
    //set the min/max variables
  m.minX = min[0]; m.minY = min[1]; m.minZ = min[2];
  m.maxX = max[0]; m.maxY = max[1]; m.maxZ = max[2];

  //calculate the largest range in x,y,z
  var s = Math.max( Math.abs(min[0]-max[0]),
                   Math.abs(min[1]-max[1]),
                   Math.abs(min[2]-max[2]))
  
  //calculate the distance to place camera from model
  var d = (s/2.0)/Math.tan(45/2.0);

  //place the camera at the calculated position
  camera.position[2] = d * 10.0;

  //orient the camera to look at the center of the model
  camera.lookAt = [(m.minX+m.maxX)/2.0,(m.minY+m.maxY)/2.0,(m.minZ+m.maxZ)/2.0];

  m.vertexBuffer = gl.createBuffer();
  //bind the data we placed in the verts array to an OpenGL buffer
  gl.bindBuffer(gl.ARRAY_BUFFER, m.vertexBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(verts), gl.STATIC_DRAW);
	
	m.normBuffer = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, m.normBuffer);
	gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(normals), gl.STATIC_DRAW);
	/*
	var tex;
	var image1 = new Image();
	image1.src = "castleTexture.jpg";
	
	//Create the Texture
	tex = gl.createTexture();
	gl.bindTexture(gl.TEXTURE_2D, tex);
	gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, 1, 1, 0, gl.RGBA, gl.UNSIGNED_BYTE,new Uint8Array([0, 0, 255, 255]));
	
	//Fix non powers of 2
	gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
	gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE);
  gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
  gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
	
	//Apply the Image
	//Add an Event Listener Courtesy of WebGL Texture Pages
	image1.addEventListener('load', function() {
		gl.bindTexture(gl.TEXTURE_2D, tex);
		gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, true);
		gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA,gl.UNSIGNED_BYTE, image1);
		gl.generateMipmap(gl.TEXTURE_2D);
		
		//Tell the listener to draw the scene
		drawScene();
	});
	*/
}