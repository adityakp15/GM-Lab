//
//  main.cpp
//  Test-2
//
//  Created by Aditya Ponnudurai on 31/12/21.
//
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

int n;

using namespace std;

typedef struct {
    float x;
    float y;
}Point;

void myinit() {
    glClearColor(1, 1, 1, 0);
    glColor3f(0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glPointSize(5);
    glLoadIdentity();
    gluOrtho2D(-250, 250, -250, 250);
}

void translate(float T[][3], float tx, float ty) {
    float temp[3][3] = { {1,0,tx},{0,1,ty},{0,0,1} };
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            T[i][j] = temp[i][j];
        }
    }
}

void multiply(float T[3][3], float P[3][10], float newP[3][10]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < n; ++j) {
            newP[i][j] = 0;
            for (int k = 0; k < 3; ++k) {
                newP[i][j] += T[i][k] * P[k][j];
            }
        }
    }
}

void multiplyT(float T1[3][3], float T2[3][3], float newT[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            newT[i][j] = 0;
            for (int k = 0; k < 3; ++k) {
                newT[i][j] += T1[i][k] * T2[k][j];
            }
        }
    }
}

void plot(float P[3][10]) {
    glBegin(GL_LINE_LOOP);
    for (int j = 0; j < n; ++j) {
        glVertex2f(P[0][j], P[1][j]);
    }
    glEnd();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << P[j][i] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void scale(float T[3][3], float sx, float sy, Point fp) {
    float temp[3][3] = { {sx,0,fp.x*(1-sx)},{0,sy,fp.y*(1-sy)},{0,0,1} };
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            T[i][j] = temp[i][j];
        }
    }
}

void rotate(float T[3][3], float a, Point fp) {
    a = a * 3.14 / 180;
    float temp[3][3] = { {cos(a),-sin(a),fp.x*(1-cos(a))+fp.y*sin(a)},{sin(a),cos(a),fp.y*(1-cos(a))-fp.x*sin(a)},{0,0,1} };
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            T[i][j] = temp[i][j];
            cout << T[i][j] << " ";
        }
    }
}

void reflectX(float T[3][3]) {
    float temp[3][3] = { {1,0,0},{0,-1,0},{0,0,1} };
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            T[i][j] = temp[i][j];
        }
    }
}

void reflectY(float T[3][3]) {
    float temp[3][3] = { {-1,0,0},{0,1,0},{0,0,1} };
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            T[i][j] = temp[i][j];
        }
    }
}


void reflectOrigin(float T[3][3]) {
    float temp[3][3] = { {-1,0,0},{0,-1,0},{0,0,1} };
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            T[i][j] = temp[i][j];
        }
    }
}


void reflectXY(float T[3][3]) {
    float temp[3][3] = { {0,1,0},{1,0,0},{0,0,1} };
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            T[i][j] = temp[i][j];
        }
    }
}

void shearX(float T[3][3], float sh) {
    float temp[3][3] = { {1,sh,0},{0,1,0},{0,0,1} };
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            T[i][j] = temp[i][j];
        }
    }
}

void shearY(float T[3][3], float sh) {
    float temp[3][3] = { {1,0,0},{sh,1,0},{0,0,1} };
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            T[i][j] = temp[i][j];
        }
    }
}

void transform() {

    glClear(GL_COLOR_BUFFER_BIT);
    Point fp;
    float T[3][3];
    float P[3][10], newP[3][10];
    n = 3;
    P[0][0] = 0;
    P[1][0] = 0;
    P[2][0] = 1;
    P[0][1] = 50;
    P[1][1] = 50;
    P[2][1] = 1;
    P[0][2] = 100;
    P[1][2] = 0;
    P[2][2] = 1;
    fp.x = 100;
    fp.y = 100;
    //translate(T, 50,50);
    //scale(T, 2, 3, fp);
    //rotate(T, 45, fp);
    //reflectX(T);
    //reflectY(T);
    //reflectOrigin(T);
    //reflectXY(T);
    //shearX(T, 1);
    shearY(T, 1);
    multiply(T, P,newP);
    plot(P);
    glColor3f(1, 0, 0);
    plot(newP);
    glFlush();
}

void composite() {
    glClear(GL_COLOR_BUFFER_BIT);
    Point fp;
    float T1[3][3], T2[3][3], T[3][3];
    float P[3][10], newP[3][10];
    n = 3;
    P[0][0] = 0;
    P[1][0] = 0;
    P[2][0] = 1;
    P[0][1] = 50;
    P[1][1] = 50;
    P[2][1] = 1;
    P[0][2] = 100;
    P[1][2] = 0;
    P[2][2] = 1;

    fp.x = 50;
    fp.y = 50;
    
    rotate(T1, 45,fp);
    translate(T2, 50, 50);
    multiplyT(T1, T2, T);
    multiply(T, P, newP);
    plot(P);
    glColor3f(1, 0, 0);
    plot(newP);
    glFlush();
}

void animate(int state) {
    glClear(GL_COLOR_BUFFER_BIT);
    Point fp;
    float T[3][3];
    float P[3][10], newP[3][10];
    n = 2;
    P[0][0] = 0;
    P[1][0] = 0;
    P[2][0] = 1;
    P[0][1] = 100;
    P[1][1] = 100;
    P[2][1] = 1;
    fp.x = 0;
    fp.y = 0;
    rotate(T, state, fp);
    //translate(T, state, 0);
    multiply(T, P, newP);
    glColor3f(1, 0, 0);
    plot(newP);
    glFlush();
    glutTimerFunc(1000, animate, (state + 2) % 360);
    
}

void demo() {
    glutTimerFunc(1000, animate, 0);
}


int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("2D transforms");
    glutDisplayFunc(demo);
    myinit();
    glutMainLoop();
    return 1;
}
