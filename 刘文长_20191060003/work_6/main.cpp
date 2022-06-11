
#define _STDCALL_SUPPORTED
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#define PI 3.1415926535

//初始化
void init(void) {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	gluOrtho2D(-400, 400.0, -400, 400.0);
}
//平移变换
void translation(int *x,int *y,int xdistance,int ydistance){
    int now[1][3]={*x,*y,1};
    int by[3][3]={1,0,0,
                  0,1,0,
                  xdistance,ydistance,1};
    int after[1][3]={0};
    int i,j,k;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
              after[0][i] += now[0][j]*by[j][i];
        }
    }
    *x=after[0][0];
    *y=after[0][1];
}
//比例变换
void proportion(int *x,int *y,float xmultiple,float ymultiple){
    int now[1][3]={*x,*y,1};
    float by[3][3]={xmultiple,0,0,
                  0,ymultiple,0,
                  0,0,1};
    float after[1][3]={0};
    int i,j,k;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
              after[0][i] += now[0][j]*by[j][i];
        }
    }
    *x=after[0][0];
    *y=after[0][1];
}
//旋转变换
void myrotate(int *x,int *y,float degree){
    int now[1][3]={*x,*y,1};
    float by[3][3]={cos(degree),sin(degree),0,
                  -sin(degree),cos(degree),0,
                  0,0,1};
    float after[1][3]={0};
    int i,j,k;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
              after[0][i] += now[0][j]*by[j][i];
        }
    }
    *x=after[0][0];
    *y=after[0][1];
}

void setPixel(int x,int y){
	glPointSize(1.0f);
	glBegin(GL_POINTS);
        //translation(&x,&y,200,100);
        //proportion(&x,&y,0.4,0.4);
        myrotate(&x,&y,PI/4);
		glVertex2i(x,y);
	glEnd();
	glFlush();
}
void myBreseham(int x0,int y0,int xEnd,int yEnd){
    int i,x,y,dx,dy;
    if(xEnd>=x0){
        dx=xEnd-x0;
        dy=yEnd-y0;
        x=x0;y=y0;
    }
    else{
        dx=x0-xEnd;
        dy=y0-yEnd;
        x=xEnd;y=yEnd;
    }
    float k=float(dy)/float(dx);
    if(k>=0&&k<1){
        float d=0.5-k;
        for(i=0;i<fabs(dx);i++){
            if(d<0){
            x=x+1;
            y=y+1;
            d=d+1-k;
            setPixel(x,y);
            }
            else{
            x=x+1;
            d=d-k;
            setPixel(x,y);
            }
        }
    }
   if(k>=1){
        float d=1-0.5*k;
        for(i=0;i<fabs(dy);i++){
            if(d<0){
                y=y+1;
                d=d+1;
                setPixel(x,y);
            }
            else{
                x=x+1;
                y=y+1;
                d=d+1-k;
                setPixel(x,y);
            }
        }
    }
    if(k>-1&&k<0){
        float d=-0.5-k;
        for(i=0;i<fabs(dx);i++){
            if(d<0){
                x=x+1;
                d=d-k;
                setPixel(x,y);
            }
            else{
                x=x+1;
                y=y-1;
                d=d-1-k;
                setPixel(x,y);
            }
        }
    }
    if(k<=-1){
        float d=-1-0.5*k;
        for(i=0;i<fabs(dy);i++){
            if(d<0){
                x=x+1;
                y=y-1;
                d=d-1-k;
                setPixel(x,y);
            }
            else{
                y=y-1;
                d=d-1;
                setPixel(x,y);
            }
        }
    }
}


void myDisplay(void){
    glClear(GL_COLOR_BUFFER_BIT);// 清空显示窗口
    glColor3f(0.0,0.0,0.0);// 指定前景色（当前绘制颜色）为黑色
    myBreseham(-200,60,300,-90);
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
    glutDisplayFunc(myDisplay);     // 指定绘制的回调函数
    glutMainLoop ( );          // 进入无穷循环，等待事件处理
}
