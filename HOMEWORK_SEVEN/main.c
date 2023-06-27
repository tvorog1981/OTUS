#include<GL/glut.h>
#include<GL/gl.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<strings.h>
#include<string.h>
const GLint Scale  = 25;
GLint number = 4;
GLint dir;
const GLint  N = 30;
const GLint  M = 20;
GLint count = 0;
GLint w = N * Scale;
GLint h = M * Scale;

struct {
  GLint x, y;
}snake[100];


struct{
  GLint x,y;
}fruit[10];




GLvoid new(GLint  f){
    fruit[f].x = rand() % N;
    fruit[f].y = rand() % M;
}


GLvoid DrawApple(GLint f){
  glColor3f(0.0,0.0,1.0);
  glRectf(fruit[f].x *Scale, fruit[f].y *Scale, (fruit[f].x +1)*Scale,(fruit[f].y +1)*Scale);

}

GLvoid initialization(GLint * argc ,char ** argv);
GLvoid DrawField();
GLvoid display();
GLvoid DrawSnake();
GLvoid timer(int);
GLvoid tick();
GLvoid eventKey(GLint, GLint,GLint);

GLint main(int argc ,char ** argv){
  
  initialization(&argc,argv);

  return EXIT_SUCCESS;
}







GLvoid initialization(GLint * argc ,char ** argv){
  srand(time(0));
  for(int i = 0 ; i < 10;i++){
    new(i);
  }
    snake[0].x = 10;
    snake[0].y = 10;

  glutInit(argc,argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(w,h);
  glutCreateWindow("SNAKE");
  glClearColor(1.0,1.0,0.6,1.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0,w,0,h);
  glutDisplayFunc(display);
  glutSpecialFunc(eventKey);
  glutTimerFunc(50,timer,0);
  glutMainLoop();
}

GLvoid display(){ 
  glClear(GL_COLOR_BUFFER_BIT);

  DrawField();
  DrawSnake();

  for(GLint i = 0 ; i< 10;i++){
    DrawApple(i);
  }
  glFlush();
  glutSwapBuffers();
}

GLvoid DrawSnake(){
  glColor3f(0.0,0.0,1.0);
  for(GLint i = 0 ; i < number; i++){
    glRectf(snake[i].x * Scale, snake[i].y * Scale, (snake[i].x + 0.9)*Scale, (snake[i].y + 0.9)* Scale);
  }

}

GLvoid DrawField(){
  glColor3f(0.0,0.7,0.0);
  glBegin(GL_LINES);
  for(GLint i = 0 ; i < w; i += Scale){
    glVertex2f(i,0);
    glVertex2f(i,h);
  }
  for(GLint j = 0 ; j < h; j += Scale){
    glVertex2f(0,j);
    glVertex2f(w,j);
  }
  glEnd();

}

GLvoid tick(){
  if(dir == 0) snake[0].y+=1;
    if(dir == 1) snake[0].x-=1;
      if(dir == 2) snake[0].x+=1;
        if(dir == 3) snake[0].y-=1;
	
  for(GLint i = number; i > 0 ; --i){
    snake[i].x=snake[i-1].x;
    snake[i].y=snake[i-1].y;
  }

  for(GLint j = 0 ; j < number;j++){
    if(snake[0].x == fruit[j].x && snake[0].y ==fruit[j].y){
      number++;
      char * score ="Score: ";
      ++count;
      char buff_score[100];
      bzero(buff_score,100);
      sprintf(buff_score, "%d", count);
      char buff[100];
      bzero(buff,100);
      strcpy(buff ,score);
      strncat(buff,buff_score,50);
      glutSetWindowTitle(buff);
      new(j);
    }
  }
  //border
  if(snake[0].x > N){ dir = 1;} if(snake[0].x < 0){ dir = 2;}
  if(snake[0].y > M) {dir = 3;} if(snake[0].y < 0){ dir = 0;}

  //tail
  //  for(GLint i = 2 ; i< number;i++){
  // if(snake[0].x == snake[i].x && snake[0].y == snake[i].y){ number = i;}
  // }

  
}
GLvoid timer(int value){
  //remove warning
  if (value == 0){}
  display();
  tick();
  glutTimerFunc(50,timer,0);

}
GLvoid eventKey(GLint key, GLint a,GLint b){
  //remove warning
  if(a != 111 && b !=222){}
  switch(key){
  case 101: dir =0 ;break;
    case 102: dir =2 ;break;
      case 100: dir =1 ;break;
	case 103: dir = 3 ;break;
  }
}
