#include <GL/glut.h>
#include <stdlib.h>
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

int start_x = 0, start_y = 0;
int end_x = 0, end_y = 0;
int var = 0;

void Bresenham(int x1, int y1, int x2, int y2)
{
    glColor3fv(colors[colorIndex]);

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        glBegin(GL_POINTS);
        glVertex2i(x1, y1);
        glEnd();

        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;

        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }

        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
    glFlush();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    Bresenham(0, 0, 0, 0);

    printf("start_x: %d, start_y: %d\n", start_x, start_y);
    Bresenham(start_x, start_y, end_x, end_y);
    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    if (key >= '0' && key <= '9')
    {
        colorIndex = key - '0';
        glutPostRedisplay();
    }
}

void mouse(int button, int state, int x, int y)
{

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (!var)
        {
            start_x = end_x = x;
            start_y = end_y = glutGet(GLUT_WINDOW_HEIGHT) - y;

            var = 1;
        }

        else if (var)
        {
            end_x = x;
            end_y = glutGet(GLUT_WINDOW_HEIGHT) - y;
            glutPostRedisplay();

            var = 0;
        }
    }
}

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
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
