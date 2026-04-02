#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

float angle = 0.0;   // rotation angle

void init(void){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100.0, 100.0, -100.0, 100.0, -1.0, 1.0);
}

void Draw(){
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1, 0, 0);

    glPushMatrix();

    // Rotation apply
    glRotatef(angle, 0, 0, 1);

    float r = 30;

    // Hexagon
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 6; i++){
        float ang = 2 * 3.1416 * i / 6 + 3.1416 / 6;
        float x = r * cos(ang);
        float y = r * sin(ang);
        glVertex2f(x, y);
    }
    glEnd();

    glPopMatrix();

    glutSwapBuffers();
}

// Mouse movement controls rotation
void mouseMove(int x, int y){
    angle = x;   // angle control with mouse X position
    glutPostRedisplay();
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("2D Rotation - Mouse Control");

    init();
    glutDisplayFunc(Draw);

    // Mouse control
    glutPassiveMotionFunc(mouseMove);

    glutMainLoop();
    return 0;
}
