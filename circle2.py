from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *


def putpixel(x, y):
    glBegin(GL_POINTS)
    glVertex2i(x, y)
    glEnd()


def draw_circle(xc, yc, x, y):
    putpixel(xc + x, yc + y)
    putpixel(xc - x, yc + y)
    putpixel(xc + x, yc - y)
    putpixel(xc - x, yc - y)
    putpixel(xc + y, yc + x)
    putpixel(xc - y, yc + x)
    putpixel(xc + y, yc - x)
    putpixel(xc - y, yc - x)


def circle_bres(xc, yc, r):
    x = 0
    y = r
    d = 3 - 2 * r
    draw_circle(xc, yc, x, y)
    while y >= x:
        x += 1
        if d > 0:
            y -= 1
            d = d + 4 * (x - y) + 10
        else:
            d = d + 4 * x + 6
        draw_circle(xc, yc, x, y)


def main():
    # glutInit()
    # glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB)
    # glutInitWindowSize(500, 500)
    # glutInitWindowPosition(0, 0)
    # glutCreateWindow("Bresenham Circle")
    # glClearColor(1.0, 1.0, 1.0, 1.0)
    # gluOrtho2D(-250.0, 250.0, -250.0, 250.0)
    # glutDisplayFunc(lambda: circle_bres(0, 0, 100))
    # glutMainLoop()

    glutInit()
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB)
    glutInitWindowSize(800, 600)
    glutCreateWindow("Line Drawer")
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluOrtho2D(0, 800, 0, 600)
    glClearColor(1.0, 1.0, 1.0, 1.0)
    glutMainLoop()


if __name__ == "__main__":
    main()
