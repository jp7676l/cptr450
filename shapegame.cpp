 #include <GL/glut.h>
 #include <iostream>
 #include <fstream>

  char* card[12];
  int x;
  int y;
  int fm = x/200 + y/200*4;
 
  void display(void)
  {
     glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_QUADS);
    glColor3f(0.1, 0.0f, 0.0f);
    glVertex2i(10, 10);
    glVertex2i(800, 10);
    glVertex2i(800, 400);
    glVertex2i(10, 400);
    glEnd();

     for(int photo = 0; photo < 12; photo++)
     {
     glRasterPos2i(photo*200%800, photo/4*200);//goal for y: photo position of 0,1,2,3 to give a result of 0. Position 4,5,6,7 should give me 200. 8,9,10,11 gives 400.
     glDrawPixels(200,200, GL_RGB, GL_UNSIGNED_BYTE, card[photo]);
     }
      glFlush();
  }

  
  void reshape(int width, int height)
  {
     glViewport(0, 0, width, height);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluOrtho2D(0.0, width, 0.0, height);
     glMatrixMode(GL_MODELVIEW);
  }

 void read(char *filename, int photo)
 {
  ifstream image;
  char filetype[4];
  int junk;
  int width;
  int height;
  short Planes; 
  short BitCount;
  int Compression;
  
  image.open(filename,ios::binary);
  image.read(filetype,2);
  image.read(&junk,4);//file size
  image.read(&junk,4);//reserved 4 bytes
  image.read(&junk,4);//offset bits
  image.read(&junk,4);//headersize
  image.read(&width,4);
  image.read(&height,4);
  image.read(&Planes,2);
  image.read(&BitCount,2);
  image.read(&Compression,4);
  image.read(&junk,4);//imagesize
  image.read(&junk,4);//xpelspermeter
  image.read(&junk,4);//yperlspermeter
  image.read(&junk,4);//colorsused
  image.read(&junk,4);//colorsimportant  

  cout << "Read" << width << "x" << height << "image" << endl;

  if (Planes != 1 || BitCount !=24 || Compression !=0)
  {
    cout << "Not the image format your looking for" <<endl;
    return;
  }
  int imagesize = width * height * 3;
  card[photo] = new char[imagesize];
  image.read(card[photo],imagesize);
  }

void setup()
{
 read("ycard.bmp",0);
 read("ycard1.bmp",1);
 read("ycard2.bmp",2);
 read("ycard3.bmp",3);
 read("ycard4.bmp",4);
 read("ycard5.bmp",5);
 read("ycard6.bmp",6);
 read("ycard7.bmp",7);
 read("ycard8.bmp",8);
 read("ycard9.bmp",9);
 read("ycard10.bmp",10);
 read("ycard11.bmp",11);
 
}

void handlekey(unsigned char key, int x, int y)
{
   int height;
   y = height - y;
   switch (key)
   {
      case 's': // Start game
      break;
      case 'h': // Give hint
      break;
      case 'q': // Quit
      exit(1);
   }

  glutPostRedisplay();
}

 void handlemouse(int button, int state, int x, int y)
{
   //int height;
  //y = height - y;
 
   if (state != GLUT_DOWN) return;

   switch (button)
   {
      case GLUT_LEFT_BUTTON:  // Swap tiles
      cout << "coordinates " << x << y << endl;
      cout << "This is tile: " << x/200 + y/200*4 <<  endl;
      cout << "Recently clicked on tile: " << fm  << endl;
      
      case GLUT_RIGHT_BUTTON: // Optional
      break;
   }

  glutPostRedisplay();
}
 

  int main(int argc, char *argv[])
  {
     glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
     glutInitWindowSize(800, 600);
     glutInitWindowPosition(50, 50);
     glutCreateWindow("Project 1");

     // Other setup
     setup();
     glClearColor(1.0, 1.0, 1.0, 1.0);
     glMatrixMode(GL_PROJECTION);
     gluOrtho2D(0.0, 800.0, 0.0, 600.0);

     glutDisplayFunc(display);
     glutReshapeFunc(reshape);
     glutKeyboardFunc(handlekey);     // Add keyboard
     glutMouseFunc(handlemouse);      // Add mouse
     glutMainLoop();

     return 0;
  }

