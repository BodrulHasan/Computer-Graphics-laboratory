#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<math.h>
void display();
void reshape(int,int);

void init(){

glClearColor(.2,.3,.8,1.0);

}

int main(int argc,char ** argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
    glutInitWindowPosition(200,100);

    glutInitWindowSize(500,500);
    glutCreateWindow("Circle");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);


    init();

    glutMainLoop();

}

void drawCircle()
{
    float radius = 0.5;
    float theta, x, y;

    int numberOfSegments = 360;

    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < numberOfSegments; i++)
    {
        theta = i * 2.0 * 3.1416 / numberOfSegments;

        x = radius * cos(theta);
        y = radius * sin(theta);

        glVertex2f(x, y);
    }

    glEnd();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    drawCircle();
    glutSwapBuffers();

}

void reshape(int x, int y){
glViewport(0,0,x,y);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(-10,10,-10,10);
glMatrixMode(GL_MODELVIEW);

}
