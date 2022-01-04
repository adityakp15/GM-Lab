//
//  main.cpp
//  Test-6
//
//  Created by Aditya Ponnudurai on 03/01/22.
//

#define GL_SILENCE_DEPRECATION

#include <GLUT/glut.h>
#include <stdlib.h>
#include <stdio.h>

void myinit() {
    glClearColor(1, 1, 1, 0);
//glColor3f(0.0, 0.0, 0.0);
//    glShadeModel(GL_SMOOTH);
//    GLfloat light_diffuse[] = { 1,1,1,1 };
//
//    GLfloat light_position[] = { 0,0,1,0 };
//    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
//    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
//    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
}

void drawCube(int state) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 7, 0, 0, 0, 0, 1, 0);
//    GLfloat cube_color[] = { 0, 0, 1, 0.0 };
//    glMaterialfv(GL_FRONT, GL_DIFFUSE, cube_color);
    glRotatef(state, 1, 1, 0);
//    glutSolidCube(1);
    glColor3f(1, 0.5, 0);
    glutSolidTeapot(1);
    glutSwapBuffers();
    glutTimerFunc(1000 / 60, drawCube, (state+1)%360);
}

void cubeDemo() {
    glutTimerFunc(1000 / 60, drawCube, 0);
}

int main(int argc, char* argv[]) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("3d animation");
    glutDisplayFunc(cubeDemo);
    myinit();
    glutMainLoop();
    return 1;

}
