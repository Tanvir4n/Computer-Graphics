#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

int choice = 0;

// Translation
float tx = 0.0f, ty = 0.0f;

// Scaling
float sx = 1.0f, sy = 1.0f;

// Rotation
float angle = 10.0f;

// Reflection
int refType = 1;

// 🔥 Shearing
float shx = 0.5f, shy = 0.0f;

void circle(GLfloat r, GLfloat cx, GLfloat cy)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 360; i++)
    {
        float a = i * 3.1416f / 180;
        glVertex2f(cx + r * cos(a), cy + r * sin(a));
    }
    glEnd();
}

void drawFlag(float ox, float oy, float w, float h)
{
    float flagLeft   = ox;
    float flagRight  = ox + w;
    float flagBottom = oy;
    float flagTop    = oy + h;
    float flagCX     = ox + w * 0.42f;
    float flagCY     = oy + h * 0.5f;
    float radius     = h * 0.28f;

    // Pole
    glColor3f(0.545f, 0.412f, 0.078f);
    glBegin(GL_QUADS);
    glVertex2f(ox - 4, oy - 40);
    glVertex2f(ox - 4, flagTop + 20);
    glVertex2f(ox,     flagTop + 20);
    glVertex2f(ox,     oy - 40);
    glEnd();

    // Tip
    glColor3f(0.855f, 0.647f, 0.125f);
    glBegin(GL_TRIANGLES);
    glVertex2f(ox - 2, flagTop + 30);
    glVertex2f(ox - 6, flagTop + 20);
    glVertex2f(ox + 2, flagTop + 20);
    glEnd();

    // Flag
    glColor3f(0.0f, 0.416f, 0.306f);
    glBegin(GL_QUADS);
    glVertex2f(flagLeft,  flagBottom);
    glVertex2f(flagLeft,  flagTop);
    glVertex2f(flagRight, flagTop);
    glVertex2f(flagRight, flagBottom);
    glEnd();

    // Circle
    glColor3f(0.957f, 0.165f, 0.255f);
    circle(radius, flagCX, flagCY);
}

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-200.0, 200.0, -200.0, 200.0);
}

void drawShapes(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    float fw = 120.0f, fh = 80.0f;
    float fx = -fw * 0.42f;
    float fy = -fh * 0.5f;

    if (choice == 1)
    {
        glPushMatrix();
        glTranslatef(tx, ty, 0.0f);
        drawFlag(fx, fy, fw, fh);
        glPopMatrix();
    }
    else if (choice == 2)
    {
        glPushMatrix();
        glScalef(sx, sy, 1.0f);
        drawFlag(fx, fy, fw, fh);
        glPopMatrix();
    }
    else if (choice == 3)
    {
        glPushMatrix();
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
        drawFlag(fx, fy, fw, fh);
        glPopMatrix();
    }
    else if (choice == 4)
    {
        glPushMatrix();
        if (refType == 1)
            glScalef(1.0f, -1.0f, 1.0f);
        else if (refType == 2)
            glScalef(-1.0f, 1.0f, 1.0f);
        else
            glScalef(-1.0f, -1.0f, 1.0f);

        drawFlag(fx, fy, fw, fh);
        glPopMatrix();
    }
    else if (choice == 5)
    {
        // 🔥 SHEARING
        glPushMatrix();

        GLfloat shearMatrix[16] = {
            1,   shy, 0, 0,
            shx, 1,   0, 0,
            0,   0,   1, 0,
            0,   0,   0, 1
        };

        glMultMatrixf(shearMatrix);

        drawFlag(fx, fy, fw, fh);
        glPopMatrix();
    }

    glutSwapBuffers();
}

void specialKeys(int key, int x, int y)
{
    if (choice == 1)
    {
        if (key == GLUT_KEY_UP)    ty += 5;
        if (key == GLUT_KEY_DOWN)  ty -= 5;
        if (key == GLUT_KEY_RIGHT) tx += 5;
        if (key == GLUT_KEY_LEFT)  tx -= 5;
        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y)
{
    if (choice == 3)
    {
        if (key == 'l') { angle += 10; glutPostRedisplay(); }
        if (key == 'r') { angle -= 10; glutPostRedisplay(); }
    }

    // 🔥 Shearing control
    if (choice == 5)
    {
        if (key == 'x') { shx += 0.1f; glutPostRedisplay(); }
        if (key == 'X') { shx -= 0.1f; glutPostRedisplay(); }
        if (key == 'y') { shy += 0.1f; glutPostRedisplay(); }
        if (key == 'Y') { shy -= 0.1f; glutPostRedisplay(); }
    }
}

int main(int argc, char* argv[])
{
    printf("========================================\n");
    printf("  Bangladesh Flag - 2D Transformations  \n");
    printf("========================================\n");
    printf("  1. Translation\n");
    printf("  2. Scaling\n");
    printf("  3. Rotation\n");
    printf("  4. Reflection\n");
    printf("  5. Shearing \n");
    printf("========================================\n");
    printf("Enter your choice (1-5): ");
    scanf("%d", &choice);

    if (choice == 2)
    {
        printf("Enter sx: "); scanf("%f", &sx);
        printf("Enter sy: "); scanf("%f", &sy);
    }
    else if (choice == 4)
    {
        printf("1.X-axis  2.Y-axis  3.Origin: ");
        scanf("%d", &refType);
    }
    else if (choice == 5)
    {
        printf("Enter shear X (shx): ");
        scanf("%f", &shx);
        printf("Enter shear Y (shy): ");
        scanf("%f", &shy);
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);

    glutCreateWindow("BD Flag - Transformations");

    init();
    glutDisplayFunc(drawShapes);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
