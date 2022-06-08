#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>

void myinit(void) //初始化
{
    glClearColor(1.0, 1.0, 1.0, 0.0); //白色背景
    glColor3f(1.0, 0.0, 0.0);         //用红色画圆
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 500.0, 0.0, 500.0); //设置窗口宽高
    glMatrixMode(GL_MODELVIEW);
}
void plot_circle_points(int xc, int yc, int x, int y) //八分法画圆
{
    glBegin(GL_POINTS);
    glVertex3f(xc + x, yc + y, 0);
    glVertex3f(xc - x, yc + y, 0);
    glVertex3f(xc + x, yc - y, 0);
    glVertex3f(xc - x, yc - y, 0);
    glVertex3f(xc + y, yc + x, 0);
    glVertex3f(xc - y, yc + x, 0);
    glVertex3f(xc + y, yc - x, 0);
    glVertex3f(xc - y, yc - x, 0);
    glEnd();
}
void drawcircle(int xc, int yc, int radius) //中点Bresenham画圆算法
{
    int x, y, p;
    x = 0;
    y = radius;
    p = 3 - 2 * radius;
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    while (x < y)
    {
        plot_circle_points(xc, yc, x, y);
        if (p < 0)
            p = p + 4 * x + 6;
        else
        {
            p = p + 4 * (x - y) + 10;
            y -= 1;
        }
        x += 1;
    }
    if (x == y)
        plot_circle_points(xc, yc, x, y);
}

void display(void) //显示函数
{
    glClear(GL_COLOR_BUFFER_BIT); //清理窗口
    glViewport(0, 0, 500, 500);
    int r;
    printf_s("请输入圆的半径：\n");
    scanf_s("%d", &r);
    drawcircle(200, 200, r);
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500); //窗口大小
    glutInitWindowPosition(0, 0);
    glutCreateWindow("中点Bresenham画圆算法"); //窗口标题
    glutDisplayFunc(display);
    myinit();
    glutMainLoop();
}
