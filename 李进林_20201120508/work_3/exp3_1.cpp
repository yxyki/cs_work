#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void setPixel(int x, int y)
{
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}
void lineBres(int x0, int y0, int xEnd, int yEnd)
{
    int dx = fabs(xEnd - x0), dy = fabs(yEnd - y0);
    int p = 2 * dy - dx;
    int twoDy = 2 * dy, twoDyMinusDx = 2 * (dy - dx);
    int x, y;
    if (x0 > xEnd)
    {
        x = xEnd;
        y = yEnd;
        xEnd = x0;
    }
    else
    {
        x = x0;
        y = y0;
    }
    setPixel(x, y);
    while (x < xEnd)
    {
        x++;
        if (p < 0)
            p += twoDy;
        else
        {
            y++;
            p += twoDyMinusDx;
        }
        setPixel(x, y);
    }
}

void init(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f); //设置显示窗口颜色为白色
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0f, 200.0f, 0.0f, 150.0f); //设置规划参数
}

void myDisplay()
{
    int x0, y0, xEnd, yEnd;
    printf_s("请输入点坐标（用空格作为分隔符，起点在前，终点在后）：");
    scanf_s("%d %d %d %d", &x0, &y0, &xEnd, &yEnd);
    lineBres(x0, y0, xEnd, yEnd);
}

void main(int argc, char **argv)
{
    glutInit(&argc, argv);                       //初始化
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //设置显示模式
    glutInitWindowPosition(50, 100);             //设置窗口位置
    glutInitWindowSize(400, 300);                //设置窗口长宽
    glutCreateWindow("Bresenham算法");           //设置标题
    init();
    glutDisplayFunc(&myDisplay);
    glutMainLoop();
}
