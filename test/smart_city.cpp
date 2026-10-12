
#include <GL/freeglut.h>
#include <cmath>
#include <cstdlib>

// 3D SMART CITY SIMULATION
// Computer Graphics Final Year Project

float cameraX = 0.0f;
float cameraY = 35.0f;
float cameraZ = 65.0f;

float carPosition = -35.0f;
float rotationAngle = 0.0f;
bool showTrees = true;
bool showTrafficLights = true;
bool nightMode = false;

void drawText(float x, float y, const char* text)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 1000, 0, 700);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(0.2f, 0.95f, 1.0f);
    glRasterPos2f(x, y);

    for (int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void drawCube(float x, float y, float z,
              float sx, float sy, float sz,
              float r, float g, float b)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(sx, sy, sz);
    glColor3f(r, g, b);
    glutSolidCube(1.0);
    glPopMatrix();
}

void drawCylinder(float x, float y, float z,
                  float radius, float height,
                  float r, float g, float b)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    glColor3f(r, g, b);

    GLUquadric* q = gluNewQuadric();
    gluCylinder(q, radius, radius, height, 16, 8);
    gluDisk(q, 0, radius, 16, 1);
    glTranslatef(0, 0, height);
    gluDisk(q, 0, radius, 16, 1);
    gluDeleteQuadric(q);

    glPopMatrix();
}

void drawGround()
{
    drawCube(0, -0.6f, 0, 100, 1, 100,
             0.20f, 0.48f, 0.24f);

    // Main roads
    drawCube(0, -0.05f, 0, 100, 0.1f, 12,
             0.17f, 0.18f, 0.20f);

    drawCube(0, -0.04f, 0, 12, 0.1f, 100,
             0.17f, 0.18f, 0.20f);

    // Road lane markings
    for (int i = -45; i <= 45; i += 8)
    {
        drawCube((float)i, 0.02f, 0, 3, 0.04f, 0.18f,
                 1.0f, 0.9f, 0.35f);

        drawCube(0, 0.02f, (float)i, 0.18f, 0.04f, 3,
                 1.0f, 0.9f, 0.35f);
    }

    // Sidewalks
    drawCube(0, 0.0f, 7.5f, 100, 0.12f, 2,
             0.65f, 0.65f, 0.65f);

    drawCube(0, 0.0f, -7.5f, 100, 0.12f, 2,
             0.65f, 0.65f, 0.65f);

    drawCube(7.5f, 0.0f, 0, 2, 0.12f, 100,
             0.65f, 0.65f, 0.65f);

    drawCube(-7.5f, 0.0f, 0, 2, 0.12f, 100,
             0.65f, 0.65f, 0.65f);
}

void drawBuilding(float x, float z,
                  float width, float height, float depth,
                  float r, float g, float b)
{
    // Main building
    drawCube(x, height / 2.0f, z,
             width, height, depth, r, g, b);

    // Roof
    drawCube(x, height + 0.15f, z,
             width + 0.3f, 0.3f, depth + 0.3f,
             0.25f, 0.28f, 0.32f);

    // Windows on front and rear
    for (float wy = 1.5f; wy < height - 0.5f; wy += 2.0f)
    {
        for (float wx = -width / 2.0f + 0.8f;
             wx < width / 2.0f - 0.3f; wx += 1.5f)
        {
            float wr = nightMode ? 1.0f : 0.35f;
            float wg = nightMode ? 0.78f : 0.80f;
            float wb = nightMode ? 0.25f : 0.95f;

            drawCube(x + wx, wy, z + depth / 2.0f + 0.025f,
                     0.65f, 0.9f, 0.05f, wr, wg, wb);

            drawCube(x + wx, wy, z - depth / 2.0f - 0.025f,
                     0.65f, 0.9f, 0.05f, wr, wg, wb);
        }
    }

    // Windows on the sides
    for (float wy = 1.5f; wy < height - 0.5f; wy += 2.0f)
    {
        for (float wz = -depth / 2.0f + 0.8f;
             wz < depth / 2.0f - 0.3f; wz += 1.5f)
        {
            drawCube(x + width / 2.0f + 0.025f, wy, z + wz,
                     0.05f, 0.9f, 0.65f,
                     0.35f, 0.85f, 1.0f);

            drawCube(x - width / 2.0f - 0.025f, wy, z + wz,
                     0.05f, 0.9f, 0.65f,
                     0.35f, 0.85f, 1.0f);
        }
    }
}

void drawTree(float x, float z)
{
    if (!showTrees) return;

    drawCylinder(x, 0, z, 0.25f, 2.0f,
                 0.40f, 0.20f, 0.08f);

    glPushMatrix();
    glTranslatef(x, 2.5f, z);
    glColor3f(0.08f, 0.55f, 0.16f);
    glutSolidSphere(1.0, 16, 16);
    glPopMatrix();
}

void drawStreetLight(float x, float z)
{
    drawCylinder(x, 0, z, 0.08f, 4.0f,
                 0.30f, 0.30f, 0.32f);

    drawCube(x, 4.0f, z + 0.35f,
             0.15f, 0.12f, 0.8f,
             0.85f, 0.85f, 0.70f);

    glPushMatrix();
    glTranslatef(x, 4.0f, z + 0.65f);

    if (nightMode)
        glColor3f(1.0f, 0.9f, 0.45f);
    else
        glColor3f(0.8f, 0.8f, 0.6f);

    glutSolidSphere(0.22, 12, 12);
    glPopMatrix();
}

void drawCar(float x, float z, float r, float g, float b)
{
    // Car body
    drawCube(x, 0.65f, z, 3.5f, 0.9f, 1.7f,
             r, g, b);

    // Cabin
    drawCube(x, 1.3f, z, 1.8f, 0.65f, 1.35f,
             0.35f, 0.75f, 0.90f);

    // Wheels
    for (int side = -1; side <= 1; side += 2)
    {
        for (int front = -1; front <= 1; front += 2)
        {
            glPushMatrix();
            glTranslatef(x + front * 1.1f, 0.35f,
                         z + side * 0.85f);
            glRotatef(90, 0, 1, 0);
            glColor3f(0.08f, 0.08f, 0.08f);
            glutSolidTorus(0.12, 0.22, 10, 16);
            glPopMatrix();
        }
    }

    // Headlights
    drawCube(x + 1.76f, 0.72f, z - 0.48f,
             0.08f, 0.2f, 0.25f, 1.0f, 1.0f, 0.7f);

    drawCube(x + 1.76f, 0.72f, z + 0.48f,
             0.08f, 0.2f, 0.25f, 1.0f, 1.0f, 0.7f);
}

void drawTrafficSignal(float x, float z)
{
    if (!showTrafficLights) return;

    drawCylinder(x, 0, z, 0.12f, 4.0f,
                 0.15f, 0.15f, 0.15f);

    drawCube(x, 4.3f, z, 0.65f, 1.8f, 0.55f,
             0.08f, 0.08f, 0.08f);

    glPushMatrix();
    glTranslatef(x, 4.85f, z + 0.30f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glutSolidSphere(0.18, 12, 12);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x, 4.3f, z + 0.30f);
    glColor3f(1.0f, 0.75f, 0.0f);
    glutSolidSphere(0.18, 12, 12);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x, 3.75f, z + 0.30f);
    glColor3f(0.0f, 1.0f, 0.1f);
    glutSolidSphere(0.18, 12, 12);
    glPopMatrix();
}

void drawCity()
{
    // Buildings on both sides of the main road
    drawBuilding(-18, -18, 8, 16, 8,
                 0.35f, 0.45f, 0.65f);

    drawBuilding(-32, -24, 9, 23, 9,
                 0.55f, 0.35f, 0.65f);

    drawBuilding(-20, 18, 10, 25, 9,
                 0.25f, 0.55f, 0.75f);

    drawBuilding(-34, 22, 8, 14, 8,
                 0.65f, 0.40f, 0.30f);

    drawBuilding(19, -20, 10, 20, 9,
                 0.45f, 0.50f, 0.60f);

    drawBuilding(33, -25, 9, 28, 8,
                 0.30f, 0.45f, 0.55f);

    drawBuilding(20, 20, 9, 17, 9,
                 0.65f, 0.50f, 0.25f);

    drawBuilding(34, 24, 8, 22, 8,
                 0.35f, 0.55f, 0.45f);

    // Green areas
    for (int i = -40; i <= 40; i += 12)
    {
        drawTree((float)i, 10.0f);
        drawTree((float)i, -10.0f);
        drawTree(10.0f, (float)i);
        drawTree(-10.0f, (float)i);
    }

    // Street lights
    for (int i = -40; i <= 40; i += 15)
    {
        drawStreetLight((float)i, 8.8f);
        drawStreetLight((float)i, -8.8f);
    }

    // Traffic signals near the junction
    drawTrafficSignal(8.0f, 8.0f);
    drawTrafficSignal(-8.0f, -8.0f);

    // Moving vehicle
    drawCar(carPosition, -3.0f, 0.9f, 0.12f, 0.08f);
    drawCar(-carPosition, 3.0f, 0.10f, 0.25f, 0.9f);
}

void display()
{
    if (nightMode)
        glClearColor(0.025f, 0.035f, 0.10f, 1.0f);
    else
        glClearColor(0.40f, 0.72f, 0.95f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(cameraX, cameraY, cameraZ,
              0, 0, 0,
              0, 1, 0);

    drawGround();
    drawCity();

    // 2D dashboard overlay
    glDisable(GL_DEPTH_TEST);
    drawText(20, 665, "SMART CITY - 3D DIGITAL TWIN");
    drawText(20, 635,
             "W/S: Zoom  A/D: Rotate  T: Trees  L: Lights");
    drawText(20, 605,
             "N: Day/Night  Arrows: Camera  R: Reset");
    glEnable(GL_DEPTH_TEST);

    glutSwapBuffers();
}

void reshape(int width, int height)
{
    if (height == 0) height = 1;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(55.0,
                   (double)width / height,
                   0.5, 300.0);

    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int, int)
{
    switch (key)
    {
        case 'w':
        case 'W':
            cameraZ -= 4.0f;
            break;

        case 's':
        case 'S':
            cameraZ += 4.0f;
            break;

        case 'a':
        case 'A':
            cameraX -= 4.0f;
            break;

        case 'd':
        case 'D':
            cameraX += 4.0f;
            break;

        case 't':
        case 'T':
            showTrees = !showTrees;
            break;

        case 'l':
        case 'L':
            showTrafficLights = !showTrafficLights;
            break;

        case 'n':
        case 'N':
            nightMode = !nightMode;
            break;

        case 'r':
        case 'R':
            cameraX = 0;
            cameraY = 35;
            cameraZ = 65;
            break;

        case 27:
            std::exit(0);
    }

    glutPostRedisplay();
}

void specialKeys(int key, int, int)
{
    switch (key)
    {
        case GLUT_KEY_LEFT:
            rotationAngle -= 5;
            cameraX = 65.0f * sin(rotationAngle * 3.14159f / 180.0f);
            cameraZ = 65.0f * cos(rotationAngle * 3.14159f / 180.0f);
            break;

        case GLUT_KEY_RIGHT:
            rotationAngle += 5;
            cameraX = 65.0f * sin(rotationAngle * 3.14159f / 180.0f);
            cameraZ = 65.0f * cos(rotationAngle * 3.14159f / 180.0f);
            break;

        case GLUT_KEY_UP:
            cameraY += 2.0f;
            break;

        case GLUT_KEY_DOWN:
            cameraY -= 2.0f;
            if (cameraY < 5.0f) cameraY = 5.0f;
            break;
    }

    glutPostRedisplay();
}

void update(int)
{
    carPosition += 0.25f;

    if (carPosition > 45.0f)
        carPosition = -45.0f;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE |
                        GLUT_RGB |
                        GLUT_DEPTH);

    glutInitWindowSize(1200, 800);
    glutInitWindowPosition(100, 50);

    glutCreateWindow("Smart City 3D Digital Twin");

    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutTimerFunc(16, update, 0);

    glutMainLoop();

    return 0;
}
