#include <windows.h>
#include <GL/glut.h>
void init(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f); //设置显示窗口颜色为白色
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0f, 200.0f, 0.0f, 150.0f); //设置规划参数
}
void lineSegment(void)
{
    glClear(GL_COLOR_BUFFER_BIT); //清除展示窗口
    glColor3f(0.0f, 0.4f, 0.2f);  //将线段颜色设置为绿色
    glBegin(GL_LINES);
    glVertex2i(180, 15); //指定线段几何形状
    glVertex2i(10, 145);
    glEnd();
    glFlush(); //尽可能快地处理所有OPenGL例程
}
void main(int argc, char **argv)
{
    glutInit(&argc, argv);                       //初始化
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //设置显示模式
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(400, 300);                  //设置窗口长宽
    glutCreateWindow("An Example OpenGL Program"); //设置标题
    init();
    glutDisplayFunc(lineSegment);
    glutMainLoop();
}
