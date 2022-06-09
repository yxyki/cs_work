#define _STDCALL_SUPPORTED
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>
#include <stdio.h>

void wuAntiLine(int x1,int y1, int x2, int y2)
{
    int x = x1,y=y1;float k = (float)(y2 - y1)/(x2 - x1);float e = k;
    while (x <x2){
        glBegin(GL_POINTS);
        glColor3f(e * 1.0, e * 1.0 ,0);
        glVertex2i(x, y);
        glColor3f((1 - e)*1.0,(1 - e)*1.0,0);
        glVertex2i(x,y+1);
        glEnd();
        e += k;if(e>=1.0){
            e--;y++;
        }x++;
    }
}
void myDisplay(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f,0.0f,0.0f);
    glPointSize(5);
    wuAntiLine(0,0,20,30);
    wuAntiLine(0,0,30,20);
    glFlush();
}
void init(){
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-20,30,-20,50);
    glShadeModel(GL_FLAT);
}
int main(int argc, char* argv[]){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(300,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("simple");
    init();
    glutDisplayFunc(myDisplay);
    glutMainLoop();
    return 0 ;
}
