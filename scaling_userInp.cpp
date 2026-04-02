#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

void init(void){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100.0, 100.0, -100.0, 100.0, -1.0, 1.0);
}

// draw hexagon
void drawHexagon(){
    float r = 20;

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
    glColor3f(0, 1, 0); // green like image

    // Original (left side)
    glPushMatrix();
    glTranslatef(-40, 0, 0);
    drawHexagon();
    glPopMatrix();

    // Scaled (right side)
    glPushMatrix();
    glTranslatef(40, 0, 0);   // move to right
    glScalef(2.0, 2.0, 1.0);  // scaling (bigger)
    drawHexagon();
    glPopMatrix();

    glutSwapBuffers();
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("2D Scaling Demo");

    init();
    glutDisplayFunc(Draw);

    glutMainLoop();
    return 0;
}
