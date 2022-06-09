#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

void init(void)
{
    glClearColor (0.5, 0.8, 1.0, 0.0);  // 指定清空颜色（背景色）为蓝色
    gluOrtho2D (0.0, 300.0, 0.0, 300.0);   //指定二维坐标系中被显示的区域
}

/*
inline int round (const float a)  {
    return int (a + 0.5);
}
*/

void setPixel(int x,int y){
	glPointSize(1.0f);
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
	glFlush();
}

void lineDDA(int x0,int y0,int xEnd,int yEnd){
    int dx=xEnd-x0, dy=yEnd-y0, steps, k;
    float xIncrement,yIncrement,x=x0,y=y0;
    if(fabs(dx)>fabs(dy))
        steps=fabs(dx);
    else
        steps=fabs(dy);
    xIncrement=float(dx)/float(steps);
    yIncrement=float(dy)/float(steps);
    setPixel(round(x),round(y));
    for(k=0;k<steps;k++){
        x+=xIncrement;
        y+=yIncrement;
        setPixel(round(x),round(y));
    }
}

void myDisplay(void){
    glClear(GL_COLOR_BUFFER_BIT);// 清空显示窗口
    glColor3f(0.0,0.0,0.0);// 指定前景色（当前绘制颜色）为黑色
    lineDDA(0,230,100,20);
    glFlush();// 使绘制立即反映到屏幕上
}

int main (int argc, char** argv)
{
    glutInit (&argc, argv);                         // 初始 GLUT
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);   //设定显示模式
    glutInitWindowPosition (500, 200);   // 设定窗口位置
    glutInitWindowSize (300, 300);      // 设定窗口大小
    glutCreateWindow ("An Example OpenGL Program");
    // 用前面指定参数创建窗口，并定义窗口名称
    init( );                       // 进行一些初始化工作
    glutDisplayFunc(&myDisplay);     // 指定绘制的回调函数
    glutMainLoop ( );          // 进入无穷循环，等待事件处理
}
