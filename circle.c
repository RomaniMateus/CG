#include "GL/glut.h"
#include <stdio.h>

int colorIndex = 0;
float colors[10][3] = {
    {0.0, 0.0, 1.0}, // Blue
    {1.0, 0.0, 0.0}, // Red
    {0.0, 1.0, 0.0}, // Green
    {1.0, 1.0, 0.0}, // Yellow
    {0.0, 1.0, 1.0}, // Cyan
    {1.0, 0.0, 1.0}, // Magenta
    {0.5, 0.5, 0.5}, // Gray
    {0.0, 0.0, 0.0}, // Black
    {1.0, 1.0, 1.0}, // White
    {0.0, 0.0, 0.5}  // Dark Blue
};

int X = 400, Y = 300;

void mouse(int button, int state, int x, int y)
{

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        X = x;
        Y = glutGet(GLUT_WINDOW_HEIGHT) - y;
    }
    glutPostRedisplay();
}

void putpixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}
void drawCircle(int xc, int yc, int x, int y)
{
    putpixel(xc + x, yc + y);
    putpixel(xc - x, yc + y);
    putpixel(xc + x, yc - y);
    putpixel(xc - x, yc - y);
    putpixel(xc + y, yc + x);
    putpixel(xc - y, yc + x);
    putpixel(xc + y, yc - x);
    putpixel(xc - y, yc - x);
}

void circleBresenham(int xc, int yc, int r)
{
    int x = 0, y = r;
    int d = 1 - r;

    glColor3fv(colors[colorIndex]);
    drawCircle(xc, yc, x, y);
    while (y >= x)
    {
        x++;

        if (d > 0)
        {
            y--;
            d = d + 2 * (x - y) + 1;
        }
        else
            d = d + 2 * x + 1;
        drawCircle(xc, yc, x, y);
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    circleBresenham(X, Y, 30); // function call
    glFlush();
}
// Driver code
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Line Drawer");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
