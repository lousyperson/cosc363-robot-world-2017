//  ========================================================================
//  COSC363: Computer Graphics (2016);  University of Canterbury.
//
//  FILE NAME: Train.cpp
//  See Lab03.pdf for details
//  ========================================================================

//#include <stdlib.h>
#include <math.h>
#include <GL/freeglut.h>

GLUquadric *q;    //Required for creating cylindrical objects
double theta = -10.5;
int robotMovement = 0;
bool movementFlag = true;
float lgt_src[4] = { 0.0f, 20.0f, 0.0f, 1.0f };

//-- Ground Plane --------------------------------------------------------
void floor()
{
	float white[4] = { 1., 1., 1., 1. };
	float black[4] = { 0 };
	glColor4f(0.7, 0.7, 0.7, 1.0);  //The floor is gray in colour
	glNormal3f(0.0, 1.0, 0.0);

	glMaterialfv(GL_FRONT, GL_SPECULAR, black);

	//The floor is made up of several tiny squares on a 200x200 grid. Each square has a unit size.
	glBegin(GL_QUADS);
	for (int i = -200; i < 200; i++)
	{
		for (int j = -200; j < 200; j++)
		{
			glVertex3f(i, 0.0, j);
			glVertex3f(i, 0.0, j + 1);
			glVertex3f(i + 1, 0.0, j + 1);
			glVertex3f(i + 1, 0.0, j);
		}
	}
	glEnd();
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);

}

//------- Rail Track ----------------------------------------------------
// A single circular track of specified radius
void track(float radius)
{
	float angle1, angle2, ca1, sa1, ca2, sa2;
	float x1, z1, x2, z2, x3, z3, x4, z4;  //four points of a quad
	float toRad = 3.14159265 / 180.0;  //Conversion from degrees to radians

	glBegin(GL_QUADS);
	for (int i = 0; i < 360; i += 5)    //5 deg intervals
	{
		angle1 = i * toRad;       //Computation of angles, cos, sin etc
		angle2 = (i + 5) * toRad;
		ca1 = cos(angle1); ca2 = cos(angle2);
		sa1 = sin(angle1); sa2 = sin(angle2);
		x1 = (radius - 0.5)*sa1; z1 = (radius - 0.5)*ca1;
		x2 = (radius + 0.5)*sa1; z2 = (radius + 0.5)*ca1;
		x3 = (radius + 0.5)*sa2; z3 = (radius + 0.5)*ca2;
		x4 = (radius - 0.5)*sa2; z4 = (radius - 0.5)*ca2;

		glNormal3f(0., 1., 0.);       //Quad 1 facing up
		glVertex3f(x1, 1.0, z1);
		glVertex3f(x2, 1.0, z2);
		glVertex3f(x3, 1.0, z3);
		glVertex3f(x4, 1.0, z4);

		glNormal3f(-sa1, 0.0, -ca1);   //Quad 2 facing inward
		glVertex3f(x1, 0.0, z1);
		glVertex3f(x1, 1.0, z1);
		glNormal3f(-sa2, 0.0, -ca2);
		glVertex3f(x4, 1.0, z4);
		glVertex3f(x4, 0.0, z4);

		glNormal3f(sa1, 0.0, ca1);   //Quad 3 facing outward
		glVertex3f(x2, 1.0, z2);
		glVertex3f(x2, 0.0, z2);
		glNormal3f(sa2, 0.0, ca2);
		glVertex3f(x3, 0.0, z3);
		glVertex3f(x3, 1.0, z3);
	}
	glEnd();
}

//-------- Tracks  ----------------------------------------------------
void tracks()
{
	glColor4f(0.0, 0.0, 0.3, 1.0);
	track(115.0);   //Inner track has radius 115 units
	track(125.0);   //Outer track has radius 125 units
}

//--Draws a character model constructed using GLUT objects ------------------
void drawModel()
{
	glColor3f(1., 0.78, 0.06);		//Head
	glPushMatrix();
		glTranslatef(0, 7.7, 0);
		glutSolidCube(1.4);
	glPopMatrix();

	glColor3f(1., 0., 0.);			//Torso
	glPushMatrix();
		glTranslatef(0, 5.5, 0);
		glScalef(3, 3, 1.4);
		glutSolidCube(1);
	glPopMatrix();

	glColor3f(0., 0., 1.);			//Right leg
	glPushMatrix();
		glTranslatef(-0.8, 4, 0);
		glRotatef(-robotMovement, 1, 0, 0);
		glTranslatef(0.8, -4, 0);
		glTranslatef(-0.8, 2.2, 0);
		glScalef(1, 4.4, 1);
		glutSolidCube(1);
	glPopMatrix();

	glColor3f(0., 0., 1.);			//Left leg
	glPushMatrix();
		glTranslatef(0.8, 4, 0);
		glRotatef(robotMovement, 1, 0, 0);
		glTranslatef(-0.8, -4, 0);
		glTranslatef(0.8, 2.2, 0);
		glScalef(1, 4.4, 1);
		glutSolidCube(1);
	glPopMatrix();

	glColor3f(0., 0., 1.);			//Right arm
	glPushMatrix();
		glTranslatef(-2, 6.5, 0);
		glRotatef(robotMovement, 1, 0, 0);
		glTranslatef(2, -6.5, 0);
		glTranslatef(-2, 5, 0);
		glScalef(1, 4, 1);
		glutSolidCube(1);
	glPopMatrix();

	glColor3f(0., 0., 1.);			//Left arm
	glPushMatrix();
		glTranslatef(2, 6.5, 0);
		glRotatef(-robotMovement, 1, 0, 0);
		glTranslatef(-2, -6.5, 0);
		glTranslatef(2, 5, 0);
		glScalef(1, 4, 1);
		glutSolidCube(1);
	glPopMatrix();
}

//---------------------------------------------------------------------
void initialize(void)
{
	float grey[4] = { 0.2, 0.2, 0.2, 1.0 };
	float white[4] = { 1.0, 1.0, 1.0, 1.0 };

	q = gluNewQuadric();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT0, GL_AMBIENT, grey);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 0.01);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT1, GL_SPECULAR, white);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	gluQuadricDrawStyle(q, GLU_FILL);
	glClearColor(0.0, 0.0, 0.0, 0.0);  //Background colour

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60., 1.0, 10.0, 1000.0);   //Perspective projection

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, 50);
}

//-------------------------------------------------------------------
void display(void)
{
	//float lgt_pos[] = { 0.0f, 50.0f, 0.0f, 1.0f };  //light0 position (directly above the origin)
	//float spot_pos[] = { -10.0f, 14.0f, 0.0f, 1.0f };
	//float spotdir[] = { -1, -1, 0 };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(-80, 50, 250, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glLightfv(GL_LIGHT0, GL_POSITION, lgt_src);   //light position

	floor();
	tracks();

	float shadowMat[16] = { lgt_src[1],0,0,0, -lgt_src[0],0,-lgt_src[2],-1, 0,0,lgt_src[1],0, 0,0,0,lgt_src[1] };

	glEnable(GL_LIGHTING);
	glPushMatrix();											//Draw Actual Object
		glRotatef(theta, 0, 1, 0);
		glTranslatef(0, 1, -120);
		//glLightfv(GL_LIGHT1, GL_POSITION, spot_pos);
		//glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotdir);
		glRotatef(90, 0, 1, 0);
		glScalef(5.0, 5.0, 5.0);
		drawModel();
	glPopMatrix();

	glDisable(GL_LIGHTING); 
	glPushMatrix();											//Draw Shadow Object
		glMultMatrixf(shadowMat);
		glRotatef(theta, 0, 1, 0);
		glTranslatef(0, 1, -120);
		glRotatef(90, 0, 1, 0);
		glScalef(5.0, 5.0, 5.0);
		glColor4f(0.2, 0.2, 0.2, 1.0);
		drawModel();
	glPopMatrix();

	glutSwapBuffers();   //Useful for animation
}

void myTimer(int value)
{
	theta += 2;
	glutPostRedisplay();
	glutTimerFunc(50, myTimer, 0);
}

void robotTimer(int value)
{
	if (movementFlag && robotMovement < 30)
	{
		robotMovement++;
	}
	else if (movementFlag)
	{
		movementFlag = !movementFlag;
		robotMovement--;
	}
	else if (!movementFlag && robotMovement > -30)
	{
		robotMovement--;
	}
	else
	{
		movementFlag = !movementFlag;
		robotMovement++;
	}
	glutPostRedisplay();
	glutTimerFunc(50, robotTimer, 0);
}

//---------------------------------------------------------------------
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Robot World");
	initialize();

	glutDisplayFunc(display);
	glutTimerFunc(50, myTimer, 0);
	glutTimerFunc(50, robotTimer, 0);
	glutMainLoop();
	return 0;
}
