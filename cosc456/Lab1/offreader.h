#ifndef OFFREADER_H
#define OFFREADER_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"jmesh.h"

/* return value: number of vertices upon success, -1 upon failure*/
int load_off_mesh(FILE*, jmesh*);
int str_els(char *);
int triBuild(char*, int, int, int, jmesh*);
int *buildArray(char *, int);
float max_coord(float, float);
float min_coord(float, float);

#endif

