var images=[];
var imagesToLoad= 0;
var textureList=[
    [null,"TEXTURE_CUBE_MAP"], //cubemap texture
	["posz.jpg","TEXTURE_2D"], //front 
	["negy.jpg","TEXTURE_2D"], //Floor Good
	["posx.jpg","TEXTURE_2D"], //Good Right
	["posy.jpg","TEXTURE_2D"], //Ceiling Good
	["negz.jpg","TEXTURE_2D"], //top
	["negx.jpg","TEXTURE_2D"], //back 
];

//hard coded in
var imagesToLoad=0;

demo.prototype.initImages = function(){
    var listUrls=[];
    for(var i =0; i < textureList.length;i++){
        if(textureList[i][1]=="TEXTURE_2D"){
            images.push(null);
            listUrls.push(textureList[i][0]);
        }
    }
    loadListImages(listUrls);
}

function loadListImages(urls){
    imagesToLoad = urls.length;
    for (var i = 0; i < urls.length; ++i) {
        loadImage(urls[i],i);
    }
}

function loadImage(url,i) {
    var image = new Image();
		image.src = url;
    //image.onload = function (){
    image.addEventListener('load', function() {
    imagesToLoad--;
    images[i]=image;
    if(imagesToLoad==0){
			bindTextures();
    }
    }); 
}
	
function bindTextures(){
    var buffers=[]
    var currImage=0;

    for(var i=0;i< textureList.length; i++){
        if(textureList[i][1]=="TEXTURE_2D"){
            buffers.push( gl.createTexture());
            bind_TEXTURE_2D(buffers[i], currImage);
            currImage++;
        }else if (textureList[i][1]=="TEXTURE_CUBE_MAP"){
            buffers.push( gl.createTexture());
			bind_TEXTURE_CUBE_MAP(buffers[i]);
        }else{
            console.log(textureList[i][1]+ " : I Cant handle this texture :(");
        }

    }
    for (var i = 0; i < textureList.length; i++) {
        gl.activeTexture(gl.TEXTURE0 + i);
        gl.bindTexture(gl[textureList[i][1]], buffers[i]);
    }
		setTimeout(drawScene(), 1000);
}

function bind_TEXTURE_CUBE_MAP(cubemap) {
    gl.bindTexture(gl.TEXTURE_CUBE_MAP, cubemap);
    gl.texParameteri(gl.TEXTURE_CUBE_MAP, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
    gl.texParameteri(gl.TEXTURE_CUBE_MAP, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE);
    gl.texParameteri(gl.TEXTURE_CUBE_MAP, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
    gl.texParameteri(gl.TEXTURE_CUBE_MAP, gl.TEXTURE_MAG_FILTER, gl.LINEAR);

    var cubeFaces = [
    	[0, gl.TEXTURE_CUBE_MAP_POSITIVE_Z], //right
      [1, gl.TEXTURE_CUBE_MAP_NEGATIVE_X], //left
      [2, gl.TEXTURE_CUBE_MAP_NEGATIVE_Y], //top 
      [3, gl.TEXTURE_CUBE_MAP_POSITIVE_X], //bottom
      [4, gl.TEXTURE_CUBE_MAP_POSITIVE_Y], //front
    	[5, gl.TEXTURE_CUBE_MAP_NEGATIVE_Z]  //back
    ];

    for (var i = 0; i < cubeFaces.length; i++) {
        gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, true);
        gl.bindTexture(gl.TEXTURE_CUBE_MAP, cubemap)
        gl.texImage2D(cubeFaces[i][1], 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, images[cubeFaces[i][0]]);
        gl.bindTexture(gl.TEXTURE_CUBE_MAP, null);
    }
}

function bind_TEXTURE_2D(texture,currentImage){
    gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, false);
    gl.bindTexture(gl.TEXTURE_2D, texture);
     gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, 1, 1, 0, gl.RGBA, gl.UNSIGNED_BYTE,new Uint8Array([0, 0, 255, 255]));
	gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, images[currentImage]);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE);
    gl.generateMipmap(gl.TEXTURE_2D);
    gl.bindTexture(gl.TEXTURE_2D, null)
}
