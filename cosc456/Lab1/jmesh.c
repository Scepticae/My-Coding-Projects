#include<stdlib.h>
#include<stdio.h>
#include"jmesh.h"
#include"offreader.h"

jmesh * 
new_jmesh(char *file)
{
	int check = 0;
  jmesh * jm;

  jm = (jmesh*)malloc(sizeof(jmesh));

  check = fileType(file, jm);
	
	if(check == -1){jm = NULL;}
	
  return jm;
}

int fileType(char *t, jmesh *jm){
	int n = 0;
	FILE *fp;
	
  fp=fopen(t, "r");
	
	//Check to See if File Exists
	if(fp==NULL){
		fprintf(stderr,"could not open: %s\n", t);
    fprintf(stderr,"Format: (2 args)-> executable filename\n");
    exit(1);
  }
	
	//Check Which Type to Load
	if (strcmp(strchr(t, '.'),".off")==0) {
		n = load_off_mesh(fp, jm);
	}
	else{
		fprintf(stderr,"File is not of type .off\n");
		n = -1;
	}
	
	return n;
}
void free_mesh(jmesh *jm){
	;
}