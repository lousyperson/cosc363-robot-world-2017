//  ========================================================================
//
//  COSC363: Computer Graphics Assignment 1
//
//  Author: Zhi You Tan (zyt10)
//
//  ========================================================================

// from https://www.youtube.com/watch?v=imCNAWMC1Xs

//#include <stdlib.h>
#include <math.h>
#include <GL/freeglut.h>
#include "loadTGA.h"
#include <string>

GLUquadric *q;    //Required for creating cylindrical objects
GLuint txId[9];		//Texture ids
float eye_x = -35.0f, eye_y = 10.0f, eye_z = 55.0f;		//Initial camera position
float look_x = 0.0f, look_y = 10.0f, look_z = 10.0f;		//"Look-at" point along -z direction
float lookTheta = -0.174f;		//Look angle
int step = 0;		//camera motion
int cam_hgt = 150;
float angle_left_right = 0.0f;

// worker robot inits
float theta = 0.0f;
float workerMovement = 0.0f;
bool workerFlag = true;
bool workerForward = true;

// doing work
bool stop = false;
float swingAngle = -1.0f;
int count = 0;
bool done = false;

// jumping robot inits
float jumpHandAngle = 0.0f;
float jumpLegAngle = 0.0f;
int jumpHeight = 0;
bool jumpUpBool = true;

// dog inits
float legLeft = 0.0f;
float dogWalk = 0.0f;
bool legLeftBool = true;

// bb8 inits
float bb8Rotation = 0.0f;
float bb8Movement = 0.0f;
bool bb8FrontBool = true;

// view mode
bool freeView = true;

void loadTexture(void)
{
	glGenTextures(9, txId); 	// Create 1 texture id

	glBindTexture(GL_TEXTURE_2D, txId[0]);  //Use this texture name for the following OpenGL texture
	loadTGA("bb8.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, txId[1]);  //Use this texture name for the following OpenGL texture
	loadTGA("skybox/tropday_down.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, txId[2]);  //Use this texture name for the following OpenGL texture
	loadTGA("skybox/tropday_back.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, txId[3]);  //Use this texture name for the following OpenGL texture
	loadTGA("skybox/tropday_front.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, txId[4]);  //Use this texture name for the following OpenGL texture
	loadTGA("skybox/tropday_left.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, txId[5]);  //Use this texture name for the following OpenGL texture
	loadTGA("skybox/tropday_right.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, txId[6]);  //Use this texture name for the following OpenGL texture
	loadTGA("skybox/tropday_up.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, txId[7]);  //Use this texture name for the following OpenGL texture
	loadTGA("Gold-Nugget.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, txId[8]);  //Use this texture name for the following OpenGL texture
	loadTGA("silver.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void drawSkyBox(void)
{
	float size = 150.;
	float floorHeight = -0.1;

	glDisable(GL_LIGHTING);		//turn off lighting, when making the skybox
//	glDisable(GL_DEPTH_TEST);		//turn off depth texting
	glEnable(GL_TEXTURE_2D);		//and turn on texturing
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glColor4f(1, 1, 1, 1.0);

	//glBindTexture(GL_TEXTURE_2D, txId[1]);		// replaced by floor()
	//glNormal3f(0.0, 1.0, 0.0);
	//glBegin(GL_QUADS);   		 //down
	//glTexCoord2f(0, 0); glVertex3f(-size, floorHeight, size);
	//glTexCoord2f(1, 0); glVertex3f(size, floorHeight, size);
	//glTexCoord2f(1, 1); glVertex3f(size, floorHeight, -size);
	//glTexCoord2f(0, 1); glVertex3f(-size, floorHeight, -size);
	//glEnd();

	glBindTexture(GL_TEXTURE_2D, txId[2]);
	glNormal3f(0.0, 0.0, -1.0);
	glBegin(GL_QUADS);   		 //back
	glTexCoord2f(0, 0); glVertex3f(size, floorHeight, size);
	glTexCoord2f(1, 0); glVertex3f(-size, floorHeight, size);
	glTexCoord2f(1, 1); glVertex3f(-size, size, size);
	glTexCoord2f(0, 1); glVertex3f(size, size, size);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, txId[3]);
	glNormal3f(0.0, 0.0, 1.0);
	glBegin(GL_QUADS);   		 //front
	glTexCoord2f(0, 0); glVertex3f(size, floorHeight, -size);
	glTexCoord2f(1, 0); glVertex3f(size, size, -size);
	glTexCoord2f(1, 1); glVertex3f(-size, size, -size);
	glTexCoord2f(0, 1); glVertex3f(-size, floorHeight, -size);
	
	glEnd();

	glBindTexture(GL_TEXTURE_2D, txId[4]);
	glNormal3f(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);   		 //left
	glTexCoord2f(0, 0); glVertex3f(size, floorHeight, -size);
	glTexCoord2f(1, 0); glVertex3f(size, floorHeight, size);
	glTexCoord2f(1, 1); glVertex3f(size, size, size);
	glTexCoord2f(0, 1); glVertex3f(size, size, -size);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, txId[5]);
	glNormal3f(-1.0, 0.0, 0.0);
	glBegin(GL_QUADS);   		 //right
	glTexCoord2f(0, 0); glVertex3f(-size, floorHeight, size);
	glTexCoord2f(1, 0); glVertex3f(-size, floorHeight, -size);
	glTexCoord2f(1, 1); glVertex3f(-size, size, -size);
	glTexCoord2f(0, 1); glVertex3f(-size, size, size);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, txId[6]);
	glNormal3f(0.0, -1.0, 0.0);
	glBegin(GL_QUADS);   		 //up
	glTexCoord2f(0, 0); glVertex3f(size, size, size);
	glTexCoord2f(1, 0); glVertex3f(-size, size, size);
	glTexCoord2f(1, 1); glVertex3f(-size, size, -size);
	glTexCoord2f(0, 1); glVertex3f(size, size, -size);
	
	glEnd();

	glEnable(GL_LIGHTING);
//	glEnable(GL_DEPTH_TEST);
}

void floor()
{
	float floorHeight = -0.2f;
	float size = 150.0f;

	float white[4] = { 1., 1., 1., 1. };
	float black[4] = { 0 };
	glColor4f(0.560, 0.560, 0.419, 1.0);  //The floor is brown in colour
	glNormal3f(0.0, 1.0, 0.0);

	glMaterialfv(GL_FRONT, GL_SPECULAR, black);

	//The floor is made up of several tiny squares on a 200x200 grid. Each square has a unit size.
	glBegin(GL_QUADS);
	for (int i = -200; i < 200; i++)
	{
		for (int j = -200; j < 200; j++)
		{
			glVertex3f(i, floorHeight, j);
			glVertex3f(i, floorHeight, j + 1);
			glVertex3f(i + 1, floorHeight, j + 1);
			glVertex3f(i + 1, floorHeight, j);
		}
	}
	glEnd();
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
}

//--Draws a character model constructed using GLUT objects ------------------
void drawWorkerModel(bool isShadow)
{
	glDisable(GL_TEXTURE_2D);

	if (isShadow) glColor3f(0.25, 0.25, 0.25);
	else glColor3f(0.078, 1, 0.258);		//Headlight
	glPushMatrix();
		glTranslatef(0, 6, -0.8);
		glRotatef(45, 1, 0, 0);
		glutSolidCube(0.5);
	glPopMatrix();

	if (isShadow) glColor3f(0.25, 0.25, 0.25);
	else glColor3f(1., 0.78, 0.06);		//Head
	glPushMatrix();
		glTranslatef(0, 5.5, 0);
		glutSolidCube(1.4);
	glPopMatrix();

	if (isShadow) glColor3f(0.25, 0.25, 0.25);
	else glColor3f(1., 0., 0.);			//Torso
	glPushMatrix();
		glTranslatef(0, 3.3, 0);
		glScalef(3, 3, 1.4);
		glutSolidCube(1);
	glPopMatrix();

	if (isShadow) glColor3f(0.25, 0.25, 0.25);
	else glColor3f(0., 0., 1.);			//Right leg
	glPushMatrix();
		glTranslatef(-0.8, 1.8, 0);
		glRotatef(-workerMovement, 1, 0, 0);
		glTranslatef(0.8, -1.8, 0);
		glTranslatef(-0.8, 0, 0);
		glScalef(1, 4.4, 1);
		glutSolidCube(1);
	glPopMatrix();
		
	glPushMatrix();		//Left leg
		glTranslatef(0.8, 1.8, 0);
		glRotatef(workerMovement, 1, 0, 0);
		glTranslatef(-0.8, -1.8, 0);
		glTranslatef(0.8, 0, 0);
		glScalef(1, 4.4, 1);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();		//Right arm
		glTranslatef(-2, 4.3, 0);
		glRotatef(workerMovement, 1, 0, 0);
		glTranslatef(2, -4.3, 0);
		glTranslatef(-2, 2.8, 0);
		glScalef(1, 4, 1);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();		//Left arm
		glTranslatef(2, 4.3, 0);
		glRotatef(-workerMovement, 1, 0, 0);
		glRotatef(swingAngle, 1, 0, 0);
		glTranslatef(-2, -4.3, 0);
		glTranslatef(2, 2.8, 0);
		glScalef(1, 4, 1);
		glutSolidCube(1);
	glPopMatrix();

	if (isShadow) glColor3f(0.25, 0.25, 0.25);
	else glColor3f(0.545, 0.270, 0.074);			//Pickaxe
	glPushMatrix();
	glTranslatef(2, 4.3, 0);
	glRotatef(-workerMovement, 1, 0, 0);
	glRotatef(swingAngle, 1, 0, 0);
	glTranslatef(-2, -4.3, 0);
	glTranslatef(2, 1, -2.5);
	glScalef(1, 1, 8);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(2, 4.3, 0);
		glRotatef(-workerMovement, 1, 0, 0);
		glRotatef(swingAngle, 1, 0, 0);
		glTranslatef(-2, -4.3, 0);
		glTranslatef(2, 1, -5);
		glRotatef(90, 1, 0, 0);
		glutSolidCone(0.5, 3, 36, 17);
	glPopMatrix();
}

void swingPickaxe(int value)
{
	if (stop)
	{
		//cout << "done swing pickaxe" + to_string(swingAngle) + '\n';
		workerMovement = 0.0f;		// to pause the rest of body parts

		if (!done && swingAngle < 0.0f)
		{
			swingAngle = 180.0f;
			swingAngle -= 20.0f;
		}
		else if (!done && swingAngle > 0.0f)
		{
			swingAngle -= 20.0f;
		}
		else if (!done)
		{
			done = !done;
			swingAngle = -1.0f;
			stop = !stop;
		}
		else if (done && swingAngle < 0.0f)
		{
			swingAngle = 180.0f;
			swingAngle -= 20.0f;
		}
		else if (done && swingAngle > 0.0f)
		{
			swingAngle -= 20.0f;
		}
		else if (done)
		{
			done = !done;
			swingAngle = -1.0f;
			stop = !stop;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(50, swingPickaxe, 0);
}

void workerTimer(int value)
{
	if (!stop)
	{
		//cout << "done worker timer" + to_string(theta) + '\n';

		// arc the robot is walking
		if (workerForward && theta < 45)
		{
			theta += 1;
		}
		else if (workerForward)
		{
			stop = !stop;
			workerForward = !workerForward;
		}
		else if (!workerForward && theta > 0)
		{
			theta -= 1;
		}
		else if (!workerForward)
		{
			stop = !stop;
			workerForward = !workerForward;
		}

		// just hands and legs swinging
		if (workerFlag && workerMovement < 30)
		{
			workerMovement++;
		}
		else if (workerFlag)
		{
			workerFlag = !workerFlag;
			workerMovement--;
		}
		else if (!workerFlag && workerMovement > -30)
		{
			workerMovement--;
		}
		else
		{
			workerFlag = !workerFlag;
			workerMovement++;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(50, workerTimer, 0);
}

void drawJumpingRobot(bool isShadow)
{
	glDisable(GL_TEXTURE_2D);

	if (isShadow) glColor3f(0.25, 0.25, 0.25);
	else glColor3f(1., 0.78, 0.06);		//Head
	glPushMatrix();
		glTranslatef(0, 7.7, 0);
		glutSolidCube(1.4);
	glPopMatrix();

	if (isShadow) glColor3f(0.25, 0.25, 0.25);
	else glColor3f(1., 0., 0.);			//Torso
	glPushMatrix();
		glTranslatef(0, 5.5, 0);
		glScalef(3, 3, 1.4);
		glutSolidCube(1);
	glPopMatrix();

	if (isShadow) glColor3f(0.25, 0.25, 0.25);
	else glColor3f(0., 0., 1.);			//Right leg
	glPushMatrix();
		glTranslatef(-0.8, 4, 0);
		glRotatef(jumpLegAngle, 0, 0, 1);
		glTranslatef(0.8, -4, 0);
		glTranslatef(-0.8, 2.2, 0);
		glScalef(1, 4.4, 1);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();		//Left leg
		glTranslatef(0.8, 4, 0);
		glRotatef(-jumpLegAngle, 0, 0, 1);
		glTranslatef(-0.8, -4, 0);
		glTranslatef(0.8, 2.2, 0);
		glScalef(1, 4.4, 1);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();		//Right arm
		glTranslatef(-2, 6.5, 0);
		glRotatef(jumpHandAngle, 0, 0, 1);
		glTranslatef(2, -6.5, 0);
		glTranslatef(-2, 5, 0);
		glScalef(1, 4, 1);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();		//Left arm
		glTranslatef(2, 6.5, 0);
		glRotatef(-jumpHandAngle, 0, 0, 1);
		glTranslatef(-2, -6.5, 0);
		glTranslatef(2, 5, 0);
		glScalef(1, 4, 1);
		glutSolidCube(1);
	glPopMatrix();
}

void drawDog(bool isShadow)
{
	glDisable(GL_TEXTURE_2D);

	if (isShadow) glColor3f(0.25, 0.25, 0.25);
	else glColor3f(1., 0.78, 0.06);		//Head
	glPushMatrix();
		glTranslatef(0, 4, 4);
		glScalef(1, 1, 2);
		glutSolidCube(1);
	glPopMatrix();

	if (isShadow) glColor3f(0.25, 0.25, 0.25);
	else glColor3f(1., 0., 0.);			//Torso
	glPushMatrix();
		glTranslatef(0, 2.5, 0);
		glScalef(3, 2, 7);
		glutSolidCube(1);
	glPopMatrix();

	if (isShadow) glColor3f(0.25, 0.25, 0.25);
	else glColor3f(0., 0., 1.);			//Left front leg
	glPushMatrix();
		glTranslatef(-0.5, 3, 2.5);
		glRotatef(legLeft, 1, 0, 0);
		glTranslatef(0.5, -3, -2.5);
		glTranslatef(-1, 0, 3);
		glScalef(1, 3, 1);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();		//Right front leg
		glTranslatef(0.5, 3, 2.5);
		glRotatef(-legLeft, 1, 0, 0);
		glTranslatef(-0.5, -3, -2.5);
		glTranslatef(1, 0, 3);
		glScalef(1, 3, 1);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();		//Left rear leg
		glTranslatef(-0.5, 3, -2.5);
		glRotatef(-legLeft, 1, 0, 0);
		glTranslatef(0.5, -3, 2.5);
		glTranslatef(-1, 0, -3);
		glScalef(1, 3, 1);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();		//Right rear leg
		glTranslatef(0.5, 3, -2.5);
		glRotatef(legLeft, 1, 0, 0);
		glTranslatef(-0.5, -3, 2.5);
		glTranslatef(1, 0, -3);
		glScalef(1, 3, 1);
		glutSolidCube(1);
	glPopMatrix();
}

void dogTimer(int value)
{
	dogWalk++;		// make dog walk in circle
	int dogAngle = 30;

	if (!legLeftBool && legLeft < dogAngle)
	{
		legLeft++;
		jumpLegAngle++;
	}
	else if (!legLeftBool)
	{
		legLeftBool = !legLeftBool;
	}
	else if (legLeftBool && legLeft > -dogAngle)
	{
		legLeft--;
		jumpLegAngle--;
	}
	else if (legLeftBool)
	{
		legLeftBool = !legLeftBool;
	}
	glutPostRedisplay();
	glutTimerFunc(50, dogTimer, 0);
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

void drawBB8(bool isShadow)
{
	if (isShadow) glColor3f(0.25, 0.25, 0.25);
	else
	{
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glEnable(GL_TEXTURE_2D);
		gluQuadricTexture(q, GL_TRUE);
		glBindTexture(GL_TEXTURE_2D, txId[0]);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}

	glPushMatrix();		// BB8 Main Ball
		glTranslatef(0, 0, bb8Movement);
		glRotatef(-bb8Rotation, 0.0, 1.0, 0.0);
		glTranslatef(0.0, 3.0, 0.0);
		glRotatef(-120, 1, 0, 0);
		gluSphere(q, 2.5, 36, 17);
	glPopMatrix();

	glPushMatrix();		// BB8 Head
		glTranslatef(0, 0, bb8Movement);
		glTranslatef(0.0, 5.5, 0.0);
		glRotatef(-90, 1, 0, 0);
		gluSphere(q, 1.5, 36, 17);
	glPopMatrix();

	if (!isShadow) glDisable(GL_TEXTURE_2D);
}

void bb8Timer(int value)
{
	bb8Rotation+=10;		// continuously spinning
	if (bb8FrontBool && bb8Movement < 30)
	{
		bb8Movement++;
	}
	else if (bb8FrontBool)
	{
		bb8FrontBool = !bb8FrontBool;
	}
	else if (!bb8FrontBool && bb8Movement > -30)
	{
		bb8Movement--;
	}
	else if (!bb8FrontBool)
	{
		bb8FrontBool = !bb8FrontBool;
	}
	glutPostRedisplay();
	glutTimerFunc(50, bb8Timer, 0);
}

void drawOres(bool isShadow)
{
	if (isShadow) glColor3f(0.25, 0.25, 0.25);
	else
	{
		glColor4f(1.0, 1.0, 1.0, 1.0);        //Base colour
		glEnable(GL_TEXTURE_2D);
		gluQuadricTexture(q, GL_TRUE);
		glBindTexture(GL_TEXTURE_2D, txId[7]);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}

	glPushMatrix();		// Gold nugget
	glRotatef(53, 0, 1, 0);
	glTranslatef(0, 1, -50);
	gluSphere(q, 2.5, 36, 17);
	glPopMatrix();

	if (isShadow) glColor3f(0.25, 0.25, 0.25);
	else
	{
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glEnable(GL_TEXTURE_2D);
		gluQuadricTexture(q, GL_TRUE);
		glBindTexture(GL_TEXTURE_2D, txId[8]);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}

	glPushMatrix();		// Silver ore
	glRotatef(-8, 0, 1, 0);
	glTranslatef(0, 1, -50);
	gluSphere(q, 2.5, 36, 17);
	glPopMatrix();

	if (!isShadow) glDisable(GL_TEXTURE_2D);
}

//---------------------------------------------------------------------
void initialize(void)
{
	loadTexture();
	glEnable(GL_TEXTURE_2D);

	float grey[4] = { 0.2, 0.2, 0.2, 1.0 };
	float white[4] = { 1.0, 1.0, 1.0, 1.0 };
	//float green[4] = { 0.0, 1.0, 0.0, 1.0 };

	q = gluNewQuadric();

	glEnable(GL_LIGHTING);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, 50);

	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, grey);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);

	glEnable(GL_LIGHT1);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 10);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT1, GL_SPECULAR, white);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	gluQuadricDrawStyle(q, GLU_FILL);
	gluQuadricNormals(q, GLU_SMOOTH);
	glClearColor(0.0, 0.0, 0.0, 0.0);  //Background colour

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60., 1.0, 10.0, 1000.0);   //Perspective projection

	//initSkybox();
}

//-------------------------------------------------------------------
void display(void)
{
	float lgt_src[4] = { 0.0f, 200.0f, 0.0f, 1.0f };
	float spot_pos[] = { 0.0f, 6.0f, -0.8f, 1.0f };
	float spotdir[] = { 0.0f, -1.0f, -1.0f, 1.0f };

	// camera position and limit the movement within skybox
	float dir_x = -sin(lookTheta), dir_y = 0, dir_z = -cos(lookTheta);
	float d = 2;
	if (eye_x + dir_x * step + dir_x * d < 200 && eye_x + dir_x * step + dir_x * d > -200 && eye_z + dir_z * step + dir_z * d < 200 && eye_z + dir_z * step + dir_z * d > -200)
	{
		eye_x += dir_x * step;
		eye_z += dir_z * step;
	}
	look_x = eye_x + dir_x * d;
	look_y = eye_y;
	look_z = eye_z + dir_z * d;

	// OpenGL Lighting
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (freeView)
	{
		gluLookAt(eye_x, eye_y, eye_z, look_x, look_y, look_z, 0, 1, 0);
	}
	else
	{
		gluLookAt(0, 8 + jumpHeight, -90,
				  0, 8 + jumpHeight, -89,
				  0, 1, 0);
	}

	glLightfv(GL_LIGHT0, GL_POSITION, lgt_src);   // light position

	floor();
	drawSkyBox();

	float shadowMat[16] = { lgt_src[1],0,0,0, -lgt_src[0],0,-lgt_src[2],-1, 0,0,lgt_src[1],0, 0,0,0,lgt_src[1] };

	glEnable(GL_LIGHTING);		//Draw Worker Robot
	glPushMatrix();
		if (done)
		{
			glRotatef(theta, 0, 1, 0);
			glTranslatef(0, 1, -50);
			glRotatef(180, 0, 1, 0);
			glTranslatef(0, -1, 50);
			glRotatef(-theta, 0, 1, 0);
		}
		glRotatef(theta, 0, 1, 0);
		glTranslatef(0, 1, -50);
		glRotatef(90, 0, 1, 0);		// to face where robot is moving
		glLightfv(GL_LIGHT1, GL_POSITION, spot_pos);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotdir);
		drawWorkerModel(false);
	glPopMatrix();

	glDisable(GL_LIGHTING);		//Draw Worker Robot Shadow
	glPushMatrix();
		glMultMatrixf(shadowMat);
		if (done)
		{
			glRotatef(theta, 0, 1, 0);
			glTranslatef(0, 1, -50);
			glRotatef(180, 0, 1, 0);
			glTranslatef(0, -1, 50);
			glRotatef(-theta, 0, 1, 0);
		}
		glRotatef(theta, 0, 1, 0);
		glTranslatef(0, 1, -50);
		glRotatef(90, 0, 1, 0);
		glColor4f(0.2, 0.2, 0.2, 1.0);
		drawWorkerModel(true);
	glPopMatrix();

	glEnable(GL_LIGHTING);		// Draw jumping robot
	glPushMatrix();
		glTranslatef(0, 0, -90);		// put the robot in place
		glTranslatef(0, jumpHeight, 0);		// make the robot jump
		drawJumpingRobot(false);
	glPopMatrix();

	glDisable(GL_LIGHTING);		//Draw jumping robot shadow
	glPushMatrix();
		glMultMatrixf(shadowMat);
		glTranslatef(0, 0, -90);
		glTranslatef(0, jumpHeight, 0);
		drawJumpingRobot(true);
	glPopMatrix();

	glEnable(GL_LIGHTING);		//Draw dog
	glPushMatrix();
		glRotatef(-dogWalk, 0, 1, 0);
		glTranslatef(0, 1, -20);
		glRotatef(90, 0, 1, 0);		// to face where robot is moving
		drawDog(false);
	glPopMatrix();

	glDisable(GL_LIGHTING);		//Draw dog shadow
	glPushMatrix();
		glMultMatrixf(shadowMat);
		glRotatef(-dogWalk, 0, 1, 0);
		glTranslatef(0, 1, -20);
		glRotatef(90, 0, 1, 0);
		drawDog(true);
	glPopMatrix();

	glEnable(GL_LIGHTING);		//Draw bb8
	glPushMatrix();
		drawBB8(false);
	glPopMatrix();

	glDisable(GL_LIGHTING);		//Draw bb8 shadow
	glPushMatrix();
		glMultMatrixf(shadowMat);
		drawBB8(true);
	glPopMatrix();

	glEnable(GL_LIGHTING);		// Draw ores
	glPushMatrix();
		drawOres(false);
	glPopMatrix();

	glDisable(GL_LIGHTING);		//Draw ores shadow
	glPushMatrix();
		glMultMatrixf(shadowMat);
		drawOres(true);
	glPopMatrix();

	glEnable(GL_LIGHTING);

	glutSwapBuffers();   //Useful for animation
}

//--------------------------------------------------------------------------------
void special(int key, int x, int y)
{
	step = 0;

	if (freeView)
	{
		if (key == GLUT_KEY_LEFT) lookTheta += (5.0 * 3.14 / 180.0);   //in radians
		else if (key == GLUT_KEY_RIGHT) lookTheta -= (5.0 * 3.14 / 180.0);
		else if (key == GLUT_KEY_DOWN) step = -1;
		else if (key == GLUT_KEY_UP) step = 1;
	}

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == ' ')
	{
		freeView = !freeView;
	}
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
	glutTimerFunc(50, workerTimer, 0);		// temp to see forehead pos
	glutTimerFunc(50, swingPickaxe, 0);
	glutTimerFunc(50, jumpTimer, 0);
	glutTimerFunc(50, dogTimer, 0);
	glutTimerFunc(50, bb8Timer, 0);
	glutSpecialFunc(special);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
