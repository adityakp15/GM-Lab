//
//  main.cpp
//  Test-3
//
//  Created by Aditya Ponnudurai on 01/01/22.
//
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

float xw_max,xw_min,yw_max,yw_min,xv_max,xv_min,yv_max,yv_min;
int points[3][2];

void myInit(){
    glClearColor(1, 1, 1, 0);
    glColor3f(0, 0, 0);
    glPointSize(2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
}

void windowToViewport(){
    float sx,sy,xv,yv;
    glClear(GL_COLOR_BUFFER_BIT);
    
//    Window
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xw_min, yw_min);
    glVertex2f(xw_max, yw_min);
    glVertex2f(xw_max, yw_max);
    glVertex2f(xw_min, yw_max);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<3;i++){
        glVertex2f(points[i][0], points[i][1]);
    }
    glEnd();
    
//    Viewport
    glColor3f(0, 0, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xv_min, yv_min);
    glVertex2f(xv_max, yv_min);
    glVertex2f(xv_max, yv_max);
    glVertex2f(xv_min, yv_max);
    glEnd();
    
    sx = (xv_max-xv_min)/(xw_max-xw_min);
    sy = (yv_max-yv_min)/(yw_max-yw_min);
    
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<3;i++){
        xv = xv_min + (points[i][0]-xw_min)*sx;
        yv = yv_min + (points[i][1]-yw_min)*sy;
        cout<<xv<<" "<<yv<<endl;
        glVertex2f(xv, yv);
    }
    glEnd();
    glFlush();
}
int main(int argc,char * argv[]) {
    
    cout << "\nEnter xw_min: ";
    cin >> xw_min;
    cout << "\nEnter xw_max: ";
    cin >> xw_max;
    cout << "\nEnter yw_min: ";
    cin >> yw_min;
    cout << "\nEnter yw_max: ";
    cin >> yw_max;
    cout << "\nEnter xv_min: ";
    cin >> xv_min;
    cout << "\nEnter xv_max: ";
    cin >> xv_max;
    cout << "\nEnter yv_min: ";
    cin >> yv_min;
    cout << "\nEnter yv_max: ";
    cin >> yv_max;
    cout << "\nEnter point 1: ";
    cin >> points[0][0]>>points[0][1];
    cout << "\nEnter point 2: ";
    cin >> points[1][0]>>points[1][1];
    cout << "\nEnter point 3: ";
    cin >> points[2][0]>>points[2][1];
    
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
    glutCreateWindow("Window to Viewport");
    glutDisplayFunc(windowToViewport);
    myInit();
    glutMainLoop();
    return 1;
}
