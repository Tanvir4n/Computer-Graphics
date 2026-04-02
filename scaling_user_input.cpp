#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

// user input scaling
float sx = 1.0;
float sy = 1.0;

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
    glColor3f(1, 0, 0); // green

    // Original (left)
    glPushMatrix();
    glTranslatef(-40, 0, 0);
    drawHexagon();
    glPopMatrix();

    // Scaled (right)
    glPushMatrix();
    glTranslatef(40, 0, 0);
    glScalef(sx, sy, 1.0); // user input scaling
    drawHexagon();
    glPopMatrix();

    glutSwapBuffers();
}

int main(int argc, char **argv){

    // USER INPUT
    printf("Enter scaling factor for X: ");
    scanf("%f", &sx);

    printf("Enter scaling factor for Y: ");
    scanf("%f", &sy);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("2D Scaling (User Input)");

    init();
    glutDisplayFunc(Draw);

    glutMainLoop();
    return 0;
}
