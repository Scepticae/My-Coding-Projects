#ifndef JMESH_H
#define JMESH_H

#include<stdio.h>

typedef struct {
  int nvert;
  int ntri;
	float max_x, max_y, max_z;
	float min_x, min_y, min_z;
	float centroid[3];
  float **vertices;
  float **normals;
  int **triangles;
} jmesh;


/* return value: pointer to jmesh upon success, NULL upon failure*/
jmesh * new_jmesh(char *);
int fileType(char *, jmesh*);
void free_mesh(jmesh *);

#endif


