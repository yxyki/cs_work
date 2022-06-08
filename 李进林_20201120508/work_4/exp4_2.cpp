#include <iostream>
#include <vector>
#include "GL/glut.h"

using namespace std;

//定义用于边表ET和活动边表AET的通用类Edge
class Edge
{
public:
    int ymax;
    float x;
    float dx;
    Edge *next;
};

//定义用于表示像素点坐标的类Point
class Point
{
public:
    int x;
    int y;
    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
};
//窗体宽高
const int windowWidth = 1800;
const int windowHeight = 1200;

// Demo 箭头 顶点
vector<Point> vertices = {Point(395, 887), Point(479, 998), Point(1199, 433), Point(1101, 867), Point(1294, 715), Point(1417, 171), Point(857, 163), Point(668, 314), Point(1111, 321)};

Edge *ET[windowHeight];
//活动边表
Edge *AET;

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);
}

void polygonScan()
{
    //计算最高点的y坐标
    int maxY = 0;
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i].y > maxY)
        {
            maxY = vertices[i].y;
        }
    }
    //初始化ET和AET
    Edge *pET[windowHeight];
    for (int i = 0; i < maxY; i++)
    {
        pET[i] = new Edge();
        pET[i]->next = nullptr;
    }
    AET = new Edge();
    AET->next = nullptr;

    //清空显示窗口并设置画点颜色为灰色
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_POINTS);

    //建立边表ET
    for (int i = 0; i < vertices.size(); i++)
    {
        //取出当前点1前后相邻的共4个点，点1与点2的连线作为本次循环处理的边，另外两个点点0和点3用于计算奇点
        int x0 = vertices[(i - 1 + vertices.size()) % vertices.size()].x;
        int x1 = vertices[i].x;
        int x2 = vertices[(i + 1) % vertices.size()].x;
        int x3 = vertices[(i + 2) % vertices.size()].x;
        int y0 = vertices[(i - 1 + vertices.size()) % vertices.size()].y;
        int y1 = vertices[i].y;
        int y2 = vertices[(i + 1) % vertices.size()].y;
        int y3 = vertices[(i + 2) % vertices.size()].y;
        //水平线直接舍弃
        if (y1 == y2)
            continue;
        //分别计算下端点y坐标、上端点y坐标、下端点x坐标和斜率倒数
        int ymin = y1 > y2 ? y2 : y1;
        int ymax = y1 > y2 ? y1 : y2;
        float x = y1 > y2 ? x2 : x1;
        float dx = (x1 - x2) * 1.0f / (y1 - y2);
        //奇点特殊处理，若点2->1->0的y坐标单调递减则y1为奇点，若点1->2->3的y坐标单调递减则y2为奇点
        if (((y1 < y2) && (y1 > y0)) || ((y2 < y1) && (y2 > y3)))
        {
            ymin++;
            x += dx;
        }
        //创建新边，插入边表ET
        Edge *p = new Edge();
        p->ymax = ymax;
        p->x = x;
        p->dx = dx;
        p->next = pET[ymin]->next;
        pET[ymin]->next = p;
    }

    //扫描线从下往上扫描，y坐标每次加1
    for (int i = 0; i < maxY; i++)
    {
        //取出ET中当前扫描行的所有边并按x的递增顺序（若x相等则按dx的递增顺序）插入AET
        while (pET[i]->next)
        {
            //取出ET中当前扫描行表头位置的边
            Edge *pInsert = pET[i]->next;
            Edge *p = AET;
            //在AET中搜索合适的插入位置
            while (p->next)
            {
                if (pInsert->x > p->next->x)
                {
                    p = p->next;
                    continue;
                }
                if (pInsert->x == p->next->x && pInsert->dx > p->next->dx)
                {
                    p = p->next;
                    continue;
                }
                //找到位置
                break;
            }
            //将pInsert从ET中删除，并插入AET的当前位置
            pET[i]->next = pInsert->next;
            pInsert->next = p->next;
            p->next = pInsert;
        }

        // AET中的边两两配对并填色
        Edge *p = AET;
        while (p->next && p->next->next)
        {
            for (int x = p->next->x; x < p->next->next->x; x++)
            {
                glVertex2i(x, i);
            }
            p = p->next->next;
        }

        //删除AET中满足y=ymax的边
        p = AET;
        while (p->next)
        {
            if (p->next->ymax == i)
            {
                Edge *pDelete = p->next;
                p->next = pDelete->next;
                pDelete->next = nullptr;
                delete pDelete;
            }
            else
            {
                p = p->next;
            }
        }

        //更新AET中边的x值，进入下一循环
        p = AET;
        while (p->next)
        {
            p->next->x += p->next->dx;
            p = p->next;
        }
    }
    glEnd();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("扫描线填充算法箭头图");
    init();
    glutDisplayFunc(polygonScan);
    glutMainLoop();
    return 0;
}
