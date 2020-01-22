/* lab1.c */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glut.h>
#include "utils.h"
#include "jmesh.h"

int 
main(int argc, char **argv)
{
  graphics_state gs;
	jmesh *jm;

	//Load the mesh
  jm = new_jmesh(argv[1]);
	
	//Check to see if the mesh is valid
  if (jm == NULL){
     fprintf(stderr,"load_off_mesh failed\n");
		 exit(0);
	}
	
	gs.jm = jm;
  gs.height=512;
  gs.width =512;

  print_howto();

  { /* GLUT initialization */
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(gs.width,gs.height);
    glutInitWindowPosition(100,100);
    glutCreateWindow(argv[0]);
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutKeyboardFunc(keys);
    glutMouseFunc(mouse_handler);
    glutMotionFunc(trackMotion);

  }

  init(&gs);
  glutTimerFunc(0, update, 0);
  glutMainLoop();

  return 0;
}
