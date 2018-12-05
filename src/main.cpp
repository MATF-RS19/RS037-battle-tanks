#include <GL/glut.h>



void on_display(void);
void initialize(void);
void on_reshape(int width, int height);
void on_keyboard(unsigned char key, int x, int y);
void podloga(void);
void igrac1(void);
void igrac2(void);
void prepreka(void);

int width_window = 700;
int height_window = 500;

int main(int argc, char* argv[]){

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

  glutInitWindowSize(width_window,height_window);
  glutInitWindowPosition(100,100);
  glutCreateWindow("battle tenks");

  initialize();
  glutDisplayFunc(on_display);
  glutReshapeFunc(on_reshape);
  glutKeyboardFunc(on_keyboard);

  glutMainLoop();

  return 0;
}

void initialize(void){
  glClearColor(0,0,0,0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0,1,-1.75,0,0,0,0,0,1);
}

void on_keyboard(unsigned char key, int x, int y){
  switch (key) {
    case 27:
      exit(EXIT_SUCCESS);
      break;
  }
}


void on_reshape(int width, int height){
  width_window = width;
  height_window =  height;

  // postavljanje kamere
  glViewport(0,0,width_window,height_window);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(53,width_window/(float)height_window,1, 15);

}

void on_display(void){

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glShadeModel(GL_SMOOTH);  
   glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0,1,-1.5,0,0,1,0,0,1);
  glRotatef(90,1,0,0);

  podloga();
  //glRotatef(45,0,0,1);

    igrac1();
    igrac2();
    prepreka();

  //glRotatef(-45,0,0,1);

  glutSwapBuffers();
}
void podloga(void){
 
  glBegin(GL_POLYGON);
  glColor3f(0,0.5,0.5);
    glVertex3f(-1,1,0);
    glVertex3f(-1,-1,0);
    glVertex3f(1,-1,0);
    glVertex3f(1,1,0);	    
  glEnd(); 
     
}

void igrac1(void){
  
  GLfloat light_position[] = {0.6,0,1,0};
  GLfloat ambient_light[] = {0,0,0,1};
  GLfloat diffuse_light[] = {0.5,0,0,1};
  GLfloat specular_light[] = {0.7,0,0,1};

  GLfloat ambient_coeffs[] = {0.6,0.1,0,1};
  GLfloat diffuse_coeffs[] = {0.8,0.0,0.0,1};
  GLfloat specular_coeffs[] = {1,1,1,1};

  GLfloat shininess = 20;

  glLightfv(GL_LIGHT1,GL_POSITION,light_position);
  glLightfv(GL_LIGHT1,GL_AMBIENT,ambient_light);
  glLightfv(GL_LIGHT1,GL_DIFFUSE,diffuse_light);
  glLightfv(GL_LIGHT1,GL_SPECULAR,specular_light);

  glMaterialfv(GL_FRONT,GL_AMBIENT,ambient_coeffs);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse_coeffs);
  glMaterialfv(GL_FRONT,GL_SPECULAR,specular_coeffs);
  glMaterialf(GL_FRONT,GL_SHININESS,shininess);

 // glEnable(GL_LIGHTING);
 // glEnable(GL_LIGHT1);  
  
  glTranslatef(-0.6,0,0);
  glRotatef(90,0,1,0);
  glPushMatrix();
    glPushMatrix();
      glColor3f(0.8,0,0);
      glScalef(0.6,1,1.5);
      glutSolidCube(0.2);
    glPopMatrix();
    glPushMatrix();
      glColor3f(0.6,0,0);
      glTranslatef(0.07,0.02,0);
      glScalef(0.4,0.6,1);
      glutSolidCube(0.2);
    glPopMatrix();
    glPushMatrix();
      glColor3f(0,0,0);
      glTranslatef(0,0.22,0.1);
      glScalef(0.1,0.1,1.5);
      glutSolidCube(0.2);
    glPopMatrix();
  glRotatef(-90,0,1,0);
  glPopMatrix();
  glRotatef(-90,0,1,0);
  glTranslatef(0.6,0,0);

 // glDisable(GL_LIGHT1);
 // glDisable(GL_LIGHTING);  
  
}

void igrac2(void){
  
  GLfloat light_position[] = {-0.6,0,1,0};
  GLfloat ambient_light[] = {0,0,0,1};
  GLfloat diffuse_light[] = {0,0,0.7,1};
  GLfloat specular_light[] = {0,0,0.9,1};

  GLfloat ambient_coeffs[] = {0,0.1,0.6,1};
  GLfloat diffuse_coeffs[] = {0.0,0.0,0.8,1};
  GLfloat specular_coeffs[] = {1,1,1,1};

  GLfloat shininess = 20;

  glLightfv(GL_LIGHT0,GL_POSITION,light_position);
  glLightfv(GL_LIGHT0,GL_AMBIENT,ambient_light);
  glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse_light);
  glLightfv(GL_LIGHT0,GL_SPECULAR,specular_light);

  glMaterialfv(GL_FRONT,GL_AMBIENT,ambient_coeffs);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse_coeffs);
  glMaterialfv(GL_FRONT,GL_SPECULAR,specular_coeffs);
  glMaterialf(GL_FRONT,GL_SHININESS,shininess);

 // glEnable(GL_LIGHTING);
 // glEnable(GL_LIGHT0);
  
  glTranslatef(0.6,0,0);
  glRotatef(90,0,1,0);
  glPushMatrix();
    glPushMatrix();
      glColor3f(0,0,0.8);
      glScalef(0.6,1,1.5);
      glutSolidCube(0.2);
    glPopMatrix();
    glPushMatrix();
      glColor3f(0,0,0.6);
      glTranslatef(0.07,0.02,0);
      glScalef(0.4,0.6,1);
      glutSolidCube(0.2);
    glPopMatrix();
  glPopMatrix();
  glPushMatrix();
  glRotatef(180,0,1,0);
    glColor3f(0,0,0);
    glTranslatef(0,0.22,0.1);
    glScalef(0.1,0.1,1.5);
    glutSolidCube(0.2);
      glRotatef(-180,0,1,0);
  glPopMatrix();
  glRotatef(-90,0,1,0);
  glTranslatef(-0.6,0,0);

//  glDisable(GL_LIGHT0);
//  glDisable(GL_LIGHTING);  
  
}

void prepreka(void){
     glPushMatrix();
      glColor3f(0.2,0.2,0.2);
      glScalef(0.4,5,3);
      glutSolidCube(0.2);
    glPopMatrix();  
 }