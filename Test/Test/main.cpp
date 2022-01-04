//
//  main.cpp
//  Test
//
//  Created by Aditya Ponnudurai on 29/12/21.
//
#define GL_SILENCE_DEPRECATION

#include<GLUT/glut.h>
#include <iostream>
#include<stdlib.h>
#include<math.h>

using namespace std;

void myInit(){
    glClearColor(1,1,1,0);
    glColor3f(0, 0, 0);
    glPointSize(2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
//    gluOrtho2D(-250, 250, -250, 250);
}

void dda(int x1, int y1, int x2, int y2){
    int x,y,dx,dy,steps,x_inc,y_inc;
    
    dx = x2-x1;
    dy = y2-y1;
    
    if(abs(dx)>=abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);
    
    x_inc = dx/steps;
    y_inc = dy/steps;
    
    x = x1;
    y = y1;
    
    for(int i=0;i<=steps;i++){
        glBegin(GL_POINTS);
        cout<<x<<" "<<y<<endl;
        glVertex2f(x, y);
        glEnd();
        
        x += x_inc;
        y += y_inc;

    }

//    glFlush();
    
}

void bresenham(int x1, int y1, int x2, int y2){
    int x,y,dx,dy;
    int x_inc,y_inc,a,b,p;
    bool isSwap = false;
    
    dx = abs(x2-x1);
    dy = abs(y2-y1);
    
    if(x2>x1)
        x_inc = 1;
    else
        x_inc = -1;
    
    if(y2>y1)
        y_inc = 1;
    else
        y_inc = -1;
    
    if(dy>dx){
//        swapping dy and dx
        int temp = dx;
        dx = dy;
        dy = temp;
        isSwap = true;
    }
    
    p = 2*dy-dx;
    a = 2*dy;
    b = 2*(dy-dx);
    
    x = x1;
    y = y1;
    
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    cout<<x<<" "<<y<<endl;
    for(int i=0;i<=dx;i++){
        if(p<0){
            if(isSwap)
                y += y_inc;
            else
                x += x_inc;
            p += a;
        }
        else{
            y += y_inc;
            x += x_inc;
            p += b;
        }
        glVertex2f(x, y);
        cout<<x<<" "<<y<<endl;

    }
    glEnd();
    
}

void mpc(int x1, int y1, int r){
    int x,y,p;
    
    x = 0;
    y = r;
    p = 1-r;
    
    glBegin(GL_POINTS);
    while(x<=y){
        x++;
        if(p<0){
            p += 2*x+1;
        }
        else{
            y--;
            p += 2*x+1-2*y;
        }
        glVertex2f(x+x1, y+y1);
        glVertex2f(-x+x1, y+y1);
        glVertex2f(x+x1, -y+y1);
        glVertex2f(-x+x1, -y+y1);
        glVertex2f(y+x1, x+y1);
        glVertex2f(-y+x1, x+y1);
        glVertex2f(y+x1, -x+y1);
        glVertex2f(-y+x1, -x+y1);
    }
    glEnd();
    
}
void myFunc(){
    glClear(GL_COLOR_BUFFER_BIT);
//    dda(100, 100, 100, 110);
//    dda(150, 150, 150, 160);
//    bresenham(100, 100, 100, 110);
//    bresenham(90, 105, 105, 90);
//    mpc(250, 250, 100);
    glFlush();
}

int main(int argc,char * argv[]) {
    
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Test");
    glutDisplayFunc(myFunc);
    myInit();
    glutMainLoop();
    return 1;
}
