if (typeof String.prototype.startsWith !== 'function') {
  String.prototype.startsWith = function (str){
    return this.slice(0, str.length) === str;
  };
}
var modelLoader = {};

modelLoader.Mesh = function( objectData ){
    /*
        With the given elementID or string of the OBJ, this parses the
        OBJ and creates the mesh.
    */
		var check = 0;
    var verts = [];
		var norms = [];
		
    // unpacking stuff
    var packed = {};
    packed.indices = [];
    
    // array of lines separated by the newline
    var lines = objectData.split( '\n' )
    for( var i=0; i<lines.length; i++ ){

       lines[i] = lines[i].replace(/\s{2,}/g, " "); // remove double spaces

      // if this is a vertex
      if( lines[ i ].startsWith( 'v ' ) ){
        line = lines[ i ].slice( 2 ).split( " " )
        verts.push( line[ 0 ] );
        verts.push( line[ 1 ] );
        verts.push( line[ 2 ] );
      }
      // if this is a vertex normal
      else if( lines[ i ].startsWith( 'vn ' ) ){
				 line = lines[ i ].slice( 2 ).split( " " )
        norms.push( line[ 0 ] );
        norms.push( line[ 1 ] );
        norms.push( line[ 2 ] );
				check = 1;
      }
      // if this is a texture
      else if( lines[ i ].startsWith( 'vt' ) ){
      }
      // if this is a face
      else if( lines[ i ].startsWith( 'f ' ) ){
        line = lines[ i ].slice( 2 ).split( " " );
        for(var j=1; j <= line.length-2; j++){
            var i1 = line[0].split('/')[0] - 1;
            var i2 = line[j].split('/')[0] - 1;
            var i3 = line[j+1].split('/')[0] - 1;
            packed.indices.push(i1,i2,i3);
        }
      }
    }
    this.vertices = verts;
    this.indices = packed.indices;
		
		//Use normals if already provided otherwise calculate the normals
		if(check == 0){
			this.normals = calcVertNorms(verts, packed.indices);
		}
		else{
			this.normals = norms;
		}
}

calcVertNorms = function(verts, indices){
	var surfNorms = [];          //Array of Surface Normals
	var vertNormals = [];
	var vertSums = []; //Array to some up vertex normal values
	var va = [0.0, 0.0, 0.0];            //Array for point a of face
	var vb = [0.0, 0.0, 0.0];            //Array for point b of face
	var vc = [0.0, 0.0, 0.0];            //Array for point c of face
	var v1 = [0.0, 0.0, 0.0];            //Array for first triangle vector
	var v2 = [0.0, 0.0, 0.0];            //Array for 2nd triangle vector
	var vcross = [0.0, 0.0, 0.0];       //Array for single surface normal
	var unitVec = [0.0, 0.0, 0.0];     //Array for normalized vector
	var mag = 0.0;                    //Variable for magnitude
	
	//Initialize every element in the vertSums array to 0.0
	for(var i = 0; i < verts.length; i++){
		vertSums.push(0.0);
	}
	
	//Iterate through faces, build vectors and calculate cross product for surface normals
	for(var i = 0; i < indices.length; i += 3){
		va[0] = verts[indices[i] * 3];
		va[1] = verts[indices[i] * 3 + 1];
		va[2] = verts[indices[i] * 3 + 2];
		
		vb[0] = verts[indices[i+1] * 3];
		vb[1] = verts[indices[i+1] * 3 + 1];
		vb[2] = verts[indices[i+1] * 3 + 2];
		
		vc[0] = verts[indices[i+2] * 3];
		vc[1] = verts[indices[i+2] * 3 + 1];
		vc[2] = verts[indices[i+2] * 3 + 2];
		
		//Set up two vectors for the cross product
		for(var j = 0; j < 3; j++){
			v1[j] = va[j] - vb[j];
			v2[j] = va[j] - vc[j];
		}
		
		//Calculate surface normal using cross product
		vcross = cross(v1, v2);
		
		//Sum the surface normals for each vertices
		for(var k = 0; k < 3; k++){
			vertSums[indices[i+k] * 3] += vcross[0];
			vertSums[indices[i+k] * 3 + 1] += vcross[1];
			vertSums[indices[i+k] * 3 + 2] += vcross[2];
		}
		
		//Add single surface normal to surface normal array
		surfNorms.push(vcross[0], vcross[1], vcross[2]);
	}
	
	//Calculate the magnitude and normalize the vertex normals
	for(var i = 0; i < vertSums.length; i += 3){
		unitVec[0] = vertSums[i];
		unitVec[1] = vertSums[i+1];
		unitVec[2] = vertSums[i+2];
		
		mag = Vector3fLength(unitVec);
		
		for(var j = 0; j < 3; j++){
			unitVec[j] /= mag;
			vertNormals.push(unitVec[j]);
		}
	}
	
	//Return the vertex normals
	return vertNormals;
}