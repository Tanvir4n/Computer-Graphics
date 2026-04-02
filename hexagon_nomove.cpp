#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

float tx = 0.0;
float ty = 0.0;

void init(void){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100.0, 100.0, -100.0, 100.0, -1.0, 1.0);
}

void Draw(){
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1, 1, 1); // white color

    glPushMatrix();
    glTranslatef(tx, ty, 0);

    float r = 30;

    // Hexagon (Benzene ring)
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 6; i++){
        float angle = 2 * 3.1416 * i / 6 + 3.1416 / 6; // rotate 30°
        float x = r * cos(angle);
        float y = r * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();

    glPopMatrix();

    glutSwapBuffers();
}

/*
void spe_key(int key, int x, int y){
    switch (key){
    case GLUT_KEY_UP: ty += 5; break;
    case GLUT_KEY_DOWN: ty -= 5; break;
    case GLUT_KEY_RIGHT: tx += 5; break;
    case GLUT_KEY_LEFT: tx -= 5; break;
    }

    glutPostRedisplay();
}
*/

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Hexagon Benzene Ring Only");

    init();
    glutDisplayFunc(Draw);
    //glutSpecialFunc(spe_key);

    glutMainLoop();
    return 0;
}
