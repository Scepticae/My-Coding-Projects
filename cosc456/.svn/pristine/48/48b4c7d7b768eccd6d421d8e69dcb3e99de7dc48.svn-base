#include"offreader.h"
#include"jmesh.h"
#include<stdio.h>
#include<string.h>
#include<ctype.h>

/* return value: number of vertices upon success, -1 upon failure*/
int load_off_mesh(FILE * fp, jmesh * jm){
	int i = 0, verts = 0, faces = 0, edges = 0;
	int count = 0, nsides =0, ntris = 0;
	float count_x = 0, count_y = 0, count_z = 0;
	char tmp[100];
	char format[100];
	
	//Check to make sure it is an OFF file
	fscanf(fp, "%s", format);
	
	if(strcmp(format, "OFF") != 0){
		fprintf(stderr, "Not an OFF file\n");
		return -1;
	}
	
	//Read in the 2nd line for verts, faces and edges
	fscanf(fp, "%d", &verts);
	fscanf(fp, "%d", &faces);
	fscanf(fp, "%d", &edges);
	
	//Set jmesh number of vertices
	jm->nvert = verts;
	
	//Create Storage for Vertices
	jm->vertices = (float**)malloc(sizeof(float*)*verts);
	
	//Read in the vertices
	for(i=0; i < verts; i++){
		jm->vertices[i] = (float*)malloc(sizeof(float)*3);
		fscanf(fp, "%f", &jm->vertices[i][0]);
	  fscanf(fp, "%f", &jm->vertices[i][1]);
		fscanf(fp, "%f", &jm->vertices[i][2]);
		
		//Keep totals for x, y, and z
		count_x += jm->vertices[i][0];
		count_y += jm->vertices[i][1];
		count_z += jm->vertices[i][2];
		
		//Set max and min values for initial verts
		if(i == 0){
			jm->max_x = jm->vertices[i][0];
			jm->max_y = jm->vertices[i][1];
			jm->max_z = jm->vertices[i][2];
			jm->min_x = jm->vertices[i][0];
			jm->min_y = jm->vertices[i][1];
			jm->min_z = jm->vertices[i][2];
		}
		//Update the max and min for each coord
		else{
			jm->max_x = max_coord(jm->max_x, jm->vertices[i][0]);
			jm->max_y = max_coord(jm->max_y, jm->vertices[i][1]);
			jm->max_z = max_coord(jm->max_z, jm->vertices[i][2]);
			jm->min_x = min_coord(jm->min_x, jm->vertices[i][0]);
			jm->min_y = min_coord(jm->min_y, jm->vertices[i][1]);
			jm->min_z = min_coord(jm->min_z, jm->vertices[i][2]);
		}
	}
	
	//Set the Centroid for the object
	jm->centroid[0] = count_x / verts;
	jm->centroid[1] = count_y / verts;
	jm->centroid[2] = count_z / verts;
	
	//Create Initial storage for triangles
	jm->triangles = (int**)malloc(sizeof(int*)*(faces*2));
	
	//Clear Junk from buffer
	fgets(tmp, 100, fp);
	
	//Populates the triangle array and figures the number of triangles
	for(i=0; i < faces; i++){
		fgets(tmp, 100, fp);
		sscanf(tmp, "%d", &nsides);
		count = str_els(tmp);
		ntris = triBuild(tmp, ntris, nsides, count, jm);
	}
	
	//Set the mesh's number of triangles
	jm->ntri = ntris;
	
	//Returns the number of triangles
	return ntris;
}

int str_els(char *temp){
	int i;
	int c = 0;
	
	//Counts the number of words
	for(i=0; temp[i]!='\n'; i++){
		if(isspace(temp[i]))c++;
	}
	return c;
}

int triBuild(char *tmp, int n, int s, int c, jmesh *jm){
	int i, j = 1, k =2;
	int num;
	int *sides;
	
	//Get number of triangles to add
	num = s-2;

	//Split the String into ints
	sides = buildArray(tmp, s);

	//Set memory for each triangle array
	for(i=0; i < num; i++){
		jm->triangles[n] = (int*)malloc(sizeof(int)*3);

		//Add triangles to the triangle array
		if(num > 1){
			jm->triangles[n][0] = sides[0];
			jm->triangles[n][1] = sides[j];
			jm->triangles[n][2] = sides[k];
			j++;
			k++;
		}
		else{
			jm->triangles[n][0] = sides[0];
			jm->triangles[n][1] = sides[1];
			jm->triangles[n][2] = sides[2];
		}
		
		//Increment the Triangle array
		n++;
	}
	
	return n;
}

int *buildArray(char *temp, int sides){
	int i = 0, j = 0, n = 0;
	char t[10];
	int *nsides;
	
	//Allocate Memory
	nsides = (int*)malloc(sizeof(int)*sides);
	
	//Split the string into integers and add to a temp array
	for(i=0; j < sides+1; i++){
		t[n] = temp[i];
		if(isspace(temp[i])){
			t[n] = '\0';
			if(j > 0){
				nsides[j-1] = atoi(t);
			}
			n = 0;
			j++;
		}
		else
			n++;
	}
	
	//Returns the vert numbers corresponding to the number of sides
	return nsides;
}

float max_coord(float n_val, float o_val){
	if(n_val > o_val) return n_val;
	else return o_val;
}

float min_coord(float n_val, float o_val){
	if(n_val < o_val) return n_val;
	else return o_val;
}