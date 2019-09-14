//------- utility functions

//Pass the ModelView Matrix and the Projection matrix to the opengl shaders
function setMatrixUniforms(gContext) {
    var pUniform = gl.getUniformLocation(gContext.shaderProgram, "uPMatrix");
    gl.uniformMatrix4fv(pUniform, false, new Float32Array(gContext.perspectiveMatrix.flatten()));
    var mvUniform = gl.getUniformLocation(gContext.shaderProgram, "uMVMatrix");
    gl.uniformMatrix4fv(mvUniform, false, new Float32Array(gContext.mvMatrix.flatten()));
		var camPos = gl.getUniformLocation(GC.shaderProgram, "camPos");
		gl.uniform3fv(camPos, new Float32Array(camera.position));
		
		//Set up the materials for Gold
		//Send the ambient light to the shader program
		var ambLight = gl.getUniformLocation(GC.shaderProgram, "ambLight");
		gl.uniform3fv(ambLight, new Float32Array([0.24725, 0.1995, 0.0745]));
	
		//Send the diffuse lighting to the shader program
		var diffLight = gl.getUniformLocation(GC.shaderProgram, "diffLight");
    gl.uniform3fv(diffLight, new Float32Array([0.75164, 0.60648, 0.22648]));

		//Send specular lighting to the shader program
		var specLight = gl.getUniformLocation(GC.shaderProgram, "specLight");
		gl.uniform3fv(specLight, new Float32Array([0.628281, 0.555802, 0.366065]));

		//Send coefficients to the shader to hand light equation
		var coeff = gl.getUniformLocation(GC.shaderProgram, "coeff");
		gl.uniform3fv(coeff, new Float32Array([1.0,1.0,1.0]));

		//Send surface light intensity to shader program
		var intensity = gl.getUniformLocation(GC.shaderProgram, "intensity");
		gl.uniform1f(intensity, 51.2);
}

//
// similar to glLoadIdentity, only affects modelViewMatrix
//
function mvLoadIdentity(gContext) {
    gContext.mvMatrix = Matrix.I(4);
}

//
// similar to glMultMatrix, only affects modelViewMatrix
//
function mvMultMatrix(m,gContext) {
    gContext.mvMatrix = gContext.mvMatrix.x(m);
}

//
// similar to glTransform, only affects modelViewMatrix
//
function mvTranslate(v,gContext) {
    mvMultMatrix(Matrix.Translation($V([v[0], v[1], v[2]])).ensure4x4(),gContext);
}


//
// similar to glPushMatrix, only affects modelViewMatrix stack
//
function mvPushMatrix(m,gContext) {
  if (m) {
    gContext.mvMatrixStack.push(m.dup());
    gContext.mvMatrix = m.dup();
  } else {
    gContext.mvMatrixStack.push(gContext.mvMatrix.dup());
  }
}

//
// similar to glPopMatrix, only affects modelViewMatrix stack
//
function mvPopMatrix(gContext) {
  if (!gContext.mvMatrixStack.length) {
    throw("Can't pop from an empty matrix stack.");
  }
  
  gContext.mvMatrix = gContext.mvMatrixStack.pop();
  return gContext.mvMatrix;
}

//
// similar to glRotate, only affects modelViewMatrix
//
function mvRotate(angle, v, gContext) {
  var inRadians = angle * Math.PI / 180.0;
  
  var m = Matrix.Rotation(inRadians, $V([v[0], v[1], v[2]])).ensure4x4();
  mvMultMatrix(m,gContext);
}




//
// gluLookAt
//
function makeLookAt(ex, ey, ez,
                    cx, cy, cz,
                    ux, uy, uz)
{
    var eye = $V([ex, ey, ez]);
    var center = $V([cx, cy, cz]);
    var up = $V([ux, uy, uz]);

    var mag;

    var z = eye.subtract(center).toUnitVector();
    var x = up.cross(z).toUnitVector();
    var y = z.cross(x).toUnitVector();

    var m = $M([[x.e(1), x.e(2), x.e(3), 0],
                [y.e(1), y.e(2), y.e(3), 0],
                [z.e(1), z.e(2), z.e(3), 0],
                [0, 0, 0, 1]]);

    var t = $M([[1, 0, 0, -ex],
                [0, 1, 0, -ey],
                [0, 0, 1, -ez],
                [0, 0, 0, 1]]);
    return m.x(t);
}

//
// glOrtho
//
function makeOrtho(left, right,
                   bottom, top,
                   znear, zfar)
{
    var tx = -(right+left)/(right-left);
    var ty = -(top+bottom)/(top-bottom);
    var tz = -(zfar+znear)/(zfar-znear);

    return $M([[2/(right-left), 0, 0, tx],
               [0, 2/(top-bottom), 0, ty],
               [0, 0, -2/(zfar-znear), tz],
               [0, 0, 0, 1]]);
}

//
// gluPerspective
//
function makePerspective(fovy, aspect, znear, zfar)
{
    var ymax = znear * Math.tan(fovy * Math.PI / 360.0);
    var ymin = -ymax;
    var xmin = ymin * aspect;
    var xmax = ymax * aspect;

    return makeFrustum(xmin, xmax, ymin, ymax, znear, zfar);
}

//
// glFrustum
//
function makeFrustum(left, right,
                     bottom, top,
                     znear, zfar)
{
    var X = 2*znear/(right-left);
    var Y = 2*znear/(top-bottom);
    var A = (right+left)/(right-left);
    var B = (top+bottom)/(top-bottom);
    var C = -(zfar+znear)/(zfar-znear);
    var D = -2*zfar*znear/(zfar-znear);

    return $M([[X, 0, A, 0],
               [0, Y, B, 0],
               [0, 0, C, D],
               [0, 0, -1, 0]]);
}

//
// glOrtho
//
function makeOrtho(left, right, bottom, top, znear, zfar)
{
    var tx = - (right + left) / (right - left);
    var ty = - (top + bottom) / (top - bottom);
    var tz = - (zfar + znear) / (zfar - znear);

    return $M([[2 / (right - left), 0, 0, tx],
           [0, 2 / (top - bottom), 0, ty],
           [0, 0, -2 / (zfar - znear), tz],
           [0, 0, 0, 1]]);
}
