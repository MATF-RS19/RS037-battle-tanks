#include <GL/glut.h>
#include "SOIL.h"
#include <iostream>

#define TIMER_ID 0
#define TIMER_INTERVAL 100
#define FILENAME "universe.bmp"
#define POMERAJ 0.02

int up=1;
double up_vector_y_cor=0;
static int mouse_x, mouse_y;
static float matrix[16];

void on_display(void);
void initialize(void);
void on_reshape(int width, int height);
void on_keyboard(unsigned char key, int x, int y);
void on_timer(int value);
void prepreka(void);
static void on_mouse(int button, int state, int x, int y);
static void on_motion(int x, int y);


int width_window = 700;
int height_window = 500;
int animation_ongoing = 0;
GLuint slika_pozadine;


void initialize(void){
  glClearColor(0,0,0,0);
  glGetFloatv(GL_MODELVIEW_MATRIX, matrix);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
    slika_pozadine=SOIL_load_OGL_texture("deixis_darksky.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  if(slika_pozadine==0){
   std::cout << "Nije ucitana slika" << std::endl;   
  } 
  glEnable(GL_DEPTH_TEST);
}

static void on_mouse(int button, int state, int x, int y)
{
    mouse_x = x;
    mouse_y = y;
}



static void on_motion(int x, int y)
{
    /* Promene pozicije pokazivaca misa. */
    int delta_x, delta_y;

    /* Izracunavaju se promene pozicije pokazivaca misa. */
    delta_x = x - mouse_x;
    delta_y = y - mouse_y;
    

      
    /* Pamti se nova pozicija pokazivaca misa. */
    mouse_x = x;
    mouse_y = y;

    /* Izracunava se nova matrica rotacije. */
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glLoadIdentity();
        //glRotatef(180 * (float) delta_x / width_window, 0, 1, 0);
        glRotatef(180 * (float) delta_y / height_window, 0, 0, 1);
        glMultMatrixf(matrix);

        glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
    glPopMatrix();
    
    glutPostRedisplay();
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

      glPushMatrix();
      glColor3f(0,0.5,0.5);
      glBegin(GL_POLYGON);
	glVertex3f(-m_x,m_y,m_z);
	glVertex3f(-m_x,m_y,-m_z);
	glVertex3f(m_x,m_y,-m_z);
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
      //CRVENI
      glPushMatrix();
      glTranslatef(m_x, m_y, m_z);
      glPushMatrix();      
	glPushMatrix();
	  glColor3f(0.8,0,0);
	  glScalef(1.5,0.6,1);
	  glutSolidCube(0.2);
	glPopMatrix();
	glPushMatrix();
	  glColor3f(0.6,0,0);
	  glTranslatef(0,0.1,0.02);
	  glScalef(1,0.4,0.5);
	  glutSolidCube(0.2);
	glPopMatrix();
	glPushMatrix();
	  glColor3f(0,0,0);
//	  glMultMatrixf(matrix);
	  glTranslatef(-0.2,0.15,0.02);
	  glScalef(1.5,0.1,0.1);
	  glutSolidCube(0.2);
	glPopMatrix();
      glPopMatrix();
      glTranslatef(-m_x, -m_y, -m_z);
      glPopMatrix();
      }
      
      double health(){
	glPushMatrix();
	  glTranslatef(1,-1,0);
	  glBegin(GL_POLYGON);
	    glColor3f(0,1,0);
	    glVertex3f(-0.5,0.05,0);
	    glVertex3f(-0.5,-0.05,0);
	    glColor3f(1,0,0);
	    glVertex3f(0.5,-0.05,0);
	    glVertex3f(0.5,0.05,0);
	  glEnd();
	glPopMatrix();
		
	glPushMatrix();
	  glTranslatef(1,-1,0);
	  glBegin(GL_POLYGON);
	    glColor3f(0,0,0);
	    glVertex3f(-0.5,0.05,0);
	    glVertex3f(-0.5,-0.05,0);
	    glVertex3f(-0.5+0.5*m_health_red,-0.05,0);
	    glVertex3f(-0.5+0.5*m_health_red,0.05,0);
	  glEnd();
	glPopMatrix();
	    
	return m_health_red;
      }

 
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
 
      //PLAVI
      glPushMatrix();
      glTranslatef(m_x, m_y, m_z);
      glPushMatrix();      
	glPushMatrix();
	  glColor3f(0,0,0.8);
	  glScalef(1.5,0.6,1);
	  glutSolidCube(0.2);
	glPopMatrix();
	glPushMatrix();
	  glColor3f(0,0,0.6);
	  glTranslatef(0,0.1,0.02);
	  glScalef(1,0.4,0.5);
	  glutSolidCube(0.2);
	glPopMatrix();
	/*za pucanje*/
	glPushMatrix();
	  glColor3f(0,1,0);
	  glPushMatrix();
	  glTranslatef(0,0.15,0.02);
	  glScalef(0.5,0.3,0.1);
	  glutSolidCube(0.2);
	  glPopMatrix();
	  glMultMatrixf(matrix);
	  glTranslatef(0.2,0.15,0.02);
	  glScalef(1.5,0.1,0.1);
	  glutSolidCube(0.2);
	glPopMatrix();
      glPopMatrix();
      glTranslatef(-m_x, -m_y, -m_z);
      glPopMatrix();
      }
      
      double health(){
	glPushMatrix();
	  glTranslatef(-1,-1,0);
	  glBegin(GL_POLYGON);
	    glColor3f(1,0,0);
	    glVertex3f(-0.5,0.05,0);
	    glVertex3f(-0.5,-0.05,0);
	    glColor3f(0,1,0);
	    glVertex3f(0.5,-0.05,0);
	    glVertex3f(0.5,0.05,0);
	  glEnd();
	glPopMatrix();
	
	glPushMatrix();
	  glTranslatef(-1,-1,0);
	  glBegin(GL_POLYGON);
	    glColor3f(0,0,0);
	    glVertex3f(-0.5,0.05,0);
	    glVertex3f(-0.5,-0.05,0);
	    glVertex3f(-0.5 + 0.5*m_health_blue,-0.05,0);
	    glVertex3f(-0.5 + 0.5*m_health_blue,0.05,0);
	  glEnd();
	glPopMatrix();
	  return m_health_blue;
      }
  
//private:
  
    double m_x;
    double m_y;
    double m_z;
    double m_health_blue = 0;
};
/* zid */
class obstacle{
public:
  obstacle()
  {}
  
  obstacle(double x, double y, double z)
  :m_x(x), m_y(y), m_z(z)
  {}
  
/* iscrtavanje zida i njegovo pomeranje gore-dole */
  void obstacle_draw(){
    if(up){
      m_y+=up_vector_y_cor;
      if(m_y>.5){	
	up=0;
      }
    }
    else{
      m_y-=up_vector_y_cor;
      if(m_y<=0.1){
	up=1;
      }
    }
    glPushMatrix(); 
      glColor3f(0.2,0.2,0.2);
      glTranslatef(m_x, m_y+0.1, m_z);
      glScalef(0.4,1,5);
      glutSolidCube(0.2);
    glPopMatrix();  
  }
  
  
//private:
  double m_x;
  double m_y;
  double m_z;

};

gamer1 gRed(0.6,0.06,0.5);
gamer2 gBlue(-0.6,0.06,0.5);
floor floor(1,0,1);
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
  glutMouseFunc(on_mouse);
  glutMotionFunc(on_motion);
  
  mouse_x = 0;
  mouse_y = 0;
  
  glutMainLoop();
  return 0;
}

void on_display(void){

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glShadeModel(GL_SMOOTH);  
   glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0,0.5,2,0,0,0,0,1,0);
 

  glPushMatrix();   
    glEnable(GL_TEXTURE_2D);
    glRotatef(0, 1, 0, 0); 
    glBegin(GL_QUADS);
      glBindTexture(GL_TEXTURE_2D,slika_pozadine);
      glNormal3f(0, 1, 0);
      glTexCoord2f(0, 0);
      glVertex3f(-3, -2, 0);
      glTexCoord2f(1, 0);
      glVertex3f(3, -2, 0);
      glTexCoord2f(1, 1);
      glVertex3f(3, 2, 0);
      glTexCoord2f(0, 1);
      glVertex3f(-3, 2, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
  glPopMatrix();     
  
  floor.floor_draw();
  obstacle.obstacle_draw();
  gRed.gamer1_draw();
  gBlue.gamer2_draw();
  
  gRed.health();
  gBlue.health();
  
  glutSwapBuffers();
}

void on_timer(int value){
  if(value!=TIMER_ID){
    return;
  }
  up_vector_y_cor=0.01;
  if(animation_ongoing){
  
    glutTimerFunc(TIMER_INTERVAL,on_timer, TIMER_ID);
  }
  glutPostRedisplay();
 
}
void on_keyboard(unsigned char key, int x, int y){
  switch (key) {
    case 27:
      exit(EXIT_SUCCESS);
      break;
    case 'G':
    case 'g':
      if(!animation_ongoing){
	animation_ongoing = 1;
	glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
      std::cout << "pritisnuto g" << std::endl;
      }
      break;
    case '4':
      if(gRed.m_x >= 0.32){
	gRed.m_x -=POMERAJ;
      }
      break;
    case '6':
      if(gRed.m_x < 0.86){
	gRed.m_x +=POMERAJ;
      }
      break;
    case 'd':
    case 'D':      
      if(gBlue.m_x <= -0.32){
	gBlue.m_x +=POMERAJ;
      }
      break;
    case 'a':
    case 'A':
      if(gBlue.m_x >= -0.86){
	gBlue.m_x -=POMERAJ;
      }
      break;
  }
  glutPostRedisplay();
}
