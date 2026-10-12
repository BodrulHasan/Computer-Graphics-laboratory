
#include <GL/freeglut.h>
#include <cstdlib>

float rotateX = 25.0f;
float rotateY = -30.0f;
float cubeSize = 1.0f;

void drawSmallCube(float x, float y, float z)
{
    float gap = 0.035f;
    float s = cubeSize - gap;

    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(s, s, s);

    glBegin(GL_QUADS);

    // Front - Red
    glColor3f(0.9f, 0.05f, 0.05f);
    glVertex3f(-0.5f, -0.5f,  0.5f);
    glVertex3f( 0.5f, -0.5f,  0.5f);
    glVertex3f( 0.5f,  0.5f,  0.5f);
    glVertex3f(-0.5f,  0.5f,  0.5f);

    // Back - Orange
    glColor3f(1.0f, 0.35f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f,  0.5f, -0.5f);
    glVertex3f( 0.5f,  0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f, -0.5f);

    // Top - White
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f,  0.5f);
    glVertex3f( 0.5f, 0.5f,  0.5f);
    glVertex3f( 0.5f, 0.5f, -0.5f);

    // Bottom - Yellow
    glColor3f(1.0f, 0.9f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f,  0.5f);
    glVertex3f(-0.5f, -0.5f,  0.5f);

    // Right - Blue
    glColor3f(0.0f, 0.25f, 1.0f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f,  0.5f, -0.5f);
    glVertex3f(0.5f,  0.5f,  0.5f);
    glVertex3f(0.5f, -0.5f,  0.5f);

    // Left - Green
    glColor3f(0.0f, 0.75f, 0.15f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f,  0.5f);
    glVertex3f(-0.5f,  0.5f,  0.5f);
    glVertex3f(-0.5f,  0.5f, -0.5f);

    glEnd();

    // Black edge outlines
    glColor3f(0.04f, 0.04f, 0.04f);
    glutWireCube(1.002f);

    glPopMatrix();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(7.5, 6.0, 10.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    glRotatef(rotateX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotateY, 0.0f, 1.0f, 0.0f);

    // 4 x 4 x 4 = 64 small cubes
    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            for (int z = 0; z < 4; z++)
            {
                drawSmallCube(
                    (x - 1.5f) * cubeSize,
                    (y - 1.5f) * cubeSize,
                    (z - 1.5f) * cubeSize
                );
            }
        }
    }

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    if (h == 0) h = 1;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0,
                   (double)w / h,
                   0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int, int)
{
    switch (key)
    {
        case 'w': rotateX -= 5.0f; break;
        case 's': rotateX += 5.0f; break;
        case 'a': rotateY -= 5.0f; break;
        case 'd': rotateY += 5.0f; break;
        case '+': cubeSize += 0.05f; break;
        case '-': cubeSize -= 0.05f; break;
        case 27: std::exit(0);
    }

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(
        GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH
    );

    glutInitWindowSize(900, 700);
    glutCreateWindow("3D 4x4 Rubik Cube");

    glClearColor(0.08f, 0.09f, 0.13f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
