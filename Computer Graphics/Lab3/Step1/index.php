<?php
?>
<html>
<head>
<meta charset="utf-8">
<title>Model Viewer</title>
<!-- include all javascript source files -->
<script src="//ajax.googleapis.com/ajax/libs/jquery/1.10.2/jquery.min.js"></script>
<script type="text/javascript" src="js/sylvester.js"></script>
<script type="text/javascript" src="js/math.js"></script>
<script type="text/javascript" src="js/glUtils.js"></script>
<script type="text/javascript" src="js/meshLoader.js"></script>
<script type="text/javascript" src="js/arcball.js"></script>
<script type="text/javascript" src="js/demo.js"></script>
<script type="text/javascript" src="js/main.js"></script>
</head>
<body>
<canvas id="glcanvas">canvas not supported</canvas>

<div id="meshSelect-wrapper">
    <span>Select object from this directory (.obj files only)</span>
    <select id="meshSelect">
    <?php //----- php code to create html selection with local files

        $files = glob("*.obj"); //find all .obj files in current directory
        $beginFile = "";
        foreach ($files as $filename) {
            if($filename == end($files)){
                $beginFile = $filename;
                echo "<option selected=\"selected\">$filename</option>";
            } else {
                echo "<option>$filename</option>";
            }
        }
    ?>
    </select>
    <br />
    <span>Or upload a local file here:</span>
    <input type="file" id="files" name="files[]"/>
</div>


<!-- Fragment Shader -->
<script id="FragmentShader1" type="x-shader/x-fragment">
    #ifdef GL_OES_standard_derivatives
        #extension GL_OES_standard_derivatives : enable
    #endif
		
		//Set precision
    precision mediump float;
		
		//Set Uniform Variables
		uniform vec3 camPos;  //Camera Positioning
		uniform sampler2D sampler;  //Sampler for Image
		
		//Set Varying Variables
    varying vec3 verts;  //Vertices
		varying vec3 norms;  //Normals
		varying vec2 texCoord;  //Texture Coordinates
		
		//Implement Phong Shading
    void main(void){
			//Variables
			vec3 normals;
			
			//Set the normals
			normals = norms;
			
			//Set the Fragments to the texture values
		  gl_FragColor = texture2D(sampler, texCoord);
    }

</script>

<!-- Vertex Shader -->
<script id="VertexShader1" type="x-shader/x-vertex">
    attribute vec3 vPos;  //vertex position
		attribute vec3 normalAttribute;  //Attribute to get Normals
    attribute vec2 texVal;  //Texture Data
		
		//Set perspective and modelview uniforms
    uniform mat4 uMVMatrix;  //modelviewmatrix
    uniform mat4 uPMatrix;  //projectionmatrix
		
		//Set varying variables
		varying vec3 verts;  //Vertices
		varying vec3 norms;  //Normals
		varying vec2 texCoord;  //Texture Coordinates

    void main(void) {
			//Send texture data to frag shader
			texCoord = texVal;
			
			//Set the positioning
			norms = vec3(uMVMatrix * vec4(normalAttribute, 0.0));
			verts = vec3(uMVMatrix * vec4(vPos,1.0));
			gl_Position = uPMatrix * uMVMatrix * vec4(vPos, 1.0);
    }
</script>


<script>
    //grab the filename for the .obj we will first open
    var filename = "<? echo $beginFile ?>";

    //register callbacks for mesh loading
    setupLoadingCallbacks();

    //call the main mesh Loading function; main.js
    executeMainLoop(filename); 
</script>

</body>
</html>
