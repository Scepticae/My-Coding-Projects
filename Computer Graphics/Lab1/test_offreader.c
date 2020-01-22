#include <stdio.h>
#include <stdlib.h>
#include "jmesh.h"

//JMesh Display Function
void mesh_printer(jmesh *);

int
main(void)
{
  jmesh * mesh;

  mesh = new_jmesh(stdin);
  if (mesh == NULL)
     fprintf(stderr,"load_off_mesh failed\n");
	 
	//Test Mesh
	mesh_printer(mesh);
 
  free_mesh(mesh);
  return 0;
}

//JMesh Printer
void mesh_printer(jmesh *jm){
	int i=0;
	
	for(i=0; i < jm->nvert; i++){
		printf("Vert:%d %f %f %f\n", i, jm->vertices[i][0], jm->vertices[i][1], jm->vertices[i][2]);
	}
	for(i=0; i < jm->ntri; i++){
		printf("Triangle:%d %d %d %d\n", i, jm->triangles[i][0], jm->triangles[i][1], jm->triangles[i][2]);
	}
}