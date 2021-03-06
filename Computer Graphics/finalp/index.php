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
<script type="text/javascript" src="js/shaders.js"></script>
<script type="text/javascript" src="js/geometry.js"></script>
<script type="text/javascript" src="js/cubemap.js"></script>
</head>
<body>

<canvas id="glcanvas">canvas not supported</canvas>

<script id="FragmentShaderCube" type="x-shader/x-fragment">
    #ifdef GL_OES_standard_derivatives
		#extension GL_OES_standard_derivatives : enable
	#endif

	precision mediump float;
	
	uniform sampler2D front;
	uniform sampler2D right;
	uniform sampler2D left;
	uniform sampler2D bottom;
	uniform sampler2D back;
	uniform sampler2D top;

	varying vec2 texCoord;
	varying float index;

	void main(void){
		
		if(index <= 1.0){	
			gl_FragColor = texture2D(front, texCoord);
		}else if(index<=2.0){
			gl_FragColor = texture2D(left, texCoord);
		}else if(index<=3.0){
            gl_FragColor = texture2D(top, texCoord);
        }else if(index<=4.0){
		    gl_FragColor = texture2D(right, texCoord);
        }else if(index<=5.0){
            gl_FragColor = texture2D(bottom, texCoord);
        }else{
            gl_FragColor = texture2D(back, texCoord);
		}
	}
</script>

<script id="VertexShaderCube" type="x-shader/x-vertex">
	attribute vec3 cubepos; //vertex position  
	attribute float cubeindex;
	attribute vec2 textureCoord;

	uniform mat4 uMVMatrix;//modelviewmatrix
	uniform mat4 uPMatrix;//projectionmatrix

	varying vec2 texCoord;
	varying float index;

	void main(void){
		texCoord = textureCoord;
		index = cubeindex;
		gl_Position = uPMatrix * uMVMatrix *vec4(cubepos, 1.0);   
	}
</script>

<!-- Fragment Shader -->
<script id="FragmentShaderKnight" type="x-shader/x-fragment">
    #ifdef GL_OES_standard_derivatives
        #extension GL_OES_standard_derivatives : enable
    #endif
		
		//Set precision
    precision mediump float;
		
		//Set Uniform Variables
		uniform vec3 camPos;  //Camera Positioning
		uniform vec3 coeff;  //Lambert's Coefficients
		uniform vec3 ambLight;  //Ambient Lighting
		uniform vec3 diffLight;  //Diffuse Lighting
		uniform vec3 specLight;  //Specular Lighting
		uniform float intensity;  //Surface Brightness
		
		//Set Varying Variables
    varying vec3 verts;  //Vertices
		varying vec3 norms;  //Normals
		
		//Implement Phong Shading
    void main(void){
			//Variables
			vec3 normals, lightSource, light, refDir, camDir;
			float coSineLaw, sp, spec, ka, kd, ks;
			
			//Set the normals
			normals = norms;
			
			//Set the Lighting
			lightSource = camPos;
			light = normalize(lightSource - verts);

			//Calculate the direction of reflection
			refDir = reflect(light, normals);
			
			//Set the camera direction
			camDir  = normalize(verts);
			
			//Calculate the specular lighting
			spec = max(dot(refDir, camDir), 0.0);
			sp = pow(spec, intensity);
			
			//Set the Lighting Coefficients
			ka = coeff.x;
			kd = coeff.y;
			ks = coeff.z;
			
			//Calculate the Cosine Law for Diffuse Coloring
			coSineLaw = max(dot(normals, light), 0.0);
			
			//Set the Phong Shading Color Using the Lighting Equation
		  gl_FragColor = vec4((ka * ambLight) + (kd * coSineLaw * diffLight) + (ks * sp * specLight), 1.0);
    }

</script>

<!-- Vertex Shader -->
<script id="VertexShaderKnight" type="x-shader/x-vertex">
    attribute vec3 vPos;  //vertex position
		attribute vec3 normalAttribute;  //Attribute to get Normals
    
		//Set perspective and modelview uniforms
    uniform mat4 uMVMatrix;  //modelviewmatrix
    uniform mat4 uPMatrix;  //projectionmatrix
		
		//Set varying variables
		varying vec3 verts;  //Vertices
		varying vec3 norms;  //Normals

    void main(void) {
			//Set the positioning
			norms = vec3(uMVMatrix * vec4(normalAttribute, 0.0));
			verts = vec3(uMVMatrix * vec4(vPos,1.0));
			gl_Position = uPMatrix * uMVMatrix * vec4(vPos * 10.0, 1.0);
    }
</script>

<!-- Fragment Shader -->
<script id="FragmentShaderDragon" type="x-shader/x-fragment">
    #ifdef GL_OES_standard_derivatives
        #extension GL_OES_standard_derivatives : enable
    #endif
		
		//Set precision
    precision mediump float;
		
		//Set Uniform Variables
		uniform vec3 camPos;  //Camera Positioning
		uniform vec3 coeff;  //Lambert's Coefficients
		uniform vec3 ambLight;  //Ambient Lighting
		uniform vec3 diffLight;  //Diffuse Lighting
		uniform vec3 specLight;  //Specular Lighting
		uniform float intensity;  //Surface Brightness
		
		//Set Varying Variables
    varying vec3 verts;  //Vertices
		varying vec3 norms;  //Normals
		
		//Implement Phong Shading
    void main(void){
			//Variables
			vec3 normals, lightSource, light, refDir, camDir;
			float coSineLaw, sp, spec, ka, kd, ks;
			
			//Set the normals
			normals = norms;
			
			//Set the Lighting
			lightSource = camPos;
			light = normalize(lightSource - verts);

			//Calculate the direction of reflection
			refDir = reflect(light, normals);
			
			//Set the camera direction
			camDir  = normalize(verts);
			
			//Calculate the specular lighting
			spec = max(dot(refDir, camDir), 0.0);
			sp = pow(spec, intensity);
			
			//Set the Lighting Coefficients
			ka = coeff.x;
			kd = coeff.y;
			ks = coeff.z;
			
			//Calculate the Cosine Law for Diffuse Coloring
			coSineLaw = max(dot(normals, light), 0.0);
			
			//Set the Phong Shading Color Using the Lighting Equation
		  gl_FragColor = vec4((ka * ambLight) + (kd * coSineLaw * diffLight) + (ks * sp * specLight), 1.0);
    }

</script>

<!-- Vertex Shader -->
<script id="VertexShaderDragon" type="x-shader/x-vertex">
    attribute vec3 vPos;  //vertex position
		attribute vec3 normalAttribute;  //Attribute to get Normals
    
		//Set perspective and modelview uniforms
    uniform mat4 uMVMatrix;  //modelviewmatrix
    uniform mat4 uPMatrix;  //projectionmatrix
		
		//Set varying variables
		varying vec3 verts;  //Vertices
		varying vec3 norms;  //Normals

    void main(void) {
			//Set the positioning
			norms = vec3(uMVMatrix * vec4(normalAttribute, 0.0));
			verts = vec3(uMVMatrix * vec4(vPos,1.0));
			gl_Position = uPMatrix * uMVMatrix * vec4(vPos * 40.0, 1.0);
    }
</script>

<!-- Fragment Shader -->
<script id="FragmentShaderCastle" type="x-shader/x-fragment">
    #ifdef GL_OES_standard_derivatives
        #extension GL_OES_standard_derivatives : enable
    #endif
		
		//Set precision
    precision mediump float;
		
		//Set Uniform Variables
		uniform vec3 camPos;  //Camera Positioning
		uniform vec3 coeff;  //Lambert's Coefficients
		uniform vec3 ambLight;  //Ambient Lighting
		uniform vec3 diffLight;  //Diffuse Lighting
		uniform vec3 specLight;  //Specular Lighting
		uniform float intensity;  //Surface Brightness
		//uniform sampler2D sampler;  //Sampler for Image
		
		//Set Varying Variables
    varying vec3 verts;  //Vertices
		varying vec3 norms;  //Normals
		//varying vec2 texCoord;  //Texture Coordinates
		
		//Implement Phong Shading
    void main(void){
			//Variables
			vec3 normals, lightSource, light, refDir, camDir;
			float coSineLaw, sp, spec, ka, kd, ks;
			
			//Set the normals
			normals = norms;
			
			//Set the Lighting
			lightSource = camPos;
			light = normalize(lightSource - verts);

			//Calculate the direction of reflection
			refDir = reflect(light, normals);
			
			//Set the camera direction
			camDir  = normalize(verts);
			
			//Calculate the specular lighting
			spec = max(dot(refDir, camDir), 0.0);
			sp = pow(spec, intensity);
			
			//Set the Lighting Coefficients
			ka = coeff.x;
			kd = coeff.y;
			ks = coeff.z;
			
			//Calculate the Cosine Law for Diffuse Coloring
			coSineLaw = max(dot(normals, light), 0.0);
			
			//Set the Phong Shading Color Using the Lighting Equation
		  vec4 goraudColor = vec4((ka * ambLight) + (kd * coSineLaw * diffLight) + (ks * sp * specLight), 1.0);
			gl_FragColor = goraudColor;
    }

</script>

<!-- Vertex Shader -->
<script id="VertexShaderCastle" type="x-shader/x-vertex">
    attribute vec3 vPos;  //vertex position
		attribute vec3 normalAttribute;  //Attribute to get Normals
    
		//Set perspective and modelview uniforms
    uniform mat4 uMVMatrix;  //modelviewmatrix
    uniform mat4 uPMatrix;  //projectionmatrix
		
		//Set varying variables
		varying vec3 verts;  //Vertices
		varying vec3 norms;  //Normals
		//varying vec2 texCoord;  //Texture Coordinates

    void main(void) {
			//Set the positioning
			norms = vec3(uMVMatrix * vec4(normalAttribute, 0.0));
			verts = vec3(uMVMatrix * vec4(vPos,1.0));
			gl_Position = uPMatrix * uMVMatrix * vec4(vPos * 20.0, 1.0);
			
			//Calculate the texCoords
			//float m = pow((vPos.x * vPos.x) + (vPos.y * vPos.y) + ((vPos.z + 1.0) * (vPos.z + 1.0)), 0.5) * 2.0;
			//float s = (vPos.x / m) + 0.5;
			//float t = (vPos.y / m) + 0.5;
			
			//Send texture data to frag shader
			//texCoord = vec2(s, t);
			
    }
</script>


<script>
    //call the main mesh Loading function; main.js
		loadObjects();
</script>

</body>
</html>
