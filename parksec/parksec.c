/* "Hello World" in C using OGL - Open Graphics Library */

#include <GL/glut.h>
#define font GLUT_BITMAP_HELVETICA_18
#define tx "Hello"
#define tx2 "World!"

void text(void)
{
    char *p, tex[] = tx;
    p = tex;
    glColor3d(1.0, 1.0, 1.0);
    glRasterPos3d(-.0, -.01, -.5);
    while(*p) glutBitmapCharacter(font, *p++);
}

void text2(void)
{
    char *p, tex[] = tx2;
    p = tex;
    glColor3d(1.0, 1.0, 0.0);
    glRasterPos3d(0.0, 0.0, 0.0);
    while(*p) glutBitmapCharacter(font, *p++);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    text();
    text2();
    glFlush();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    display();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Hello World OpenGL");
    glClearColor(0,0,0,0);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
