//
//  main.cpp
//  Test-4
//
//  Created by Aditya Ponnudurai on 01/01/22.
//
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

typedef struct {
    float x;
    float y;
}Point;

float xmin, ymin, xmax, ymax;

void myinit() {
    glClearColor(1, 1, 1, 0);
    glColor3f(0, 0, 0);
    glPointSize(2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
}

void findRegionCode(Point p, int rc[4]) {
    //rc - TBRL
    if (p.y > ymax)
        rc[0] = 1;
    else
        rc[0] = 0;
    if (p.y < ymin)
        rc[1] = 1;
    else
        rc[1] = 0;
    if (p.x > xmax)
        rc[2] = 1;
    else
        rc[2] = 0;
    if (p.x < xmin)
        rc[3] = 1;
    else
        rc[3] = 0;
}

bool trivialAccept(int rc0[4], int rc1[4]) {
    int res[4];
    for (int i = 0; i < 4; ++i) {
        res[i] = rc0[i] || rc1[i];
        if (res[i] != 0) {
            return false;
        }
    }
    return true;
}

bool trivialReject(int rc0[4], int rc1[4]) {
    int res[4];
    for (int i = 0; i < 4; ++i) {
        res[i] = rc0[i] && rc1[i];
        if (res[i] == 1) {
            return true;
        }
    }
    return false;
}

void CohenPoint(Point *p, int rc[4], float m ) {
    float xClip, yClip;
    float x = p->x, y = p->y;
    if (rc[0] == 1) {
        xClip = x + (ymax - y) / m;
        if (xClip <= xmax && xClip >= xmin) {
            x = xClip;
            y = ymax;
        }
    }
    if (rc[1] == 1) {
        xClip = x + (ymin - y) / m;
        if (xClip <= xmax && xClip >= xmin) {
            x = xClip;
            y = ymin;
        }
    }
    if (rc[2] == 1) {
        yClip = y + (xmax - x) * m;
        if (yClip <= ymax && yClip >= ymin) {
            y = yClip;
            x = xmax;
        }
    }
    if (rc[3] == 1) {
        yClip = y + (xmin - x) * m;
        if (yClip <= ymax && yClip >= ymin) {
            y = yClip;
            x = xmin;
        }
    }
    p->x = x;
    p->y = y;
}


void clip() {
    Point p1, p2;
    p1.x = 50;
    p1.y = 50;
    p2.x = 350;
    p2.y = 450;

    int rc1[4], rc2[4];

    float m = (p2.y - p1.y) / (p2.x - p1.x);

    findRegionCode(p1, rc1);
    findRegionCode(p2, rc2);

    if (trivialAccept(rc1, rc2)) {
        cout << "\nLine inside";
        glColor3f(0, 1, 1);
        glBegin(GL_LINE);
        glVertex2f(p1.x, p1.y);
        glVertex2f(p2.x, p2.y);
        glEnd();
    }
    else if (trivialReject(rc1, rc2)) {
        cout << "\nLine outside";
    }
    else {
        cout << "\nLine to be clipped";
        CohenPoint(&p1,rc1,m);
        CohenPoint(&p2, rc2,m);
        glColor3f(1, 0.5, 0);

        glBegin(GL_LINES);
        glVertex2f(p1.x, p1.y);
        glVertex2f(p2.x, p2.y);
        glEnd();
    }
}

void lineClipping() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);
    xmin = 200;
    ymin = 200;
    xmax = 400;
    ymax = 400;
    glRectf(xmin, ymin, xmax, ymax);
    clip();
    glFlush();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Line clipping");
    glutDisplayFunc(lineClipping);
    myinit();
    glutMainLoop();
    return 1;
}
