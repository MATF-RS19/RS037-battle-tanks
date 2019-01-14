#include <GL/glut.h>
#include "gamers.hpp"


/******************
    CRVENI IGRAC
 ******************/

void gamer1::gamer1_draw(void){
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
void gamer1::health(){
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
double gamer1::speed(double up_vector_y_cor){
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
	/* menjanje m_y2 koordinate za translaciju belog pravougaonika za merenje brzine metka */
   if(red_up){
     m_y2+=up_vector_y_cor;
     if(m_y2>0.13){	
      red_up=0;
     }
   }
   else{
     m_y2-=up_vector_y_cor;
     if(m_y2<=-0.13){
      red_up=1;
     }
   }
    /* iscrtavanje belog pravougaonika za brzinu i njegova translacija za m_y2 */
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
  
 return up_vector_y_cor;
}


/******************
    PLAVI IGRAC
 ******************/

void gamer2::gamer2_draw(void){
 
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
void gamer2::health(){
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
double gamer2::speed(double up_vector_y_cor){
   /*skala crveno zelena za brzinu po kojoj se krece beli pravouganoik koji ustvari odredjuje brzinu metka */
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
  
  /* menjanje m_y2 koordinate za translaciju belog pravougaonika za merenje brzine metka */
  if(blue_up){
    m_y2-=up_vector_y_cor;
    if(m_y2>0.13){	
      blue_up=0;
    }
   }
  else{
    m_y2+=up_vector_y_cor;
    if(m_y2<=-0.13){
      blue_up=1;
    }
  } 
  
  /* iscrtavanje belog pravougaonika za brzinu i njegova translacija za m_y2 */
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
  
  return up_vector_y_cor;
}
  