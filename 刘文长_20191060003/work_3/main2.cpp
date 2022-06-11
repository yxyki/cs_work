#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

void init(void)
{
    glClearColor (0.5, 1.0, 1.0, 0.0);  // 指定清空颜色（背景色）为白色
    gluOrtho2D (-150.0, 150.0, -150.0, 150.0);   //指定二维坐标系中被显示的区域
}

void setPixel(int x,int y){
	glPointSize(1.0f);
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
	glFlush();
}

void myBresehamPro(int x0,int y0,int xEnd,int yEnd){
    int dx=xEnd-x0,dy=yEnd-y0;
    int x=x0,y=y0;
    int e=-dx;
    setPixel(x,y);
    for(x;x<xEnd;x++){
        e=e+2*dy;
        if(e>0){
        x+=1;
        y+=1;
        e-=2*dx;
        setPixel(x,y);
        }
        else{
        x+=1;
        setPixel(x,y);
        }
    }
}

void myDisplay(void){
    glClear(GL_COLOR_BUFFER_BIT);// 清空显示窗口
    glColor3f(0.0,0.0,0.0);// 指定前景色（当前绘制颜色）为黑色
    myBresehamPro(0,0,100,30);
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
