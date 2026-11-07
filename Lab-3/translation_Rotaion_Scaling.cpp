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
void drawSquare( float r, float g, float b){


  glBegin(GL_QUADS);

        glColor3f(r,g,b);
        
        glVertex2d(-1,1);
        glVertex2d(-1,-1);
        glVertex2d(1, -1);
        glVertex2d(1, 1);
        
    
    glEnd();


};
// Rotation 
//x' = x cos 0 + y sin 0
//y' = x sin 0 - y cos 0 

void drawVertex (){
    
    glBegin(GL_LINES);

        glColor3f(0.1, .1, .1);

        glVertex2d(0 , 10);
        glVertex2d(0, -10);
        glVertex2d(10 , 0);
        glVertex2d(-10, 0);

    glEnd();

};

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();


    // glBegin(GL_TRIANGLES);

    //     glColor3f(0.1, .1, .9);

    //     glVertex2d(0 , 1);
    //     glVertex2d(-1, 0);
    //     glVertex2d(1 , 0);
       

    // glEnd();

     drawVertex ();
    
    //  glTranslatef (2,4,0);            // Translate (Additive)
    

    
    // //  glScalef(2,2,1);         //Bigger             // Scalling (multiplicative)  -> center of gravity unchange

    //  glScalef(.5,.5,1);         //Smaller            // Scalling (multiplicative)  -> center of gravity unchange

glPushMatrix();
     glTranslated(-2,3,0);
     glScalef(1.5,3,1);
     drawSquare(1.0, 0.5, 0.9);
glPopMatrix();    

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

// 30 min class .....