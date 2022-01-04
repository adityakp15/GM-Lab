#include<GLUT/GLUT.h>
#include <vector>
#include <stdio.h>
#include <map>
#include <math.h>
#include <string>
using namespace std;
typedef struct Point {
    double x;
    double y;
    double z;
    double h;
};
double SIDE = 2;
Point multiply(vector<vector<double>> mat1, Point P);
class Cube {
map<char, Point> vertices;
string quads[6] = { "ABCD", "ADEF", "CDEH", "BCHG", "BAFG", "EFGH" };
vector<vector<double>> side_colors = {
{1.0, 0.5, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 1.0}, {1.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 1.0, 1.0},
};

public: Cube() {
vector<Point> points = {
{ -SIDE / 2, -SIDE / 2, -SIDE / 2, 1 },
{-SIDE/2, SIDE/2,-SIDE/2,1}, { SIDE/2, SIDE/2,-SIDE/2,1}, { SIDE/2,-SIDE/2,-SIDE/2,1}, { SIDE/2,-SIDE/2, SIDE/2,1}, {-SIDE/2,-SIDE/2, SIDE/2,1}, {-SIDE/2, SIDE/2, SIDE/2,1}, { SIDE/2, SIDE/2, SIDE/2,1}
};
for (int i = 0; i < points.size(); i++) {
vertices.insert(pair<char, Point>('A'+i, points[i])); }
}
    void draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3d(-250, 0, 0);
    glVertex3d(250, 0, 0);
    glVertex3d(0, -250, 0);
    glVertex3d(0, 250, 0);
    glVertex3d(0, 0, -250);
    glVertex3d(0, 0, 250);
    glEnd();
    for (int i = 0; i < 6; i++) {
    glColor3f(side_colors[i][0], side_colors[i][1], side_colors[i][2]); string quad = quads[i];
    glBegin(GL_QUADS);
    for (int j = 0; j < 4; j++) {
    glVertex3d(vertices[quad[j]].x, vertices[quad[j]].y, vertices[quad[j]].z); }
    glEnd(); }
    glFlush(); }
    
    void translate(double tx, double ty, double tz) {
        vector<vector<double>> T(4, vector<double>(4, 0));
        for (int i = 0; i < 4; i++) {
    T[i][i] = 1; }
    T[0][3] = tx;
    T[1][3] = ty;
    T[2][3] = tz;
    for (int i = 0; i < 8; i++) {
    vertices['A'+i] = multiply(T, vertices['A' + i]);
    }
    return; }

    void rotateX(double theta) {
    vector<vector<double>> R(4, vector<double>(4, 0));
    double rad = (theta * 3.1416) / 180;
    R[0][0] = 1;
    R[1][1]= cos(rad);
    R[1][2]= -sin(rad);
    R[2][1]= sin(rad);
    R[2][2]  = cos(rad);
    R[3][3]  = 1;
    for(int i = 0; i < 8; i++) {
    vertices['A' + i] = multiply(R, vertices['A' + i]);
    }
        return;
    }
    
    void rotateY(double theta) {
    vector<vector<double>> R(4, vector<double>(4, 0));
    double rad = (theta * 3.1416) / 180;
    R[1][1] = 1;
    R[0][0] = cos(rad);
    R[0][2] = sin(rad);
    R[2][0] = -sin(rad);
    R[2][2] = cos(rad);
    R[3][3] = 1;
    for (int i = 0; i < 8; i++) {
    vertices['A' + i] = multiply(R, vertices['A' + i]);
    }
    return; }
    
    void rotateZ(double theta) {
    vector<vector<double>> R(4, vector<double>(4, 0));
        double rad = (theta * 3.1416) / 180;
        R[2][2] = 1;
        R[0][0] = cos(rad);
        R[0][1] = -sin(rad);
        R[1][0] = sin(rad);
        R[1][1] = cos(rad);
        R[3][3] = 1;
        for (int i = 0; i < 8; i++){
            vertices['A' + i] = multiply(R, vertices['A' + i]);
        }
        return;
        
    }
         
void scale(double sx, double sy, double sz) {
    vector<vector<double>> S(4, vector<double>(4, 0));
    S[0][0] = sx;
    S[1][1] = sy;
    S[2][2] = sz;
    S[3][3] = 1;
    for (int i = 0; i < 8; i++) {
        vertices['A' + i] = multiply(S, vertices['A' + i]);
}
return; }
};

Point multiply(vector<vector<double>> mat1, Point P) { vector<double> product(4, 0);
vector<double> mat2 = { P.x, P.y, P.z, P.h };
// 4 x 4 matrix multiplied with 4 x 1 (represented as a 1 x 4)
for (int i = 0; i < 4; i++) {
for (int j = 0; j < 4; j++) {
product[i] += mat1[i][j] * mat2[j];
} }
return Point({product[0], product[1], product[2], product[3]});
}

void initialize() {
char choice;
glClearColor(1.0, 1.0, 1.0, 0.0);
glPointSize(5);
glLoadIdentity();
//glOrtho(-250, 250.0, -250.0, 250.0, -250.0, 250.0);
printf("Set view inside or outside the cube? (I/O): ");
scanf("%c", &choice);
if(choice == 'O')
gluPerspective(43.6, 1, 4, 15);
else
gluPerspective(43.6, 1, 5.2, 15);
gluLookAt(0, 0, 6, 0, 0, 5, 0, 1, 0);
glEnable(GL_DEPTH_TEST);
}

void demo3d() {
double tx, ty, tz, theta, sx, sy, sz; int choice;
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// Initial cube
    Cube cube;
    cube.draw();
// Transforms demo
printf("\n-----3D TRANSFORMS-----\n1 - Translate\n2 - Rotate about X-axis\n3 - Rotate about Y-axis\n");
printf("4 - Rotate about Z-axis\n5 - Scale\n\nEnter choice: "); scanf("%d", &choice);
switch (choice) {
    case 1:
printf("\nEnter tx, ty, tz: "); scanf("%lf %lf %lf", &tx, &ty, &tz); cube.translate(tx, ty, tz);
break;
case 2:
printf("Enter theta (degrees): "); scanf("%lf", &theta); cube.rotateX(theta);
break; case 3:
printf("Enter theta (degrees): "); scanf("%lf", &theta); cube.rotateY(theta);
break;
case 4:
printf("Enter theta (degrees): "); scanf("%lf", &theta); cube.rotateZ(theta);
break;
case 5:
printf("Enter sx, sy, sz: "); scanf("%lf %lf %lf", &sx, &sy, &sz); cube.scale(sx, sy, sz);
break;
default:
printf("Invalid choice\n"); break;
} cube.draw();
glFlush(); }

int main(int argc, char* argv[]) {
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize(500, 500);
glutCreateWindow("3D Transforms");
glutDisplayFunc(demo3d);
initialize();
glutMainLoop(); }
             
    
         
         

