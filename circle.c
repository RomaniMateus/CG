#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

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

int x1, centerY, x2, clickY;

void display(); // Forward declaration

void circleBresenham(int, int, int, int);
void mouse(int, int, int, int);
void keyboard(unsigned char, int, int);

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Circle Drawer");
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

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    circleBresenham(x1, centerY, x2, clickY);
    glFlush();
}

void circleBresenham(int x1, int centerY, int x2, int clickY)
{
    int r = sqrt((x2 - x1) * (x2 - x1) + (clickY - centerY) * (clickY - centerY)); // Calculate the radius

    int x = 0, y = r;
    int d = 3 - 2 * r;

    glBegin(GL_POINTS); // Start drawing points

    while (x <= y)
    {
        // Draw points using symmetry
        glVertex2i(x1 + x, centerY + y);
        glVertex2i(x1 + y, centerY + x);
        glVertex2i(x1 - x, centerY + y);
        glVertex2i(x1 - y, centerY + x);
        glVertex2i(x1 + x, centerY - y);
        glVertex2i(x1 + y, centerY - x);
        glVertex2i(x1 - x, centerY - y);
        glVertex2i(x1 - y, centerY - x);

        if (d < 0)
            d += 4 * x + 6;
        else
        {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }

    glEnd();   // End drawing points
    glFlush(); // Flush the OpenGL pipeline to update the display
}

void mouse(int button, int state, int mouseX, int mouseY)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (x1 == 0 && centerY == 0) // If it's the first click, set the center coordinates
        {
            x1 = mouseX;
            centerY = 600 - mouseY; // Invert Y-coordinate to match OpenGL's coordinate system
        }
        else // If it's the second click, set the second point and calculate the radius
        {
            x2 = mouseX;
            clickY = 600 - mouseY;

            int radius = sqrt((x2 - x1) * (x2 - x1) + (clickY - centerY) * (clickY - centerY));

            glClear(GL_COLOR_BUFFER_BIT);
            glColor3fv(colors[colorIndex]);
            glutSwapBuffers();

            x1 = centerY = x2 = clickY = 0; // Reset coordinates for the next circle
        }
    }
}

void keyboard(unsigned char key, int x, int y)
{
    if (key >= '0' && key <= '9')
    {
        colorIndex = key - '0';
        glutPostRedisplay();
    }
}
