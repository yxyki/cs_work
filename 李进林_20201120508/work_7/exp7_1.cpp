#include <GL/glut.h>
GLsizei winWidth = 400, winHeight = 300;
void init(void)
{
    glClearColor(0.0, 0.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 200, 0.0, 150.0);
}
void displayFcn(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(3.0);
}
void winReshapeFcn(GLint newWidth, GLint newHeight)
{
    glViewport(0, 0, newWidth, newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, GLdouble(newWidth), 0.0, GLdouble(newHeight));
    winWidth = newWidth;
    winHeight = newHeight;
}
void plotPoint(GLint x, GLint y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}
void mouseptPlot(GLint button, GLint action, GLint x, GLint y)
{
    if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
    {
        plotPoint(x, y);
    }
    glFlush();
}
void main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("Mouse Point Plotter");
    init();
    glutDisplayFunc(displayFcn);
    glutReshapeFunc(winReshapeFcn);
    glutMouseFunc(mouseptPlot);
    glutMainLoop();
}
GLUT鼠标函数示例二
#include <GL/glut.h>
GLsizei winWidth = 400, winHeight = 300;
GLint endPtCtr = 0;
class scrpt
{
public:
    GLint x, y;
};
void init(void)
{
    glClearColor(0.0, 0.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 200, 0.0, 150.0);
}
void displayFcn(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
}
void winReshapeFcn(GLint newWidth, GLint newHeight)
{
    glViewport(0, 0, newWidth, newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, GLdouble(newWidth), 0.0, GLdouble(newHeight));
    winWidth = newWidth;
    winHeight = newHeight;
}
void drawLineSegment(scrpt s1, scrpt s2)
{
    glBegin(GL_LINES);
    glVertex2i(s1.x, s1.y);
    glVertex2i(s2.x, s2.y);
    glEnd();
}
void polyline(GLint button, GLint action, GLint xMouse, GLint yMouse)
{
    static scrpt endpt1, endpt2;
    if (endPtCtr == 0)
    {
        if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
        {
            endPtCtr = 1;
            endpt1.x = xMouse;
            endpt1.y = winHeight - yMouse;
        }
        else if (button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN)
            exit(0);
    }
    else if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
    {
        endpt2.x = xMouse;
        endpt2.y = yMouse;
        drawLineSegment(endpt1, endpt2);
        endpt1 = endpt2;
    }
    else if (button == GLUT_RIGHT_BUTTON)
        exit(0);
    glFlush();
}

void main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("Drawing   Interactive polyline");
    init();
    glutDisplayFunc(displayFcn);
    glutMouseFunc(polyline);
    glutMainLoop();
}

（2）opengl 反走样
#include <GL/glut.h>
#include <stdio.h>

    static float rotAngle = 0.;

void init(void)
{
    GLfloat values[2];
    glGetFloatv(GL_LINE_WIDTH_GRANULARITY, values);
    printf("GL_LINE_WIDTH_GRANULARITY value is %3.1f\n", values[0]);

    glGetFloatv(GL_LINE_WIDTH_RANGE, values);
    printf("GL_LINE_WIDTH_RANGE values are %3.1f %3.1f\n", values[0], values[1]);

    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);

    glLineWidth(1.5);

    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 1.0, 0.0);
    glPushMatrix();
    glRotatef(-rotAngle, 0.0, 0.0, 0.1);
    glBegin(GL_LINES);
    glVertex2f(-0.5, 0.5);
    glVertex2f(0.5, -0.5);
    glEnd();
    glPopMatrix();

    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glRotatef(rotAngle, 0.0, 0.0, 0.1);
    glBegin(GL_LINES);
    glVertex2f(0.5, 0.5);
    glVertex2f(-0.5, -0.5);
    glEnd();
    glPopMatrix();

    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        gluOrtho2D(-1.0, 1.0, -1.0 * (GLfloat)h / (GLfloat)w, 1.0 * (GLfloat)h / (GLfloat)w);
    else
        gluOrtho2D(-1.0 * (GLfloat)w / (GLfloat)h, 1.0 * (GLfloat)w / (GLfloat)h, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'r':
    case 'R':
        rotAngle += 20.;
        if (rotAngle >= 360.0)
            rotAngle = 0.0;
        glutPostRedisplay();
        break;
    case 27:
        exit(0);
        break;
    default:
        break;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(200, 200);
    glutCreateWindow(argv[0]);
    init();
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
