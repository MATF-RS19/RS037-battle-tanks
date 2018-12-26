#include <GL/glut.h>
#include "SOIL.h"
#include <iostream>

#define TIMER_ID 0
#define TIMER_INTERVAL 100
#define FILENAME "universe.bmp"


void on_display(void);
void initialize(void);
void on_reshape(int width, int height);
void on_keyboard(unsigned char key, int x, int y);
void on_timer(int value);
void prepreka(void);

int width_window = 700;
int height_window = 500;
int animation_ongoing = 0;
GLuint slika_pozadine;


void initialize(void){
  glClearColor(0,0,0,0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0,1,-1.75,0,0,0,0,0,1);
  	
  GLfloat light_position[] = {0,0,1,0};
  GLfloat ambient_light[] = {0,0,0,1};
  GLfloat diffuse_light[] = {0.5,0,0,1};
  GLfloat specular_light[] = {0.7,0,0,1};

  GLfloat ambient_coeffs[] = {0.6,0.1,0,1};
  GLfloat diffuse_coeffs[] = {0.2,0.2,0.2,1};
  GLfloat specular_coeffs[] = {0.1,0.1,0.1,1};

  GLfloat shininess = 20;

  glLightfv(GL_LIGHT1,GL_POSITION,light_position);
  glLightfv(GL_LIGHT1,GL_AMBIENT,ambient_light);
  glLightfv(GL_LIGHT1,GL_DIFFUSE,diffuse_light);
  glLightfv(GL_LIGHT1,GL_SPECULAR,specular_light);

  glMaterialfv(GL_FRONT,GL_AMBIENT,ambient_coeffs);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse_coeffs);
  glMaterialfv(GL_FRONT,GL_SPECULAR,specular_coeffs);
  glMaterialf(GL_FRONT,GL_SHININESS,shininess);

}

void on_keyboard(unsigned char key, int x, int y){
  switch (key) {
    case 27:
      exit(EXIT_SUCCESS);
      break;
    case 's':
    case 'S':
      if(!animation_ongoing){
	animation_ongoing = 1;
	glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
      std::cout << "pritisnuto s" << std::endl;
      }
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

class floor{
public:
    floor(double x, double y, double z)
    : m_x(x), m_y(y), m_z(z)
    {};
    
    void floor_draw(){
      
      glBegin(GL_POLYGON);
      glColor3f(0,0.5,0.5);
	glVertex3f(-m_x,m_y,m_z);
	glVertex3f(-m_x,-m_y,m_z);
	glVertex3f(m_x,-m_y,m_z);
	glVertex3f(m_x,m_y,m_z);	    
      glEnd(); 
    }
    
private:
  
  double m_x;
  double m_y;
  double m_z;
  
};

class gamer1{

public:
    gamer1()
    {};
    
    gamer1(double x, double y, double z)
    : m_x(x), m_y(y), m_z(z){};
  
    void gamer1_draw(void){

      
    GLfloat light_ambient[] = {0.6,0.5,0.1,0,0};
    GLfloat light_diffuse[] = {0.4,0.2,0.8,0};
    GLfloat light_specular[] = {0.8,1,0,0.5};
    GLfloat light_position[] = {-0.5,-0.5,-1,0};

    GLfloat model_ambient[] = {0.9,0, 0, 0};
    GLfloat model_diffuse[] = {0.1,0.2,0.8,0};
    GLfloat model_specular[] = {0.75,0.6,0,1};
    GLfloat model_shininess = 20;

   glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);
   glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse);
   glLightfv(GL_LIGHT0,GL_SPECULAR,light_specular);
   glLightfv(GL_LIGHT0,GL_POSITION,light_position);
      
   glMaterialfv(GL_FRONT,GL_AMBIENT,model_ambient);
   glMaterialfv(GL_FRONT,GL_DIFFUSE,model_diffuse);
   glMaterialfv(GL_FRONT,GL_SPECULAR,model_specular);
   glMaterialf(GL_FRONT,GL_SHININESS,model_shininess);




      //CRVENI
      glTranslatef(m_x, m_y, m_z);
      glPushMatrix();
	glRotatef(90,0,1,0);
	glPushMatrix();
	  glColor3f(0.8,0,0);
	  glScalef(0.6,1,1.5);
	  glutSolidCube(0.2);
	glPopMatrix();
	glPushMatrix();
	  glEnable(GL_LIGHTING);
	  glEnable(GL_LIGHT0);

	  glColor3f(0.6,0,0);
	  glTranslatef(0.1,0.02,0);
	  glScalef(0.4,0.6,1);
	  glutSolidCube(0.2);
	  glDisable(GL_LIGHT0);
	  glDisable(GL_LIGHTING);
	glPopMatrix();
	glPushMatrix();
	  glColor3f(0,0,0);
	  glTranslatef(0.15,0.02,0.1);
	  glScalef(0.1,0.1,1.5);
	  glutSolidCube(0.2);
	glPopMatrix();
      glPopMatrix();	
      glTranslatef(-m_x, -m_y, -m_z);
      }
      
      double health(){
	glPushMatrix();
	  glRotatef(-90,1,0,0);
	  glTranslatef(-0.5,1,0);
	  glBegin(GL_POLYGON);
	    glColor3f(1,0,0);
	    glVertex3f(-0.3,0.03,0);
	    glVertex3f(-0.3,-0.03,0);
	    glColor3f(0,1,0);
	    glVertex3f(0.3,-0.03,0);
	    glVertex3f(0.3,0.03,0);
	  glEnd();
	glPopMatrix();
		
	glPushMatrix();
	  glRotatef(-90,1,0,0);
	  glTranslatef(-0.5,1,0);
	  glBegin(GL_POLYGON);
	    glColor3f(0,0,0);
	    glVertex3f(-0.3,0.03,0);
	    glVertex3f(-0.3,-0.03,0);
	    glVertex3f(-0.3+0.3*m_health_red,-0.03,0);
	    glVertex3f(-0.3+0.3*m_health_red,0.03,0);
	  glEnd();
	glPopMatrix();
	    
	return m_health_red;
      }

private:  
    double m_x;
    double m_y;
    double m_z;
    double m_health_red  = 0;
   
};

class gamer2{

public:
    gamer2()
    {};
    
    gamer2(double x, double y, double z)
    : m_x(x), m_y(y), m_z(z){};
  
    void gamer2_draw(void){
      
    GLfloat light_ambient[] = {0.6,0.5,0.1,0,0};
    GLfloat light_diffuse[] = {0.4,0.2,0.8,0};
    GLfloat light_specular[] = {0.8,1,0,0.5};
    GLfloat light_position[] = {0.5,-0.5,-1,0};

    GLfloat model_ambient[] = {0,0, 0.9, 0};
    GLfloat model_diffuse[] = {0.1,0.2,0.8,0};
    GLfloat model_specular[] = {0.75,0.6,0,1};
    GLfloat model_shininess = 20;

   glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);
   glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse);
   glLightfv(GL_LIGHT0,GL_SPECULAR,light_specular);
   glLightfv(GL_LIGHT0,GL_POSITION,light_position);
      
   glMaterialfv(GL_FRONT,GL_AMBIENT,model_ambient);
   glMaterialfv(GL_FRONT,GL_DIFFUSE,model_diffuse);
   glMaterialfv(GL_FRONT,GL_SPECULAR,model_specular);
   glMaterialf(GL_FRONT,GL_SHININESS,model_shininess);

      //PLAVI
      glTranslatef(m_x, m_y, m_z);
      glPushMatrix();
	glRotatef(180,0,0,1);
	glRotatef(90,0,1,0);
	glPushMatrix();
	  glColor3f(0,0,0.8);
	  glScalef(0.6,1,1.5);
	  glutSolidCube(0.2);
	glPopMatrix();
	glPushMatrix();
	  glEnable(GL_LIGHT0);
	  glEnable(GL_LIGHTING);
	  glColor3f(0,0,0.6);
	  glTranslatef(0.1,0.02,0);
	  glScalef(0.4,0.6,1);
	  glutSolidCube(0.2);
	  glDisable(GL_LIGHT0);
      glDisable(GL_LIGHTING);
     
	glPopMatrix();
	glPushMatrix();
	  glColor3f(0,0,0);
	  glTranslatef(0.15,0.02,0.1);
	  glScalef(0.1,0.1,1.5);
	  glutSolidCube(0.2);
	glPopMatrix();
      glPopMatrix();	
      glTranslatef(-m_x, -m_y, -m_z);

      }
      
      double health(){
	glPushMatrix();
	  glRotatef(-90,1,0,0);
	  glTranslatef(0.5,1,0);
	  glBegin(GL_POLYGON);
	    glColor3f(0,1,0);
	    glVertex3f(-0.3,0.03,0);
	    glVertex3f(-0.3,-0.03,0);
	    glColor3f(1,0,0);
	    glVertex3f(0.3,-0.03,0);
	    glVertex3f(0.3,0.03,0);
	  glEnd();
	glPopMatrix();
	
	glPushMatrix();
	  glRotatef(-90,1,0,0);
	  glTranslatef(0.5,1,0);
	  glBegin(GL_POLYGON);
	    glColor3f(0,0,0);
	    glVertex3f(-0.3,0.03,0);
	    glVertex3f(-0.3,-0.03,0);
	    glVertex3f(-0.3 + 0.3*m_health_blue,-0.03,0);
	    glVertex3f(-0.3 + 0.3*m_health_blue,0.03,0);
	  glEnd();
	glPopMatrix();
	  return m_health_blue;
      }
  
private:
  
    double m_x;
    double m_y;
    double m_z;
    double m_health_blue = 0;
};

class obstacle{
public:
  
  obstacle()
  {}
  
  obstacle(double x, double y, double z)
  :m_x(x), m_y(y), m_z(z)
  {}

  void obstacle_draw(){
    
    glPushMatrix(); 
      glColor3f(0.2,0.2,0.2);
      glTranslatef(m_x, m_y, m_z);
      glScalef(0.4,5,3);
      glutSolidCube(0.2);
    glPopMatrix();  
  }
  
  
private:
  double m_x;
  double m_y;
  double m_z;

};

gamer1 gRed(-0.6,0,0);
gamer2 gBlue(0.6,0,0);
floor floor(1,1,0);
obstacle obstacle(0,0,0);

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
  glutTimerFunc(TIMER_INTERVAL,on_timer,TIMER_ID);
  
  slika_pozadine=SOIL_load_OGL_texture("deixis_darksky.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  if(slika_pozadine==0){
   std::cout << "Nije ucitana slika" << std::endl;   
  }  
  
  glutMainLoop();

  return 0;
}

void on_display(void){

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glShadeModel(GL_SMOOTH);  
   glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0,1,-1.5,0,0,1,0,0,1);
  glRotatef(90,1,0,0);
 
  glPushMatrix();   
    glEnable(GL_TEXTURE_2D);
    glRotatef(-60, 1, 0, 0); 
    glBegin(GL_QUADS);
      glBindTexture(GL_TEXTURE_2D,slika_pozadine);
      glNormal3f(0, 1, 0);
      glTexCoord2f(0, 0);
      glVertex3f(-2, -2, 0);
      glTexCoord2f(1, 0);
      glVertex3f(2, -2, 0);
      glTexCoord2f(1, 1);
      glVertex3f(2, 2, 0);
      glTexCoord2f(0, 1);
      glVertex3f(-2, 2, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
  glPopMatrix();     
  
  floor.floor_draw();
  obstacle.obstacle_draw();
  gRed.gamer1_draw();
  gBlue.gamer2_draw();
  gRed.health();
  gBlue.health();
  /*
  if((gRed.health() <= 9) && (gBlue.health() <= 9)){
    glutTimerFunc(TIMER_INTERVAL,on_timer, TIMER_ID);    
  }*/
  
  glutSwapBuffers();
}

void on_timer(int value){
  if(value!=TIMER_ID){
    return;
  }
  
  if(animation_ongoing){
    obstacle.obstacle_draw();
    glutTimerFunc(TIMER_INTERVAL,on_timer, TIMER_ID);
  }
  
}
