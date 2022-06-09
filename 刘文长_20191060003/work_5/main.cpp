#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

void init(void)
{
    glClearColor (0.5, 0.3, 0.5, 0.0);  // 指定清空颜色（背景色）为白色
    gluOrtho2D (-150.0, 150.0, -150.0, 150.0);   //指定二维坐标系中被显示的区域
}

void putpixel(int x,int y)
{
    glPointSize(1.0f);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
    glFlush();
}

void circlePoint(int x,  int y)
{
    putpixel(x,y);
    putpixel(y,x);
    putpixel(-y,x);
    putpixel(-x,y);
    putpixel(-x,-y);
    putpixel(-y,-x);
    putpixel(y,-x);
    putpixel(x,-y);
}

void MidBresenhamcircle(int r)
{
    int x, y, d;
    x=0;
    y=r;
    d=1.25-r;                  /*赋初值*/
    while(x<y)                         /*循环退出条件*/
    {
        circlePoint(x,y);              /*绘制一个点*/
        if (d<0) d+=2*x+3;         /*判别式更新*/
        else
        {
            d+=2*(x-y)+5;
            y--;                        /*y方向上走一步*/
        }
        x++;                           /*x方向上走一步*/
    }                                     /*while循环结束*/
}

void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);// 清空显示窗口
    glColor3f(0.0,0.0,0.0);// 指定前景色（当前绘制颜色）为黑色
    MidBresenhamcircle(50);
    glFlush();// 使绘制立即反映到屏幕上
}

int main (int argc, char** argv)
{
    glutInit (&argc, argv);                         // 初始 GLUT.
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);   //设定显示模式
    glutInitWindowPosition (500, 200);   // 设定窗口位置
    glutInitWindowSize (300, 300);      // 设定窗口大小
    glutCreateWindow ("An Example OpenGL Program");
    // 用前面指定参数创建窗口，并定义窗口名称
    init( );                       // 进行一些初始化工作
    glutDisplayFunc(&myDisplay);     // 指定绘制的回调函数
    glutMainLoop ( );          // 进入无穷循环，等待事件处理
}
