#include <iostream>
#include <gl/glut.h>
#include <gl/glu.h>
#include <math.h>
#include<stdlib.h>
#define screen_ht 640
#define screen_wt 480
using namespace std;
GLfloat red=.9;
GLfloat green=.9;
GLfloat blue=.9;
GLfloat thickness;
struct Point {
	GLint x;
	GLint y;
};

Point p1, p2;

bool pattern(int style, int counter){
        if(style == 1){
            if(counter%2 == 0){
                return false;
            }
            else{
                return true;
            }
        }
        else
        if(style == 2){
            if(counter%4 == 0 || counter%5 == 0 || counter%6 == 0){
                return false;
            }
            else{
                return true;
            }
        }
        else{
            return true;
        }
}

void draw_line(Point p1, Point p2) {
	GLfloat dx = p2.x - p1.x;
	GLfloat dy = p2.y - p1.y;

	GLfloat x1 = p1.x;
	GLfloat y1 = p1.y;

	GLfloat e = 0;
    int style;
    int counter = 1;
    cout<<"Please enter pattern style\nPress 1 for dotted line\nPress 2 for dashed line\nPress anything for normal or solid line\n";
    cin>>style;

	if(abs(dx) > abs(dy)) {
		e = abs(dx);
	} else {
		e = abs(dy);
	}

	GLfloat xInc = dx/e;
	GLfloat yInc = dy/e;

    //glClear(GL_COLOR_BUFFER_BIT);
	glColor3f( red,green,blue);
	for(float i = 1; i <= e; i++) {
	    if(pattern(style, counter)){
            glBegin(GL_POINTS);
            glVertex2i(x1, y1);
            glEnd();
	    }
		x1 += xInc;
		y1 += yInc;
		counter++;
	}
	glFlush();
}

void myMouseFunc(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		p1.x = x-640/2;
		p1.y = 480/2 - y;
	}
	else if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
		p2.x = x-640/2;
		p2.y = 480/2 - y;
		draw_line(p1, p2);
	}
}

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);


	glPointSize(thickness);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-screen_ht/2, screen_ht/2, -screen_wt/2,screen_wt/2);
}
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_LINES);
	  glVertex2i(0,-screen_ht/2);
	  glVertex2i(0,screen_ht/2);
	glEnd();
	glBegin(GL_LINES);
	  glVertex2i(-screen_wt/2,0);
	  glVertex2i(screen_wt/2,0);
    glEnd();
    glFlush();}

int main(int argc, char **argv) {
    cout<<endl<<"Enter the color intensities of line in RED,GREEN,BLUE order-"<<endl;
    cin>>red>>green>>blue;
    cout<<"enter the thickness"<<endl;
    cin>>thickness;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Simple DDA");
	glutDisplayFunc(display);
	glutMouseFunc(myMouseFunc);
	init();
	glutMainLoop();

	return 0;
}
