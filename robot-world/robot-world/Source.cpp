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

GLUquadric *q;    //Required for creating cylindrical objects
GLuint txId[7];		//Texture ids
double theta = -10.5;
float robotMovement = 0.0;
bool flag = true;
float lgt_src[4] = { 0.0f, 200.0f, 0.0f, 1.0f };
float eye_x = 0, eye_y = 10, eye_z = 12;		//Initial camera position
float look_x = 0, look_y = 10, look_z = 10;		//"Look-at" point along -z direction
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

// dog inits
float legLeft = 0;
bool legLeftBool = true;
float dogWalk = 0;

// bb8 inits
float bb8Rotation = 0;
float bb8Movement = 0;
bool bb8FrontBool = true;

void loadTexture(void)
{
	glGenTextures(7, txId); 	// Create 1 texture id

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

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
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
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glColor4f(1, 1, 1, 1.0);

	glBindTexture(GL_TEXTURE_2D, txId[1]);
	glNormal3f(0.0, 1.0, 0.0);
	glBegin(GL_QUADS);   		 //down
	glTexCoord2f(0, 0); glVertex3f(-size, floorHeight, size);
	glTexCoord2f(1, 0); glVertex3f(size, floorHeight, size);
	glTexCoord2f(1, 1); glVertex3f(size, floorHeight, -size);
	glTexCoord2f(0, 1); glVertex3f(-size, floorHeight, -size);
	glEnd();

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
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, txId[1]);

	glBegin(GL_QUADS);
		glTexCoord2f(0, 150); glVertex3f(-200, 0, -200);
		glTexCoord2f(0, 0); glVertex3f(-200, 0, 200);
		glTexCoord2f(150, 0); glVertex3f(200, 0, 200);
		glTexCoord2f(150, 150); glVertex3f(200, 0, -200);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

//--Draws a character model constructed using GLUT objects ------------------
void drawRunningModel(bool isShadow)
{
	glDisable(GL_TEXTURE_2D);

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
		glRotatef(-robotMovement, 1, 0, 0);
		glTranslatef(0.8, -1.8, 0);
		glTranslatef(-0.8, 0, 0);
		glScalef(1, 4.4, 1);
		glutSolidCube(1);
	glPopMatrix();
		
	glPushMatrix();		//Left leg
		glTranslatef(0.8, 1.8, 0);
		glRotatef(robotMovement, 1, 0, 0);
		glTranslatef(-0.8, -1.8, 0);
		glTranslatef(0.8, 0, 0);
		glScalef(1, 4.4, 1);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();		//Right arm
		glTranslatef(-2, 4.3, 0);
		glRotatef(robotMovement, 1, 0, 0);
		glTranslatef(2, -4.3, 0);
		glTranslatef(-2, 2.8, 0);
		glScalef(1, 4, 1);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();		//Left arm
		glTranslatef(2, 4.3, 0);
		glRotatef(-robotMovement, 1, 0, 0);
		glTranslatef(-2, -4.3, 0);
		glTranslatef(2, 2.8, 0);
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
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
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
	gluQuadricDrawStyle(q, GLU_FILL);  //used
	gluQuadricNormals(q, GLU_SMOOTH);  //used
	glClearColor(0.0, 0.0, 0.0, 0.0);  //Background colour

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60., 1.0, 10.0, 1000.0);   //Perspective projection

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, 50);

	//initSkybox();
}

//-------------------------------------------------------------------
void display(void)
{
	float dir_x = -sin(lookTheta), dir_y = 0, dir_z = -cos(lookTheta);
	float d = 2;
	glRotatef(angle_up_down, 0.0, 1.0, 0.0);

	if (eye_x + dir_x * step + dir_x * d < 200 && eye_x + dir_x * step + dir_x * d > -200 && eye_z + dir_z * step + dir_z * d < 200 && eye_z + dir_z * step + dir_z * d > -200)
	{
		eye_x += dir_x * step;
		eye_z += dir_z * step;
	}

	look_x = eye_x + dir_x * d;
	look_y = eye_y;
	look_z = eye_z + dir_z * d;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(eye_x, eye_y, eye_z, look_x, look_y, look_z, 0, 1, 0);

	glLightfv(GL_LIGHT0, GL_POSITION, lgt_src);   //light position

	//floor();
	//drawCube();
	drawSkyBox();

	float shadowMat[16] = { lgt_src[1],0,0,0, -lgt_src[0],0,-lgt_src[2],-1, 0,0,lgt_src[1],0, 0,0,0,lgt_src[1] };

	glEnable(GL_LIGHTING);		//Draw Running Robot
	glPushMatrix();
		glRotatef(theta, 0, 1, 0);
		glTranslatef(0, 1, -50);
		glRotatef(90, 0, 1, 0);		// to face where robot is moving
		drawRunningModel(false);
	glPopMatrix();

	glDisable(GL_LIGHTING);		//Draw Running Robot Shadow
	glPushMatrix();
		glMultMatrixf(shadowMat);
		glRotatef(theta, 0, 1, 0);
		glTranslatef(0, 1, -50);
		glRotatef(90, 0, 1, 0);
		glColor4f(0.2, 0.2, 0.2, 1.0);
		drawRunningModel(true);
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

	glutSwapBuffers();   //Useful for animation
}

//--------------------------------------------------------------------------------
void special(int key, int x, int y)
{
	step = 0;
	if (key == GLUT_KEY_LEFT) lookTheta += (5.0 * 3.14 / 180.0 );   //in radians
	else if (key == GLUT_KEY_RIGHT) lookTheta -= (5.0 * 3.14 / 180.0);
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
	glutTimerFunc(50, dogTimer, 0);
	glutTimerFunc(50, bb8Timer, 0);
	glutSpecialFunc(special);
	glutMainLoop();
	return 0;
}
