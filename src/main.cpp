#include <GL/glut.h>
#include "SOIL.h"
#include <iostream>

#include "gamers.hpp"
#include "fire.hpp"
#include "draw.hpp"

#define TIMER_ID 0
#define TIMER_INTERVAL 100
#define FILENAME "universe.bmp"
#define POMERAJ 0.02

void on_display(void);
void on_reshape(int width, int height);
void on_keyboard(unsigned char key, int x, int y);
void on_timer(int value);

int width_window = 700;
int height_window = 500;
int animation_ongoing = 0;
GLuint slika_pozadine;
int up3 = 1; 
int up4 = 1;
int win = 0;
int bonus_helt_r = 1;
int bonus_helt_b = 1;
double up_vector_y_cor=0;

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

//  initialize();
    glClearColor(0,0,0,0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  /* postavljanje slike */  
    slika_pozadine=SOIL_load_OGL_texture("deixis_darksky.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  if(slika_pozadine==0){
   std::cout << "Nije ucitana slika" << std::endl;   
  } 
  glEnable(GL_DEPTH_TEST);
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
   
   
   /* iscrtavanje podloge */
   floor_tank.floor_draw();

  /* iscrtavanje helta za oba igraca */ 
   gRed.health();
   gBlue.health();

   /* iscrtavanje sivog zida koji se pomera */
   up_vector_y_cor = obstacle.obstacle_draw(up_vector_y_cor);
   
   /* iscrtavanje oba igraca */
   gRed.gamer1_draw();
   gBlue.gamer2_draw();
   
   /* provera za iscrtavanje bonus helta, kada neki od igraca dodje do toga da ima helt mevi od 1.5 a sa 2 
    *se zavrsava igrica, jednom samo ima sansu da vrati helt na pocetak */
   if (gRed.m_health_red >1 && bonus_helt_r == 1){
     gRed.help(0.4);  
     if(gRed.m_x >= 0.69 && gRed.m_x <=0.75){
       gRed.m_health_red =0;
       bonus_helt_r = 0;
    }
  } 
      if (gBlue.m_health_blue >1 && bonus_helt_b == 1){
     gBlue.help(0.4);  
     if(gBlue.m_x <= -0.69 && gBlue.m_x >=-0.75){
       gBlue.m_health_blue =0;
       bonus_helt_b = 0;
    }
  } 
   /* iscrtavanje meraca brzine */
    up_vector_y_cor = gBlue.speed(up_vector_y_cor); 
    gBlue.blue_up = gRed.red_up;
    up_vector_y_cor = gRed.speed(up_vector_y_cor);
    gBlue.blue_up = gRed.red_up;
   /* provera za ispis 'start_game' i 'game_over' i ispisivanje kada sta treba */
   if((animation_ongoing == 0) && 
     (gBlue.m_health_blue == 0) &&
     (gRed.m_health_red == 0)){
     /* ispis teksta koji se prikazuje na samom pocetku kako bi se aktivirala igrica
      * pritiskom na g i pokrenulo kretanje zida i meraca brzine */
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
  }else{
    if(animation_ongoing == 0){
      /* ispis teksta koji se poziva kada neki od igraca potrosi helt */
        char tekst1[256], *p1;

	if(win == 2){
	  sprintf(tekst1, "Game over, winner is BLUE!");  
	}else{
	  sprintf(tekst1, "Game over, winner iz RED!");
	}
	      
	glPushMatrix();
	  glRotatef(90,1,0,0);
	  glColor3f(1,1,1);
	  glRasterPos3f(-0.5,0,-0.5);
	  for(p1 = tekst1; *p1!= '\0'; p1++){
	    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p1);
	  }
    }
  }
   
   /* provera da li je crveni tenk ispalio metak */
   if(fire_red.fire_r){ 
    glPushMatrix();
      glTranslatef(fire_red.m_x,fire_red.m_y,0);
      fire_red.fire(gRed.m_x, gRed.m_y, gRed.m_z);
    
      /* provera da li metak urada u zid ako i da li je pogodio igraca */
      if((fire_red.m_y < (obstacle.m_y+0.33))&& (fire_red.m_y > (obstacle.m_y-0.33)) 
      && (fire_red.m_x < obstacle.m_x+0.2) && (fire_red.m_x > obstacle.m_x-0.2)){
	fire_red.m_y = 10;
	fire_red.fire_r = 0;
      }
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
    if(gRed.m_health_red >=2)
      win = 2;
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
