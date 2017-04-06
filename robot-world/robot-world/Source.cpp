//  ========================================================================
//  COSC363: Computer Graphics (2016);  University of Canterbury.
//
//  FILE NAME: Train.cpp
//  See Lab03.pdf for details
//  ========================================================================

//#include <stdlib.h>
#include <math.h>
#include <GL/freeglut.h>
#include "loadTGA.h"

GLUquadric *q;    //Required for creating cylindrical objects
GLuint txId[1];		//Texture ids
double theta = -10.5;
int robotMovement = 0;
bool flag = true;
float lgt_src[4] = { 0.0f, 50.0f, 0.0f, 1.0f };
float eye_x = 12, eye_y = 10, eye_z = 12;		//Initial camera position
float look_x = 12, look_y = 10, look_z = 10;		//"Look-at" point along -z direction
float lookTheta = 0;		//Look angle
int step = 0;		//camera motion
float angle_up_down = 1.0;
int cam_hgt = 150;
float angle_left_right = 0.0;

// jumping robot inits
float jumpHandAngle = 0;
float jumpLegAngle = 0;
int jumpHeight = 0;
bool jumpUpBool = true;

// volleyball robot inits
float volleyballHand = 0;
int volleyballHeight = 0;
bool volleyballUpBool = true;

void loadTexture()
{
	glGenTextures(1, txId); 	// Create 1 texture id

	glBindTexture(GL_TEXTURE_2D, txId[0]);  //Use this texture
	loadTGA("Floor.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}

void floor()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, txId[0]);

	glBegin(GL_QUADS);
	//for (int i = -200; i < 200; i++)
	//{
	//	for (int j = -200; j < 200; j++)
	//	{
	//		glVertex3f(i, 0.0, j);
	//		glVertex3f(i, 0.0, j++);
	//		glVertex3f(i + 1, 0.0, j++);
	//		glVertex3f(i + 1, 0.0, j);
	//	}
	//}

		glTexCoord2f(0, 150); glVertex3f(-200, 0, -200);
		glTexCoord2f(0, 0); glVertex3f(-200, 0, 200);
		glTexCoord2f(150, 0); glVertex3f(200, 0, 200);
		glTexCoord2f(150, 150); glVertex3f(200, 0, -200);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

//-- Ground Plane --------------------------------------------------------
//void floor()
//{
//	glEnable(GL_TEXTURE_2D);
//	glBindTexture(GL_TEXTURE_2D, txId[0]);
//
//	float white[4] = { 1., 1., 1., 1. };
//	float black[4] = { 0 };
//	glColor4f(0.7, 0.7, 0.7, 1.0);  //The floor is gray in colour
//	glNormal3f(0.0, 1.0, 0.0);
//
//	glMaterialfv(GL_FRONT, GL_SPECULAR, black);
//
//	//The floor is made up of several tiny squares on a 200x200 grid. Each square has a unit size.
//	glBegin(GL_QUADS);
//	for (int i = -200; i < 200; i++)
//	{
//		for (int j = -200; j < 200; j++)
//		{
//			glVertex3f(i, 0.0, j);
//			glVertex3f(i, 0.0, j + 1);
//			glVertex3f(i + 1, 0.0, j + 1);
//			glVertex3f(i + 1, 0.0, j);
//		}
//	}
//	glEnd();
//	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
//
//}

//--Draws a character model constructed using GLUT objects ------------------
void drawModel(void)
{
	glDisable(GL_TEXTURE_2D);

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

void myTimer(int value)
{
	theta += 2;
	glutPostRedisplay();
	glutTimerFunc(50, myTimer, 0);
}

void robotTimer(int value)
{
	if (flag && robotMovement < 30)
	{
		robotMovement++;
	}
	else if (flag)
	{
		flag = !flag;
		robotMovement--;
	}
	else if (!flag && robotMovement > -30)
	{
		robotMovement--;
	}
	else
	{
		flag = !flag;
		robotMovement++;
	}
	glutPostRedisplay();
	glutTimerFunc(50, robotTimer, 0);
}

void drawJumpingRobot(void)
{
	glDisable(GL_TEXTURE_2D);

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
		glRotatef(jumpLegAngle, 0, 0, 1);
		glTranslatef(0.8, -4, 0);
		glTranslatef(-0.8, 2.2, 0);
		glScalef(1, 4.4, 1);
		glutSolidCube(1);
	glPopMatrix();

	glColor3f(0., 0., 1.);			//Left leg
	glPushMatrix();
		glTranslatef(0.8, 4, 0);
		glRotatef(-jumpLegAngle, 0, 0, 1);
		glTranslatef(-0.8, -4, 0);
		glTranslatef(0.8, 2.2, 0);
		glScalef(1, 4.4, 1);
		glutSolidCube(1);
	glPopMatrix();

	glColor3f(0., 0., 1.);			//Right arm
	glPushMatrix();
		glTranslatef(-2, 6.5, 0);
		glRotatef(jumpHandAngle, 0, 0, 1);
		glTranslatef(2, -6.5, 0);
		glTranslatef(-2, 5, 0);
		glScalef(1, 4, 1);
		glutSolidCube(1);
	glPopMatrix();

	glColor3f(0., 0., 1.);			//Left arm
	glPushMatrix();
		glTranslatef(2, 6.5, 0);
		glRotatef(-jumpHandAngle, 0, 0, 1);
		glTranslatef(-2, -6.5, 0);
		glTranslatef(2, 5, 0);
		glScalef(1, 4, 1);
		glutSolidCube(1);
	glPopMatrix();
}

void drawVolleyballRobot(void)
{
	glDisable(GL_TEXTURE_2D);

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
	glRotatef(jumpLegAngle, 0, 0, 1);
	glTranslatef(0.8, -4, 0);
	glTranslatef(-0.8, 2.2, 0);
	glScalef(1, 4.4, 1);
	glutSolidCube(1);
	glPopMatrix();

	glColor3f(0., 0., 1.);			//Left leg
	glPushMatrix();
	glTranslatef(0.8, 4, 0);
	glRotatef(-jumpLegAngle, 0, 0, 1);
	glTranslatef(-0.8, -4, 0);
	glTranslatef(0.8, 2.2, 0);
	glScalef(1, 4.4, 1);
	glutSolidCube(1);
	glPopMatrix();

	glColor3f(0., 0., 1.);			//Right arm
	glPushMatrix();
	glTranslatef(-2, 6.5, 0);
	glRotatef(jumpHandAngle, 0, 0, 1);
	glTranslatef(2, -6.5, 0);
	glTranslatef(-2, 5, 0);
	glScalef(1, 4, 1);
	glutSolidCube(1);
	glPopMatrix();

	glColor3f(0., 0., 1.);			//Left arm
	glPushMatrix();
	glTranslatef(2, 6.5, 0);
	glRotatef(-jumpHandAngle, 0, 0, 1);
	glTranslatef(-2, -6.5, 0);
	glTranslatef(2, 5, 0);
	glScalef(1, 4, 1);
	glutSolidCube(1);
	glPopMatrix();
}

void jumpTimer(int value)
{
	if (jumpUpBool && jumpHeight < 10)
	{
		jumpHeight++;
	}
	else if (jumpUpBool)
	{
		jumpUpBool = !jumpUpBool;
	}
	else if (!jumpUpBool && jumpHeight > 0)
	{
		jumpHeight--;
	}
	else if (!jumpUpBool)
	{
		jumpUpBool = !jumpUpBool;
	}

	if (!jumpUpBool && jumpHandAngle < 0)
	{
		jumpHandAngle += 10;
		jumpLegAngle += 5;
	}
	else if (jumpUpBool && jumpHandAngle > -180)
	{
		jumpHandAngle -= 10;
		jumpLegAngle -= 5;
	}
	glutPostRedisplay();
	glutTimerFunc(50, jumpTimer, 0);
}

//---------------------------------------------------------------------
void initialize(void)
{
	loadTexture();
	glEnable(GL_TEXTURE_2D);

	float grey[4] = { 0.2, 0.2, 0.2, 1.0 };
	float white[4] = { 1.0, 1.0, 1.0, 1.0 };

	q = gluNewQuadric();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, grey);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);

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
	float dir_x = -sin(lookTheta), dir_y = 0, dir_z = -cos(lookTheta);
	float d = 2;
	glRotatef(angle_up_down, 0.0, 1.0, 0.0);

	//if (eye_x + dir_x * step + dir_x * d < 14 && eye_x + dir_x * step + dir_x * d > -14 && eye_z + dir_z * step + dir_z * d < 14 && eye_z + dir_z * step + dir_z * d > -14)
	//{
		eye_x += dir_x * step;
		eye_z += dir_z * step;
	//}

	look_x = eye_x + dir_x * d;
	look_y = eye_y;
	look_z = eye_z + dir_z * d;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(eye_x, eye_y, eye_z, look_x, look_y, look_z, 0, 1, 0);

	glLightfv(GL_LIGHT0, GL_POSITION, lgt_src);   //light position

	floor();

	float shadowMat[16] = { lgt_src[1],0,0,0, -lgt_src[0],0,-lgt_src[2],-1, 0,0,lgt_src[1],0, 0,0,0,lgt_src[1] };

	glEnable(GL_LIGHTING);
	glPushMatrix();											//Draw Actual Object
		glRotatef(theta, 0, 1, 0);
		glTranslatef(0, 1, -50);
		glRotatef(90, 0, 1, 0);
		drawModel();
	glPopMatrix();

	glDisable(GL_LIGHTING);
	glPushMatrix();											//Draw Shadow Object
		glMultMatrixf(shadowMat);
		glRotatef(theta, 0, 1, 0);
		glTranslatef(0, 1, -120);
		glRotatef(90, 0, 1, 0);
		glColor4f(0.2, 0.2, 0.2, 1.0);
		drawModel();
	glPopMatrix();

	glEnable(GL_LIGHTING);
	glPushMatrix();
		glTranslatef(0, 0, -20);		// put the robot in place
		glTranslatef(0, jumpHeight, 0);		// make the robot jump
		drawJumpingRobot();
	glPopMatrix();

	glutSwapBuffers();   //Useful for animation
}

//--------------------------------------------------------------------------------
void special(int key, int x, int y)
{
	step = 0;
	if (key == GLUT_KEY_LEFT) lookTheta += 0.1;   //in radians
	else if (key == GLUT_KEY_RIGHT) lookTheta -= 0.1;
	else if (key == GLUT_KEY_DOWN) step = -1;
	else if (key == GLUT_KEY_UP) step = 1;

	glutPostRedisplay();
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
	glutTimerFunc(50, jumpTimer, 0);
	glutSpecialFunc(special);
	glutMainLoop();
	return 0;
}
