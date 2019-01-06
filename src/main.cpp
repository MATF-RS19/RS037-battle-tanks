#include <GL/glut.h>
#include "SOIL.h"
#include <iostream>

#define TIMER_ID 0
#define TIMER_INTERVAL 100
#define FILENAME "universe.bmp"
#define POMERAJ 0.02

int up=1, up2 = 1, up3 = 1, up4 = 1;
double up_vector_y_cor=0;

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
  
    slika_pozadine=SOIL_load_OGL_texture("deixis_darksky.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  if(slika_pozadine==0){
   std::cout << "Nije ucitana slika" << std::endl;   
  } 
  glEnable(GL_DEPTH_TEST);
}

void start_game(void){
	char tekst1[256], *p1;
	sprintf(tekst1, "Start game - g");

	glPushMatrix();
	  glRotatef(90,1,0,0);
	  glColor3f(1,1,1);
	  glRasterPos3f(-0.2,0,-0.5);
	  for(p1 = tekst1; *p1!= '\0'; p1++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p1);
	}
	glPopMatrix();
	  
}



void game_over(void){
	char tekst1[256], *p1;
	sprintf(tekst1, "Game over");

	glPushMatrix();
	  glRotatef(90,1,0,0);
	  glColor3f(1,1,1);
	  glRasterPos3f(-0.2,0,-0.5);
	  for(p1 = tekst1; *p1!= '\0'; p1++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p1);
	}
	glPopMatrix();
	  
}


void on_reshape(int width, int height){
  width_window = width;
  height_window =  height;

  // postavljanje kamere
  glViewport(0,0,width_window,height_window);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70,width_window/(float)height_window,1, 100);
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0,0.5,2,0,0,0,0,1,0);
}

class floor_tank{
public:
    floor_tank(double x, double y, double z)
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
      //CRVENI igrac
      glPushMatrix();
      glTranslatef(m_x, m_y, m_z);
      /* iscrtavanje podnozja tenka */
      glPushMatrix();      
	glPushMatrix();
	  glColor3f(0.8,0,0);
	  glScalef(1.5,0.6,1);
	  glutSolidCube(0.1);
	glPopMatrix();
	/* iscrtavanje gornjeg dela tenka */
	glPushMatrix();
	  glColor3f(0.6,0,0);
	  glTranslatef(-0.01,0.05,0.02);
	  glScalef(1,0.4,0.5);
	  glutSolidCube(0.1);
	  
	glPopMatrix();
	/* nisan -za pucanje */
	glPushMatrix();
	glTranslatef(-0.01,0.05,0);
	glRotatef(-m_rot, 0,0,1);
	  glColor3f(0,1,0);
	  glTranslatef(-0.08,0.03,0.02);
	  glScalef(1.5,0.1,0.1);
	  glutSolidCube(0.1);
	glPopMatrix();
      glPopMatrix();
      glTranslatef(-m_x, -m_y, -m_z);
      glPopMatrix();
      }
      /* zeleno crveni pravougaonik koji pokazuje koliko je helta ostalo igracu pre prekida igrice */
      void health(){
	glPushMatrix();
	  glTranslatef(1,-0.5,0);
	  glBegin(GL_POLYGON);
	    glColor3f(0,1,0);
	    glVertex3f(-0.3,0.05,0);
	    glVertex3f(-0.3,-0.05,0);
	    glColor3f(1,0,0);
	    glVertex3f(0.3,-0.05,0);
	    glVertex3f(0.3,0.05,0);
	  glEnd();
	glPopMatrix();
	/* iscrtavanje crnog pravouganoika preko helta tako da pokazuje koliko puta je ppogodjen igrac */
	glPushMatrix();
	  glTranslatef(1,-0.5,0);
	  glBegin(GL_POLYGON);
	    glColor3f(0,0,0);
	    glVertex3f(-0.3,0.05,0);
	    glVertex3f(-0.3,-0.05,0);
	    glVertex3f(-0.3+0.3*m_health_red,-0.05,0);
	    glVertex3f(-0.3+0.3*m_health_red,0.05,0);
	  glEnd();
	glPopMatrix();
	    
      }
        /* merac brzine metka koji se ispaljuje  */
    void speed(){
   /*skala crveno zelena za brzinu po kojoj se krece beli pravouganoik koji ustvari odredjuje brzinu metka */
      glDisable(GL_DEPTH_TEST);
      glTranslatef(-0.9,0.5,0);   
	glPushMatrix();
	  glPushMatrix();
	  glBegin(GL_POLYGON);
	    glColor3f(1,0,0);
	    glVertex3f(0.02,0.15,0.5);
	    glVertex3f(-0.02,0.15,0.5);
	    glColor3f(0,1,0);
	    glVertex3f(-0.02,-0.15,0.5);
	    glVertex3f(0.02,-0.15,0.5);
	  glEnd();

	glPopMatrix();
	
    if(up2){
      m_y2+=up_vector_y_cor;
      if(m_y2>0.13){	
	up2=0;
      }
    }
    else{
      m_y2-=up_vector_y_cor;
      if(m_y2<=-0.13){
	up2=1;
      }
    }
    
    glTranslatef(0,-m_y2,0);
    glPushMatrix();
    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
      glVertex3f(0.02,0.01,0.5);
      glVertex3f(-0.02,0.01,0.5);
      glVertex3f(-0.02,-0.01,0.5);
      glVertex3f(0.02,-0.01,0.5);    
    glEnd();
    glPopMatrix();
    glTranslatef(0,m_y2,0);
	
    glPopMatrix();
    glTranslatef(0.9,-0.5,0);   
  }
    double m_x;
    double m_y, m_y2 = 0;
    double m_z;
    double m_rot = 0;
    double m_health_red  = 0;
};

class fire_red{
  
public:
  fire_red()
  {}
  
   fire_red(double x, double y, double z, int fire_r)
   :m_x(x), m_y(y), m_z(z), fire_r(fire_r){};
   /* 'metak' koji ispaljuje crveni igrac */
   void fire(double m_x, double m_y, double m_z){
   	glDisable(GL_DEPTH_TEST);

	glPushMatrix();
	  glTranslatef((m_x), (m_y+0.08), m_z);
	  glPushMatrix();
	  glRotatef(-fire_rot, 0,0,1);
	  glTranslatef(-0.15,0.01,0.01);
	  glColor3f(1,1,1);
	  glutSolidSphere(0.01,10,10);
	glPopMatrix();
	glPopMatrix();
      }
      
  double m_x;
  double m_y;
  double m_z;
  int fire_r = 0;
  double fire_rot;
  double fire_speed;
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
      /* iscrtavanje podnozja tenka */
      glPushMatrix();      
	glPushMatrix();
	  glColor3f(0,0,0.8);
	  glScalef(1.5,0.6,1);
	  glutSolidCube(0.1);
	glPopMatrix();
	/* iscrtavanje gornjeg dela tenka */
	glPushMatrix();
	  glColor3f(0,0,0.6);
	  glTranslatef(0.01,0.05,0.02);
	  glScalef(1,0.4,0.5);
	  glutSolidCube(0.1);
	glPopMatrix();
	/* nisan -za pucanje */
	glPushMatrix();
	glTranslatef(0.01,0.05,0);
	glRotatef(m_rot,0,0,1);
	  glColor3f(0,1,0);
	  glTranslatef(0.08,0.03,0.02);
	  glScalef(1.5,0.1,0.1);
	  glutSolidCube(0.1);
	glPopMatrix();
      glPopMatrix();
      glTranslatef(-m_x, -m_y, -m_z);
      glPopMatrix();
      }
      /* zeleno crveni pravougaonik koji pokazuje koliko je helta ostalo igracu pre prekida igrice */

      void health(){
	glPushMatrix();
	  glTranslatef(-1,-0.5,0);
	  glBegin(GL_POLYGON);
	    glColor3f(1,0,0);
	    glVertex3f(-0.3,0.05,0);
	    glVertex3f(-0.3,-0.05,0);
	    glColor3f(0,1,0);
	    glVertex3f(0.3,-0.05,0);
	    glVertex3f(0.3,0.05,0);
	  glEnd();
	glPopMatrix();
	/* iscrtavanje crnog pravouganoika preko helta tako da pokazuje koliko puta je ppogodjen igrac */	
	glPushMatrix();
	  glTranslatef(-1,-0.5,0);
	  glBegin(GL_POLYGON);
	    glColor3f(0,0,0);
	    glVertex3f(0.3,-0.05,0);
	    glVertex3f(0.3,0.05,0);
	    glVertex3f(0.3- 0.3*m_health_blue,0.05,0);
	    glVertex3f(0.3- 0.3*m_health_blue,-0.05,0);
	  glEnd();
	glPopMatrix();
      }
        /* merac brzine metka koji se ispaljuje  */      
    void speed(){
	glDisable(GL_DEPTH_TEST);
      glTranslatef(0.9,0.5,0);   
	glPushMatrix();
	  glPushMatrix();
	  glBegin(GL_POLYGON);
	    glColor3f(1,0,0);
	    glVertex3f(0.02,0.15,0.5);
	    glVertex3f(-0.02,0.15,0.5);
	    glColor3f(0,1,0);
	    glVertex3f(-0.02,-0.15,0.5);
	    glVertex3f(0.02,-0.15,0.5);
	  glEnd();

	glPopMatrix();
	
    if(up2){
      m_y2-=up_vector_y_cor;
      if(m_y2>0.13){	
	up2=0;
      }
    }
    else{
      m_y2+=up_vector_y_cor;
      if(m_y2<=-0.13){
	up2=1;
      }
    }
    glTranslatef(0,-m_y2,0);
    glPushMatrix();
    glColor3f(1,1,1);
      glBegin(GL_POLYGON);
	glVertex3f(0.02,0.01,0.5);
	glVertex3f(-0.02,0.01,0.5);
	glVertex3f(-0.02,-0.01,0.5);
	glVertex3f(0.02,-0.01,0.5);    
	glEnd();
    glPopMatrix();
    glTranslatef(0,m_y2,0);
	
    glPopMatrix();
    glTranslatef(-0.9,-0.5,0);   

  }
  
    double m_x;
    double m_y, m_y2 = 0;
    double m_z;
    double m_rot = 0;
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

class fire_blue{
  
public:
  fire_blue()
  {}
  
   fire_blue(double x, double y, double z, int fire_b)
   :m_x(x), m_y(y), m_z(z), fire_b(fire_b){};
   /* 'metak' koji ispaljuje crveni igrac */   
   void fire(double m_x, double m_y, double m_z){
   	glDisable(GL_DEPTH_TEST);
   /*skala crveno zelena za brzinu po kojoj se krece beli pravouganoik koji ustvari odredjuje brzinu metka */
	glPushMatrix();
	  glTranslatef((m_x), (m_y+0.08), m_z);
	  glPushMatrix();
	  glRotatef(fire_rot, 0,0,1);
	  glTranslatef(0.15,0.01,0.01);
	  glColor3f(1,1,1);
	  glutSolidSphere(0.01,10,10);
	glPopMatrix();
	glPopMatrix();
      }
      
  double m_x;
  double m_y;
  double m_z;
  int fire_b = 0;
  double fire_rot;
  double fire_speed;
};

gamer1 gRed(0.6,0.06,0.25);
gamer2 gBlue(-0.6,0.06,0.25);
floor_tank floor_tank(1,0,0.5);
obstacle obstacle(0,0,0);
fire_red fire_red(0,0,0,0);
fire_blue fire_blue(0,0,0,0);

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

void on_display(void){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  /* postavljanje slike kao pozadinu */    
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
    /* iscrtavanje helta za oba igraca */   
   gRed.health();
   gBlue.health();
   /* iscrtavanje podloge */
   floor_tank.floor_draw();
   /* iscrtavanje sivog zida koji se pomera */
   obstacle.obstacle_draw();
   /* iscrtavanje oba igraca */
   gRed.gamer1_draw();
   gBlue.gamer2_draw();
   /* iscrtavanje merava brzine */
   gBlue.speed(); 
   gRed.speed(); 
/* provera za ispis 'start_game' i 'game_over' i ispisivanje kada sta treba */
   if((animation_ongoing == 0) && 
     (gBlue.m_health_blue == 0) &&
     (gRed.m_health_red == 0)){
     start_game();
  }else{
    if(animation_ongoing == 0){
      game_over();
    }
  }
   
   /* provera da li je crveni tenk ispalio metak */
   if(fire_red.fire_r){ 
     
    glPushMatrix();
      glTranslatef(fire_red.m_x,fire_red.m_y,0);
      fire_red.fire(gRed.m_x, gRed.m_y, gRed.m_z);
      //&& (fire_red.m_y < (obstacle.m_y+0.33))&& (fire_red.m_y > (obstacle.m_y-0.33))
      if((fire_red.m_x >=gBlue.m_x -0.03) && 
	 (fire_red.m_x <=gBlue.m_x +0.03) &&
	 (fire_red.m_y >=gBlue.m_y - 0.02)){
	fire_red.fire_r = 0;
	gBlue.m_health_blue +=0.3;
      }
    glPopMatrix();    
   }
   
   /* provera da li je plavi tenk ispalio metak */
   if(fire_blue.fire_b){ 
     
    glPushMatrix();
      glTranslatef(fire_blue.m_x,fire_blue.m_y,0);
      fire_blue.fire(gBlue.m_x, gBlue.m_y, gBlue.m_z);
      // && (fire_blue.m_y < (obstacle.m_y+0.33))&& (fire_blue.m_y > (obstacle.m_y-0.33))
      if((fire_blue.m_x <=gRed.m_x +0.03) &&
	 (fire_blue.m_x >=gRed.m_x -0.03) &&
	 (fire_blue.m_y >= gRed.m_y - 0.02)){
	fire_blue.fire_b = 0;
	gRed.m_health_red +=0.3;
      }
    glPopMatrix();    
   }
 
  glutSwapBuffers();
}

/* on_timer funkcija koja se poziva uvek kada se pokrene animacija */
void on_timer(int value){
  if(value!=TIMER_ID){
    return;
  }
  up_vector_y_cor=0.01;
 
  if((fire_red.m_x > -3)){
    //&&(fire_red.m_y < (obstacle.m_y+0.33))&& (fire_red.m_y > (obstacle.m_y-0.33))){
    
    fire_red.m_x-=(gRed.m_y2+0.15);
   
     if(up4){
      fire_red.m_y+=gRed.m_y2+0.15;
      if(fire_red.m_y>=0.5){	
	up4=0;
      }
    }
    else{
      fire_red.m_y-=gRed.m_y2+0.15;
      if(fire_red.m_y<=0.1){
	up4=1;
      }
    }
  }
  else{
    fire_red.m_y-=20;
    fire_red.fire_r =0;
  }

    if((fire_blue.m_x < 3)){
      //&&(fire_blue.m_y < (obstacle.m_y+0.33))&& (fire_blue.m_y > (obstacle.m_y-0.33))){
   fire_blue.m_x+=(gBlue.m_y2+0.15);
   
     if(up3){
      fire_blue.m_y+=gBlue.m_y2+0.15;
      if(fire_blue.m_y>=0.5){	
	up3=0;
      }
    }
    else{
      fire_blue.m_y-=gBlue.m_y2+0.15;
      if(fire_blue.m_y<=0.1){
	up3=1;
      }
    }
  }
  else{
    fire_blue.m_y-=20;
    fire_blue.fire_b =0;
  }
  
  if(gBlue.m_health_blue >=2 || gRed.m_health_red >= 2){
    animation_ongoing =0;
  }
  
  if(animation_ongoing){
    glutTimerFunc(TIMER_INTERVAL,on_timer, TIMER_ID);
  }
  glutPostRedisplay();
 
}

/* on on_keyboard funkcija u kojoj su aktivirani odgovarajuci tasteri za pomeranje igraca */
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
      
    case '8':
      if(gRed.m_rot < 90 && fire_red.fire_r == 0){
	gRed.m_rot +=0.5;
      }
      break;
    case '2':
      if(gRed.m_rot >= 0 && fire_red.fire_r == 0){
	gRed.m_rot -=0.5;
      }
      break;
    case '5':
      if(fire_red.fire_r == 0){
	fire_red.fire_r = 1;
	fire_red.fire_rot = gRed.m_rot;
	fire_red.fire_speed = gRed.m_y2;
	fire_red.m_x = gRed.m_x-0.6;
	fire_red.m_y = gRed.m_y;//-0.08;
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
      
      case 'w':
      if(gBlue.m_rot < 90){
	gBlue.m_rot +=0.5;
      }
      break;
      
      case 's':
      if(gBlue.m_rot >= 0){
	gBlue.m_rot -=0.5;
      }
      break;   
    case 'q':
      if(fire_blue.fire_b == 0){
	fire_blue.fire_b = 1;
	fire_blue.fire_rot = gBlue.m_rot;
	fire_blue.fire_speed = gBlue.m_y2;
	fire_blue.m_x = gBlue.m_x+0.6;
	fire_blue.m_y = gBlue.m_y;//+0.08;
      }
      break;

  }
}
