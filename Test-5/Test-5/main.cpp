//
//  main.cpp
//  Test-5
//
//  Created by Aditya Ponnudurai on 01/01/22.
//
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

bool keyStates[256];
int x_angle = 0, y_angle = 0, z_angle = 0;

void drawObj(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0, 0, 0);
    //X,Y&Z Axis
    glBegin(GL_LINES);
    glVertex3f(5, 0, 0);
    glVertex3f(-5, 0, 0);
    glVertex3f(0, 5, 0);
    glVertex3f(0, -5, 0);
    glVertex3f(0, 0, 1);
    glVertex3f(0, 0, 100);
    glEnd();
    glColor3f(1.0, 0.0, 0.0);
    glLoadIdentity();
    glTranslatef(0, 0, -5);
    glPushMatrix();
    glRotatef(x_angle, 1, 0, 0);
    glRotatef(y_angle, 0, 1, 0);
    glRotatef(z_angle, 0, 0, 1);
    glutSolidTeapot(1);
    glPopMatrix();
    glFlush();

}

void keyOperations(void) {
    int ANGLE_INC = 45;
    if (keyStates['w']) { x_angle += ANGLE_INC; }
    else if (keyStates['s']) { x_angle -= ANGLE_INC; }
    else if (keyStates['a']) { y_angle -= ANGLE_INC; }
    else if (keyStates['d']) { y_angle += ANGLE_INC; }
    else if (keyStates[' ']) { z_angle += ANGLE_INC; }
    x_angle %= 360;
    y_angle %= 360;
    z_angle %= 360;
    drawObj();
}

void keyPressed(unsigned char key, int x, int y) {
    keyStates[key] = true;
    keyOperations();
}

void keyUp(unsigned char key, int x, int y) {
    keyStates[key] = false;
}

void myInit(){
    int width=500,height=500,choice;
//    choice = 1;
    choice = 2;
    glClearColor(1, 1, 1, 0);
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    if(choice == 1)
        glOrtho(-2, 2, -2, 2, 1, 100);
    else
        gluPerspective(60, (GLfloat)width/(GLfloat)height,1, 100);
    
    glMatrixMode(GL_MODELVIEW);
    for (int i = 0; i < 256; ++i) {
        keyStates[i] = false;
    }
    glEnable(GL_DEPTH_TEST);
    
}

int main(int argc,char * argv[]) {
    
    glutInit(&argc,argv);
    glutInitWindowSize(500, 500);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutCreateWindow("3D Projection");
    glutDisplayFunc(drawObj);
    myInit();
    glutKeyboardFunc(keyPressed);
    glutKeyboardUpFunc(keyUp);
    glutMainLoop();
    return 1;
    
}
