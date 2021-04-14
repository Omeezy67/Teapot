#define GL_SILENCE_DEPRECATION
#include <Opengl/Gl.h>
#include <OpenGL/glu.h>
#include <GLUT/GLUT.h>
#include <math.h>
#define W 600
#define H 600

void displaySolid(void)
{
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(-W, W, -H, H, -W, W);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
gluLookAt(0,0,10,0,0,0,0.0,1.0,0.0);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glutSolidTeapot(300);
glFlush();
glutSwapBuffers();

GLfloat mat_ambient1[]= {0.5f, 0.5f, 0.6f, 1.0f};
GLfloat mat_diffuse1[] = {0.6f, 0.6f, 0.6f, 1.0f};
GLfloat mat_specular1[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat mat_shininess1[] = {90.0f};
glMaterialfv(GL_FRONT, GL_AMBIENT,mat_ambient1);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular1);
glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess1);
}



float tepot_angle = 0.0f;
float light_angle = 0.0f;
float rAmbient = 0.0f;
float gAmbient = 0.0f;
float bAmbient = 0.0f;



void calculateColor(float x, float y) {
rAmbient = (x + 600) / 1200.0;
gAmbient = (y + 600) / 1200.0;
bAmbient = (-y + 600) / 1200.0;
}


// funtion to convert an angle from degrees to radians
float _Convert2Radians(float degree)
{
float pi = 3.14159265359;
return (degree * (pi / 180));
}



void displayTeapot(float x, float y, float size) {
calculateColor(x,y);
        
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
glEnable(GL_LIGHT1);
glEnable(GL_LIGHT2);
glEnable(GL_LIGHT3);
glEnable(GL_LIGHT4);
glShadeModel(GL_SMOOTH);
glEnable(GL_DEPTH_TEST);
glEnable(GL_NORMALIZE);

//Direction / intensity of thelight.

GLfloat lightPosition1[] = { 1000 * cos(light_angle), 0, 1000 * sin(light_angle), 1.0f };
GLfloat lightIntensity1[] = { 1.0f, 0.0f, 0.0f, 1.0f };
glLightfv(GL_LIGHT0, GL_POSITION, lightPosition1);
glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity1);

GLfloat lightPosition5[] = { 0, 0, 300, 1.0f };
GLfloat lightIntensity5[] = { 1.0f, 1.0f, 1.0f, 1.0f };
glLightfv(GL_LIGHT4, GL_POSITION, lightPosition5);
glLightfv(GL_LIGHT4, GL_DIFFUSE, lightIntensity5);

//Add ambient light. Materials.
    
GLfloat mat_ambient[] = { rAmbient,   gAmbient, bAmbient, 1.0f };
GLfloat mat_diffuse[] = { rAmbient,   gAmbient, bAmbient, 1.0f };
GLfloat mat_specular[] = { rAmbient,   gAmbient, bAmbient, 1.0f };
GLfloat mat_shininess[] = { 100.0f };
glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
glLoadIdentity();
glPushMatrix();
glTranslatef(x + 3 * size / 2, y, 0);
glRotatef(_Convert2Radians(tepot_angle), 0.0f, 1.0f, 0.0f);
glutSolidTeapot(size);
glFlush();
glPopMatrix();
}



void displayWithLight() {
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(-W, W, -H, H, -W, W);
glMatrixMode(GL_MODELVIEW);
gluLookAt(0, 0, 10, 0, 0, 0, 0.0, 1.0, 0.0);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

for (float i=-W; i < +W; i+=W/4)
for (float j = -H; j < +H; j += H / 8)
        {
            displayTeapot(i+20.0f, j+30.0f, 45.0f);
        }
tepot_angle += 200.0;
light_angle += 50.0;

glutSwapBuffers();
glutPostRedisplay();
}


int main(int argc, char** argv)
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
glutInitWindowSize(W, H);
glutInitWindowPosition(100, 100);
glutCreateWindow("My Teapot");
    
glutDisplayFunc(displayWithLight);
    
glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
glViewport(0, 0, W, H);
    
glutMainLoop();
return 0;
}

