#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void display();
void reshape(int, int);

void init()
{
    glClearColor(0.9, 0.9, 0.9, 1.0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutInitWindowPosition(200, 100);

    glutInitWindowSize(500, 500);

    glutCreateWindow("Rectangle");

    glutReshapeFunc(reshape);

    glutDisplayFunc(display);

    init();

    glutMainLoop();

    return 0;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    glBegin(GL_QUADS);

        glColor3f(1.0, 1.0, 0.0);
        
        glVertex2d(-1,1);
        glVertex2d(-1,-1);
        glVertex2d(1, -1);
        glVertex2d(1, 1);
        
        glColor3f(1.0, .0, 0.0);

        glVertex2d(2, 3);
        glVertex2d(5, 3);
        glVertex2d(5, -3);
        glVertex2d(2, -3);


    glEnd();



    glBegin(GL_TRIANGLES);

        glColor3f(0.1, .1, .9);

        glVertex2d(-4 , 4);
        glVertex2d(-6, 0);
        glVertex2d(-2 , 0);
       

    glEnd();



    glBegin(GL_LINES);

        glColor3f(0.1, .1, .1);

        glVertex2d(0 , 10);
        glVertex2d(0, -10);
        glVertex2d(10 , 0);
        glVertex2d(-10, 0);

    glEnd();

   

    glutSwapBuffers();
}

void reshape(int x, int y)
{
    glViewport(0, 0, x, y);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluOrtho2D(-10, 10, -10, 10);

    glMatrixMode(GL_MODELVIEW);
}