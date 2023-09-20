from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *


def mouse(button, state, x, y):
    print("clicked at: ", x, y)

    if button == GLUT_LEFT_BUTTON and state == GLUT_DOWN:
        X = x
        Y = glutGet(GLUT_WINDOW_HEIGHT) - y

        glutPostRedisplay()

    print("X: ", X, "Y: ", Y)


def bresenham_circle(x_center, y_center, radius):
    x = 0
    y = radius
    p_k = 1 - radius
    while x <= y:
        draw_circle(x_center, y_center, x, y)
        x += 1
        if p_k < 0:
            p_k = p_k + 2 * x + 1
        else:
            y -= 1
            p_k = p_k + 2 * x + 1 - 2 * y


def draw_circle(x_center, y_center, x, y):
    glBegin(GL_POINTS)
    glVertex2i(x_center + x, y_center + y)
    glVertex2i(x_center + x, y_center - y)
    glVertex2i(x_center - x, y_center + y)
    glVertex2i(x_center - x, y_center - y)
    glVertex2i(x_center + y, y_center + x)
    glVertex2i(x_center + y, y_center - x)
    glVertex2i(x_center - y, y_center + x)
    glVertex2i(x_center - y, y_center - x)
    glEnd()


def main():
    X = 0
    Y = 0
    glutInit()
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB)
    glutInitWindowSize(500, 500)
    glutInitWindowPosition(0, 0)
    glutCreateWindow("Bresenham Circle")
    glClearColor(1.0, 1.0, 1.0, 1.0)
    gluOrtho2D(-250.0, 250.0, -250.0, 250.0)
    glutMouseFunc(mouse)
    glutDisplayFunc(lambda: bresenham_circle(X, Y, 100))
    glutMainLoop()


if __name__ == "__main__":
    main()
