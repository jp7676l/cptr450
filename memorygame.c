//header file
#include<windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(int argc, char *argv[])
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize(800, 600);
   glutInitWindowPosition(50, 50);
   glutCreateWindow("game memory");

   // Other setup
   glClearColor(1.0, 1.0, 1.0, 1.0);
   glMatrixMode(GL_PROJECTION);
   gluOrtho2D(0.0, 800.0, 0.0, 600.0);

   glutDisplayFunc(display);
   glutMainLoop();

   return 0;
}

