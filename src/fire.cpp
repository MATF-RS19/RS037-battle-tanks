#include <GL/glut.h>
#include "fire.hpp"


void fire_red::fire(double m_x, double m_y, double m_z){
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
  

void fire_blue::fire(double m_x, double m_y, double m_z){
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