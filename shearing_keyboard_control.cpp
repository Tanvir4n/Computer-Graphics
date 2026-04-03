#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

float shx = 0.5;  // shear in X
float shy = 0.0;  // shear in Y

void init(void){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100.0, 100.0, -100.0, 100.0, -1.0, 1.0);
}

// draw hexagon
void drawHexagon(){
    float r = 30;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 6; i++){
        float angle = 2 * 3.1416 * i / 6 + 3.1416 / 6;
        float x = r * cos(angle);
        float y = r * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

void Draw(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);

    // Original (left)
    glPushMatrix();
    glTranslatef(-40, 0, 0);
    drawHexagon();
    glPopMatrix();

    // Sheared (right)
    glPushMatrix();
    glTranslatef(40, 0, 0);

    // Shear Matrix
    GLfloat shearMatrix[16] = {
        1,   shy, 0, 0,
        shx, 1,   0, 0,
        0,   0,   1, 0,
        0,   0,   0, 1
    };

    glMultMatrixf(shearMatrix);

    drawHexagon();
    glPopMatrix();

    glutSwapBuffers();
}

// Keyboard control
void keyboard(unsigned char key, int x, int y){
    switch(key){
        case 'x': shx += 0.1; break;
        case 'X': shx -= 0.1; break;

        case 'y': shy += 0.1; break;
        case 'Y': shy -= 0.1; break;
    }

    glutPostRedisplay();
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("2D Shearing - Benzene");

    init();
    glutDisplayFunc(Draw);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
