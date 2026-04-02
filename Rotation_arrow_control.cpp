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

// Arrow key control
void spe_key(int key, int x, int y){
    switch(key){

        case GLUT_KEY_RIGHT:
            angle += 10;   // clockwise
            break;

        case GLUT_KEY_LEFT:
            angle -= 10;   // anticlockwise
            break;

        case GLUT_KEY_UP:
            angle += 10;  // faster rotate
            break;

        case GLUT_KEY_DOWN:
            angle -= 10;  // faster reverse
            break;
    }

    glutPostRedisplay();
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("2D Rotation - Arrow Control");

    init();
    glutDisplayFunc(Draw);

    // Arrow key control enable
    glutSpecialFunc(spe_key);

    glutMainLoop();
    return 0;
}
