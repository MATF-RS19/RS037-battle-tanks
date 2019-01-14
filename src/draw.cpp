#include <GL/glut.h>
#include "draw.hpp"

/* iscrtavanje podloge po kojoj se krecu tenkovi */
void floor_tank::floor_draw(){   
  glPushMatrix();
    glColor3f(0,0.5,0.5);
    glBegin(GL_POLYGON);
      glVertex3f(-m_x,m_y,m_z);
      glVertex3f(-m_x,m_y,-m_z);
      glVertex3f(m_x,m_y,-m_z);
      glVertex3f(m_x,m_y,m_z);	    
    glEnd(); 
  glPopMatrix();     
}

/* iscrtavanje zida i njegovo pomeranje gore-dole */
double obstacle::obstacle_draw(double up_vector_y_cor){

  if(up){
      m_y+=up_vector_y_cor;
      if(m_y>0.5){	
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
    
    return up_vector_y_cor;
}