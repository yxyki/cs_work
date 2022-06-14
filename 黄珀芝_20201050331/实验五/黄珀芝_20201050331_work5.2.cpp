#include <windows.h>
#include <GL/glut.h>
#include <cstdio>
#include <cmath>
#include <string.h>
#include <fstream>
#include <iostream>

using namespace std;

typedef float Color[3];
int ncount=0;
int numX[100],numY[100];

void init(void)
{
    glClearColor(0,0,0,0.0);//清除当前所有颜色
    glMatrixMode(GL_PROJECTION);//投影模型
    gluOrtho2D(0,500,0,500);//二维投影，参数越大，直线越小
}

//获取一点像素的颜色
void GetPixel(GLint x, GLint y,Color color)
{
    glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,color);
}

//画像素点
void SetPixel(GLint x,  GLint y)
{
    glBegin(GL_POINTS);
        glVertex2i(x, y);
    glEnd();
}

//比较颜色是否相等
bool compare(Color c1,Color c2)
{
   return (fabs(c1[0]-c2[0])<0.001 &&fabs(c1[1]-c2[1])<0.001 && fabs(c1[2]-c2[2])<0.001) ;
}

void FloodFill4(int x,int y,Color oldcolor,Color newcolor)
{
    Color color;
    GetPixel(x,y,color);
    if(compare(color,oldcolor))
    {
        SetPixel(x,y);
        FloodFill4(x,y+1,oldcolor,newcolor);
        FloodFill4(x,y-1,oldcolor,newcolor);
        FloodFill4(x-1,y,oldcolor,newcolor);
        FloodFill4(x+1,y,oldcolor,newcolor);
    }
}

//绘制填充多边形
void drawPolygon()
{
    int i;
    glBegin(GL_POLYGON);
        for(i=0;i<ncount;i++)
        {
            cout<<numX[i]<<' '<<numY[i]<<endl;
            glVertex2i(numX[i],numY[i]);
        }
       glVertex2i(200,100);
      glVertex2i(200,200);
       glVertex2i(200,200);
       glVertex2i(100,200);
    glEnd();
}

void display()
{
    /*
    *  glClearColor表示清除颜色设为黑色
    *  glclear表示实际完成了把整个窗口清除为黑色的任务
    */
    Color oldcolor={1.0,0.0,0.0};//红色
    Color newcolor={0.0,1.0,0.0};//绿色

    glClear(GL_COLOR_BUFFER_BIT);//清除缓冲器颜色
    glColor3fv(oldcolor);//设置画笔颜色
    drawPolygon();
//    glPointSize(5);//设置点像素大小
    glColor3fv(newcolor);//设置画笔颜色
    FloodFill4(150,150,oldcolor,newcolor);
    glFlush();//刷新缓冲
}

int main(int argc,char** argv)
{
    string filename,oneline;
    char charline[10];
    char *p;

    //cout << "please enter" << endl;
    //cin >> filename;
    ifstream infile(filename.c_str());//读取文件

    while(getline(infile,oneline))//读取一行
    {
        strcpy(charline,oneline.c_str());//string转换为char[]
        p=strtok(charline,",");//以,分割字符串
        numX[ncount]=atoi(p);//字符串转换整数
        p=strtok(NULL,",");//strtok是静态函数
        numY[ncount]=atoi(p);
        ncount++;
//        cout<<numX[0]<<' '<<numY[0]<<endl;
    }

    glutInit(&argc,argv);//从main函数传递参数
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);//设置显示模式，单缓冲，RGB
    glutInitWindowPosition(0,0);//窗口位置
    glutInitWindowSize(500,500);//窗口大小
    glutCreateWindow("FloodFill4");//窗口标题

    init();//自定义初始化函数
    glutDisplayFunc(display); //渲染函数
    glutMainLoop(); //循环消息机制

    return 0;
}


/*
 *测试数据
 *100,100
 *200,100
 *200,200
 *100,300
 *50,200
*/


