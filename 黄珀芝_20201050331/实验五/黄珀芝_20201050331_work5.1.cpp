#include<windows.h>
#include<iostream>
#include<gl\glut.h>


class screenPt
{
private:
	GLint x, y;
public:
	//初始化点位置为（0，0）

	screenPt()
	{
		x = y = 0;
	}
	void setCoords(GLint xCoordValue, GLint yCoordValue)
	{
		x = xCoordValue;
		y = yCoordValue;
	}
	GLint getx() const
	{
		return x;
	}
	GLint gety() const
	{
		return y;
	}
	void incrementx()//increment增加
	{
		x++;
	}
	void decrementy()//decrement减少
	{
		y--;
	}
};

void setPixel(GLint x, GLint y)
{
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POINTS);

	glVertex2i(x, y);
	std::cout << x << "," << y << std::endl;

	glEnd();
	glFlush();
}
void circleMidpoint(GLint xc, GLint yc, GLint radius)//圆心x坐标y坐标半径
{
	screenPt circPt;
	GLint p = 1 - radius;
	circPt.setCoords(0, radius);//设置圆上点的坐标

	void circlePlotPoints(GLint xc, GLint yc, screenPt circPt);

	circlePlotPoints(xc, yc, circPt);
	while (circPt.getx() < circPt.gety())
	{
		circPt.incrementx();
		if (p < 0)
			p += 2 * circPt.getx() + 1;
		else
		{
			circPt.decrementy();
			p += 2 * (circPt.getx() - circPt.gety()) + 1;
		}
		circlePlotPoints(xc, yc, circPt);
	}
}
void circlePlotPoints(GLint xc, GLint yc, screenPt circPt)
{
	setPixel(xc + circPt.getx(), yc + circPt.gety());
	setPixel(xc - circPt.getx(), yc + circPt.gety());
	setPixel(xc + circPt.getx(), yc - circPt.gety());
	setPixel(xc - circPt.getx(), yc - circPt.gety());
	setPixel(xc + circPt.gety(), yc + circPt.getx());
	setPixel(xc - circPt.gety(), yc + circPt.getx());
	setPixel(xc + circPt.gety(), yc - circPt.getx());
	setPixel(xc - circPt.gety(), yc - circPt.getx());
}


void init(void)//初始化相关的，只设置一次的放在init里
{
	//将显示窗口的背景颜色设置为白色，前三个参数分别为RGB，
	//第四个参数是alpha值，作为调和参数，alpha值用来为两个重叠对象确定结果颜色
	//alpha=0.0表示完全透明的对象；=1.0表示不透明对象
	glClearColor(1.0, 1.0, 1.0, 0.0);//背景颜色设置为白色

	//以下两个函数设置投影类型（模式）及其它观察参数

	glMatrixMode(GL_PROJECTION);//使用正投影将世界坐标系二维就行区域的内容映射到屏幕上
	gluOrtho2D(0.0, 400.0, 0.0, 300.0);//设置的是显示窗口的宽度和高度，可以不将窗口完全显示
}

void lineSegment(void)
{
	glClear(GL_COLOR_BUFFER_BIT);//显示缓存中的背景色
	glColor3f(1.0, 0.0, 0.0);//给显示的对象设置颜色

	glBegin(GL_LINES);
	//glVertex2i(100, 50);//在窗口里画一条线
	glVertex2i(50, 100);
	glEnd();

	circleMidpoint(200, 200, 50);//输入圆心，半径

	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);//初始化glut
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//设定显示窗口的缓存和颜色模型，单缓存，RGB颜色模型
	glutInitWindowPosition(50, 100);//以屏幕左上角为初始位置，初始化设置窗口显示的位置
	glutInitWindowSize(400, 300);//初始化窗口的大小

	glutCreateWindow("my first opengl window");//创建显示窗口，给定一个标题
	init();
	glutDisplayFunc(lineSegment);
	glutMainLoop();
	//  std::cout << "Hello World!\n";
}
