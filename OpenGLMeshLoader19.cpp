#include "TextureBuilder.h"
#include "Model_3DS.h"
#include "GLTexture.h"
#include <glut.h>
#include <iostream>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>

using namespace std;
int WIDTH = 650;
int HEIGHT = 500;
int speX = 0;
int speZ = 0;
int speY = 0;
//coins
int n[60];
int h[90];
//salma rocks & cactus
int c[30];
int r[40];
int w[15];
//hana cars cones buildings
int m[30];
int o[16];
int p[200];
int q[30];

int coinposX = 0;
int coinposZ = 0;
int coneposX = 0;
int coneposZ = 0;
int carposX = 0;
int carposZ = 0;
int cactusposZ = 0;
int cactusposX = 0;
int rockposX = 0;
int rockposZ = 0;
int coins = 0;
int coinRotX = 0;
int coinRotY = 0;
int coinRotZ = 0;
int powerupX = 0;
int powerupZ = 0;
int angle = 0;
int xmove = 1;
int health = 5;
int level = 1;
int building = 0;
int won = 0; //won flag
bool flag = true; //lost flag
GLuint tex;
char title[] = "Need for speed";

// 3D Projection Options
GLdouble fovy = 45.0;
GLdouble aspectRatio = (GLdouble)WIDTH / (GLdouble)HEIGHT;
GLdouble zNear = 0.1;
GLdouble zFar = 10000;

class Vector
{
public:
	GLdouble x, y, z;
	Vector() {}
	Vector(GLdouble _x, GLdouble _y, GLdouble _z) : x(_x), y(_y), z(_z) {}
	//================================================================================================//
	// Operator Overloading; In C++ you can override the behavior of operators for you class objects. //
	// Here we are overloading the += operator to add a given value to all vector coordinates.        //
	//================================================================================================//
	void operator +=(float value)
	{
		x += value;
		y += value;
		z += value;
	}
};

Vector Eye(0, 5, 20);
Vector At(0, 0, 0);
Vector Up(0, 1, 0);

int cameraZoom = 0;

// Model Variables
Model_3DS model_house;
Model_3DS model_tree;
Model_3DS model_car;
Model_3DS model_cone;
Model_3DS model_cactus;
//Model_3DS model_banner;
Model_3DS model_flag;
Model_3DS model_coins;
Model_3DS model_goldcoins;
Model_3DS model_coin2;
Model_3DS model_street;
Model_3DS model_carobstacle;
Model_3DS model_rock;
Model_3DS model_heart;
Model_3DS model_lamp;
Model_3DS model_powerup;

// Textures
GLTexture tex_ground;
GLTexture tex_coin;
GLTexture tex_asphalt;

//GLTexture tex_city;
GLTexture tex_desert;
GLTexture mac;
GLuint ball;

//=======================================================================
// Lighting Configuration Function
//=======================================================================
void InitLightSource()
{
	/* Enable Lighting for this OpenGL Program
	glEnable(GL_LIGHTING);

	// Enable Light Source number 0
	// OpengL has 8 light sources
	glEnable(GL_LIGHT0);

	// Define Light source 0 ambient light
	GLfloat ambient[] = { 1.1f, 0.1f,0.1f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	// Define Light source 0 diffuse light
	GLfloat diffuse[] = { 1.5f, 1.5f, 1.5f, 0.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);



	// Define Light source 0 Specular light
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	GLfloat position[] = { 0, 1, 0, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, position);*/
	GLfloat specular[] = { 1.0f,1.0f,1.0f,1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	GLfloat light_position[] = { speX,0,speZ,1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	GLfloat lightIntensity[] = { 0.2,0.2,0.2,1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);
	GLfloat lightDirection[] = { speX,1,speZ + 5,0 };
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 6);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 64);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightDirection);

}
//=======================================================================
// Material Configuration Function
//======================================================================
void InitMaterial()
{
	// Enable Material Tracking
	glEnable(GL_COLOR_MATERIAL);

	// Sich will be assigneet Material Properties whd by glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Set Material's Specular Color
	// Will be applied to all objects
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

	// Set Material's Shine value (0->128)
	GLfloat shininess[] = { 96.0f };
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}

//=======================================================================
// OpengGL Configuration F unction
//=======================================================================
void myInit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(fovy, aspectRatio, zNear, zFar);
	//*****//
	// fovy: Angle between the bottom and top of the projectors, in degrees. //
	// aspectRatio: Ratio of width to height of the clipping plane. //
	// zNear and zFar: Specify the front and back clipping planes distances from camera. //
	//*****//

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
	//*****//
	// EYE (ex, ey, ez): defines the location of the camera. //
	// AT (ax, ay, az): denotes the direction where the camera is aiming at. //
	// UP (ux, uy, uz):  denotes the upward orientation of the camera. //
	//*****//

	InitLightSource();

	InitMaterial();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);
}

void InitializeCoinsArrayLevel1() {
	for (int i = 0; i < 60; i += 3)
	{
		int x = rand() % 2 + 1;
		if (x == 2) {
			n[i] = 2;
		}
		else {
			n[i] = -2;
		}
		n[i + 1] = coinposZ - 20;
		n[i + 2] = 0;
		coinposZ = coinposZ - 20;
		cout << "a";
		cout << n[i];
		cout << "b";
		cout << n[i + 1];
		cout << "c";
		cout << n[i + 2];
	};
}
void InitializeCoinsArrayLevel2() {
	coinposZ = 0;
	for (int i = 0; i < 90; i += 3)
	{
		int x = rand() % 2 + 1;
		if (x == 2) {
			h[i] = 2;
		}
		else {
			h[i] = -2;
		}
		h[i + 1] = coinposZ - 20;
		h[i + 2] = 0;
		coinposZ = coinposZ - 20;
	
	};
}
void InitializeCactusArray() {
	for (int i = 0; i < 14; i += 2)
	{
		int x = rand() % 2 + 1;
		if (x == 2) {
			c[i] = 2;
		}
		else {
			c[i] = -2;
		}
		if ((cactusposZ - 50) % 70 == 0) {
			c[i + 1] = -1000;
		}
		if ((cactusposZ - 50) % 20 == 0) {
			c[i + 1] = -1000;
		}
		else {
			c[i + 1] = cactusposZ - 50;
		}
		cactusposZ = cactusposZ - 50;
		cout << "d";
		cout << c[i];
		cout << "cactus";
		cout << c[i + 1];
	};
}
void InitializeRockArray() {
	for (int i = 0; i < 10; i += 2)
	{
		int x = rand() % 2 + 1;
		if (x == 2) {
			r[i] = 2;
		}
		else {
			r[i] = -2;
		}
		rockposZ = rockposZ - 70;
		//o[i] = rand() % 10 - 5;
		if (rockposZ % 40 == 0) {
			r[i + 1] = -1000;
		}
		else if (rockposZ % 40 == 0) {
			r[i + 1] = -1000;
		}
		else if (rockposZ == -70) {
			r[i + 1] = -1000;
		}
		else {
			r[i + 1] = (rockposZ - 70);
		}

		cout << "f";
		cout << r[i];
		cout << "rock";
		cout << r[i + 1];
	};
}
void InitializeConesArray() {
	for (int i = 0; i < 24; i += 2)
	{
		int x = rand() % 2 + 1;
		if (x == 2) {
			m[i] = 2;
		}
		else {
			m[i] = -2;
		}
		if ((coneposZ - 50) % 20 == 0) {
			m[i + 1] = -1000;
		}
		else if ((coneposZ - 50) % 70 == 0) {
			m[i + 1] = -1000;
		}
		else {
			m[i + 1] = coneposZ - 50;
		}
		coneposZ = coneposZ - 50;

			//600
	};
}
void InitializeCarArray() {
	for (int i = 0; i < 16; i += 2)
	{

		o[i] = -2;
		carposZ = carposZ - 70;
		//o[i] = rand() % 10 - 5;
		if (carposZ % 40 == 0) {
			o[i + 1] = -10000;
		}
		else if (carposZ == -70) {
			o[i + 1] = -10000;
		}
		else {
			o[i + 1] = (carposZ - 70);
		}

		//cout << "f";
		//cout << o[i];
		//cout << "g";
		//cout << o[i + 1];
		//630
	};
}
void InitializeBuildingsArray() {
	for (int i = 0; i < 200; i += 4)
	{
		p[i] = -5;
		building = building - 20;
		p[i + 1] = building;
		p[i + 2] = 5;
		p[i + 3] = building;
		cout << p[i];
		cout << "i";
		cout << p[i + 1];
		cout << "j";
		cout << i;
	};

}
void InitializePowerUpsArray() {
	powerupZ = 0;
	for (int i = 0; i < 30; i += 3)
	{
		int x = rand() % 2 + 1;
		if (x == 2) {
			q[i] = 2;
		}
		else {
			q[i] = -2;
		}
		q[i + 1] = powerupZ - 90;
		q[i + 2] = 0;
		powerupZ = powerupZ - 90;
		//	cout << "q[i]";
		//	cout << q[i];
		//	cout << "q[i+1]";
		//	cout << q[i+1];
	};
}
void InitializePowerUpsArrayL1() {
	powerupZ = 0;
	for (int i = 0; i < 30; i += 3)
	{
		int x = rand() % 2 + 1;
		if (x == 2) {
			w[i] = 2;
		}
		else {
		w[i] = -2;
		}
		w[i + 1] = powerupZ - 90;
		w[i + 2] = 0;
		powerupZ = powerupZ - 90;
		//	cout << "q[i]";
		//	cout << q[i];
		//	cout << "q[i+1]";
		//	cout << q[i+1];
	};
}


//=======================================================================
// Render Ground Function
//=======================================================================
void RenderGround()
{
	if (level == 1) {
		glDisable(GL_LIGHTING); // Disable lighting

		glColor3f(0.6, 0.6, 0.6); // Dim the ground texture a bit

		glEnable(GL_TEXTURE_2D); // Enable 2D texturing

		glBindTexture(GL_TEXTURE_2D, tex_desert.texture[0]); // Bind the ground texture

		glPushMatrix();
		glBegin(GL_QUADS);
		glNormal3f(0, 1, 0); // Set quad normal direction.
		glTexCoord2f(0, 0); // Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
		glVertex3f(-20, 0, -20);
		glTexCoord2f(5, 0);
		glVertex3f(20, 0, -20);
		glTexCoord2f(5, 5);
		glVertex3f(20, 0, 20);
		glTexCoord2f(0, 5);
		glVertex3f(-20, 0, 20);
		glEnd();
		glPopMatrix();

		glEnable(GL_LIGHTING); // Enable lighting again for other entites coming throung the pipeline.

		glColor3f(1, 1, 1); // Set material back to white instead of grey used for the ground texture.
	}
	else {
		glDisable(GL_LIGHTING);	// Disable lighting

		glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

		glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

		glBindTexture(GL_TEXTURE_2D, tex_asphalt.texture[0]);	// Bind the ground texture

		glPushMatrix();
		glBegin(GL_QUADS);
		glNormal3f(0, 1, 0);	// Set quad normal direction.
		glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
		glVertex3f(-20, 0, -20);
		glTexCoord2f(3, 0);
		glVertex3f(20, 0, -20);
		glTexCoord2f(3, 3);
		glVertex3f(20, 0, 20);
		glTexCoord2f(0, 3);
		glVertex3f(-20, 0, 20);
		glEnd();
		glPopMatrix();

		glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

		glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
	}
}
void print(int x, int y, char* string)
{
	int len, i;
	//set the position of the text in the window using the x and y coordinates
	//glRasterPos2f(x, y);
	glRasterPos2f(x, y);
	//get the length of the string to display
	len = (int)strlen(string);
	//loop to display character by character
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

void RenderCoin()
{
	glDisable(GL_LIGHTING); // Disable lighting

	glColor3f(0.6, 0.6, 0.6); // Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D); // Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, tex_coin.texture[0]); // Bind the ground texture
	glPushMatrix();
	//glRotated(90, 0, 1, 0);
	glScaled(0.2, 0.2, 0.2);
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0); // Set quad normal direction.
	glTexCoord2f(0, 0); // Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-20, 0, -20);
	glTexCoord2f(1, 0);
	glVertex3f(20, 0, -20);
	glTexCoord2f(1, 1);
	glVertex3f(20, 0, 20);
	glTexCoord2f(0, 1);
	glVertex3f(-20, 0, 20);
	glEnd();
	glPopMatrix();
	glPopMatrix();

	glEnable(GL_LIGHTING); // Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1); // Set material back to white instead of grey used for the ground texture.
}


//=======================================================================
// Display Function
//=======================================================================
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (flag == true) {
		if (level == 1) {

			GLfloat lightIntensity[] = { 0.7, 0.7, 0.7, 1.0f };
			GLfloat lightPosition[] = { 0.0f, 100.0f, 0.0f, 0.0f };
			glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
			glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);
			// Draw Ground
			glPushMatrix();
			glTranslated(0, 0.1, speZ);
			glColor3f(1, 1, 1);
			char* levelnum[20];
			sprintf((char*)levelnum, "Level 1", 0);
			print(-8, 5, (char*)levelnum);
			char* myStr[20];
			sprintf((char*)myStr, "coins", 0);
			print(-8, 6, (char*)myStr);
			char* p0s[20];
			sprintf((char*)p0s, "%d", coins);
			print(-6, 6, (char*)p0s);
			glScaled(6, 1, 30);
			RenderGround();
			glPopMatrix();

			for (int i = 0; i <= 60; i += 3)
			{
				if (n[i + 2] == 0) {
					glPushMatrix();
					glTranslated(n[i], 1, n[i + 1]);
					glScaled(0.3, 0.3, 0.3);
					glRotated(angle, 0, 1, 0);
					glRotated(90, 1, 0, 0);
					model_coin2.Draw();
					glPopMatrix();
				}
			}
			for (int i = 2; i < 10; i += 2)
			{
				glPushMatrix();
				glTranslated(r[i], 1, r[i + 1]);
				glScaled(0.02, 0.03, 0.01);
				model_rock.Draw();
				glPopMatrix();
			}
			for (int i = 4; i < 14; i += 2)
			{
				glPushMatrix();
				glTranslated(c[i], 1, c[i + 1]);
				glScaled(0.04, 0.04, 0.04);
				model_cactus.Draw();
				glPopMatrix();
			}

			//Draw car Model
			glPushMatrix();
			glTranslated(speX, 0, speZ);
			cout << "speZ";
			cout << speZ;
			glPushMatrix();
			glTranslated(0, 0, 0);
			glRotated(90, 0, 1, 0);
			glScaled(0.02, 0.02, 0.02);
			model_house.Draw();
			glPopMatrix();
			glPopMatrix();


			//heart 1
			if (health >= 1) {
				glPushMatrix();
				glColor3f(1, 0, 0);
				glTranslated(7, 6.5, speZ);
				//glTranslated(3, 6.5, speZ);
				glScaled(0.5, 0.5, 0.5);
				glRotated(90, 0, 1, 0);
				model_heart.Draw();
				glPopMatrix();
			}
			//heart 2
			if (health >= 2) {
				glPushMatrix();
				glColor3f(1, 0, 0);
				glTranslated(6, 6.5, speZ);
				//glTranslated(4, 6.5, speZ);
				glScaled(0.5, 0.5, 0.5);
				glRotated(90, 0, 1, 0);
				model_heart.Draw();
				glPopMatrix();
			}
			//heart 3
			if (health >= 3) {
				glPushMatrix();
				glEnable(GL_LIGHTING); // Enable lighting again for other entites coming throung the pipeline.
				glColor3f(1, 0, 0); // Set material back to white instead of grey used for the ground texture.
				glTranslated(5, 6.5, speZ);
				glScaled(0.5, 0.5, 0.5);
				glRotated(90, 0, 1, 0);
				model_heart.Draw();
				glPopMatrix();
			}
			//heart 4
			if (health >= 4) {
				glPushMatrix();
				glColor3f(1, 0, 0);

				glTranslated(4, 6.5, speZ);
				//glTranslated(6, 6.5, speZ);
				glScaled(0.5, 0.5, 0.5);
				glRotated(90, 0, 1, 0);
				model_heart.Draw();
				glPopMatrix();
			}
			//heart 5
			if (health >= 5) {
				glPushMatrix();
				glColor3f(1, 0, 0);
				glTranslated(3, 6.5, speZ);
				//glTranslated(7, 6.5, speZ);
				glScaled(0.5, 0.5, 0.5);
				glRotated(90, 0, 1, 0);
				model_heart.Draw();
				glPopMatrix();
			}


			//sky box
			glPushMatrix();
			glColor3f(1, 1, 1);
			GLUquadricObj* qobj;
			qobj = gluNewQuadric();
			glScaled(1000, 1000, 1000);
			glTranslated(0, 0, 0);
			glRotated(90, 1, 0, 1);
			glBindTexture(GL_TEXTURE_2D, tex);
			gluQuadricTexture(qobj, true);
			gluQuadricNormals(qobj, GL_SMOOTH);
			gluSphere(qobj, 100, 100, 100);

			gluDeleteQuadric(qobj);


			glPopMatrix();


			//draw ball
			glPushMatrix();

			GLUquadricObj* qobj2;
			qobj2 = gluNewQuadric();
			glTranslated(0, 5, -20 + speZ);
			glRotated(90, 1, 0, 0);
			glBindTexture(GL_TEXTURE_2D, ball);
			gluQuadricTexture(qobj2, true);
			gluQuadricNormals(qobj2, GL_SMOOTH);
			gluSphere(qobj2, 60, 100, 100);
			gluDeleteQuadric(qobj2);
			glPopMatrix();
			for (int i = 0; i <= 8; i += 3)
			{
				if (w[i + 2] == 0) {
					glPushMatrix();
					glTranslated(w[i], 0.5, w[i + 1]);
					glScaled(0.009, 0.009, 0.009);
					model_powerup.Draw();
					glPopMatrix();
				}
			}
			//if (!flag) {  //lost
				//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				//exiting(2);
			//}
			/*
			glPushMatrix();
			glTranslated(1, 1, 1);
			glScaled(2, 2, 2);
			model_flag.Draw();
			glPopMatrix();*/


			glFlush();
			glutSwapBuffers();
		}
		else {
			InitLightSource();
			// Draw Ground
			glPushMatrix();
			glTranslated(0, 0.1, speZ);
			glColor3f(1, 1, 1);
			char* levelnum[20];
			sprintf((char*)levelnum, "Level 2", 0);
			print(-8, 7, (char*)levelnum);
			char* myStr[20];
			sprintf((char*)myStr, "coins", 0);
			print(-8, 6, (char*)myStr);
			char* p0s[20];
			sprintf((char*)p0s, "%d", coins);
			print(-6, 6, (char*)p0s);
			if (won == 1) {
				char* winner[20];
				sprintf((char*)winner, "WINNERRR", 0);
				print(5, 7, (char*)winner);
			}
			glScaled(0.3, 3, 6);
			RenderGround();
			glPopMatrix();



			//glPushMatrix();
			//glScaled(1, 1, 1);
			//RenderCoin();
			//glPopMatrix();

			//glPushMatrix();
			//glTranslated(4, 7, 8);
			//glScaled(4, 7, 4);
			//model_flag.Draw();
			//glPopMatrix();

			//for (int count = 0; count >=-200; count-=40)
			for (int i = 0; i < 90; i += 3)
			{
				if (h[i + 2] == 0) {

					glPushMatrix();
					glTranslated(h[i], 1, h[i + 1]);
					glScaled(0.2, 0.2, 0.2);
					glRotated(angle, 0, 1, 0);
					glRotated(90, 1, 0, 0);
					model_coin2.Draw();
					glPopMatrix();

				}
			}

			for (int i = 0; i < 16; i += 2)
			{
				//cout << "ana henanaananna";
				glPushMatrix();
				cout << "i";
				cout << o[i + 1];
				glTranslated(o[i], 0.5, o[i + 1]);
				glScaled(0.5, 0.5, 0.5);
				glRotated(-90, 0, 1, 0);
				model_carobstacle.Draw();
				glPopMatrix();
			}

			for (int i = 4; i < 200; i += 2) {
				glPushMatrix();
				///glColor3f(0.5, 0.5, 1);
				glTranslated(p[i], 0, p[i + 1]);
				glScaled(0.9, 2, 1);
				model_lamp.Draw();
				glPopMatrix();

			}
			//Draw car Model
			glPushMatrix();
			glTranslated(speX, 0, speZ);
			//cout << "spez";
			//cout << speZ;
			glPushMatrix();
			glTranslated(0, 0, 0);
			glRotated(90, 0, 1, 0);
			glScaled(0.02, 0.02, 0.02);
			model_house.Draw();
			glPopMatrix();
			glPopMatrix();

			//heart 1
			if (health >= 1) {
				glPushMatrix();
				glColor3f(1, 0, 0);
				glTranslated(3, 6, speZ);
				glScaled(0.5, 0.5, 0.5);
				glRotated(90, 0, 1, 0);
				model_heart.Draw();
				glPopMatrix();
			}
			//heart 2
			if (health >= 2) {
				glPushMatrix();
				glColor3f(1, 0, 0);
				glTranslated(4, 6, speZ);
				glScaled(0.5, 0.5, 0.5);
				glRotated(90, 0, 1, 0);
				model_heart.Draw();
				glPopMatrix();
			}
			//heart 3
			if (health >= 3) {
				glPushMatrix();
				glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.
				glColor3f(1, 0, 0);	// Set material back to white instead of grey used for the ground texture.
				glTranslated(5, 6, speZ);
				glScaled(0.5, 0.5, 0.5);
				glRotated(90, 0, 1, 0);
				model_heart.Draw();
				//glBindTexture(GL_TEXTURE_2D, tex_heart.texture[0]);
				//glEnable(GL_TEXTURE_2D);	// Enable 2D texturing
				glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit
				glDisable(GL_LIGHTING);	// Disable lighting
				glPopMatrix();
			}
			//heart 4
			if (health >= 4) {
				glPushMatrix();
				glColor3f(1, 0, 0);
				glTranslated(6, 6, speZ);
				glScaled(0.5, 0.5, 0.5);
				glRotated(90, 0, 1, 0);
				model_heart.Draw();
				glPopMatrix();
			}
			//heart 5
			if (health >= 5) {
				glPushMatrix();
				glColor3f(1, 0, 0);
				glTranslated(7, 6, speZ);
				glScaled(0.5, 0.5, 0.5);
				glRotated(90, 0, 1, 0);
				model_heart.Draw();
				glPopMatrix();
			}

			//sky box
			glPushMatrix();
			glColor3f(0.1, 0.3, 0.7);
			GLUquadricObj* qobj;
			qobj = gluNewQuadric();
			glTranslated(0, 5, -20 + speZ);
			glRotated(90, 1, 0, 0);
			glBindTexture(GL_TEXTURE_2D, tex);
			gluQuadricTexture(qobj, true);
			gluQuadricNormals(qobj, GL_SMOOTH);
			gluSphere(qobj, 60, 100, 100);
			//gluSphere(qobj, 10, 100, 100); //mooon drawing
			gluDeleteQuadric(qobj);
			glPopMatrix();

			for (int i = 0; i < 22; i += 2)
			{
				glPushMatrix();
				glColor3f(1, 0.6, 0.3);
				glTranslated(m[i], 0, m[i + 1]);
				glScaled(0.5, 0.5, 0.5);
				model_cone.Draw();
				glPopMatrix();
			}
			for (int i = 0; i <= 15; i += 3)
			{
				if (q[i + 2] == 0) {
					glPushMatrix();
					glTranslated(q[i], 0.5, q[i + 1]);
					glScaled(0.009, 0.009, 0.009);
					model_powerup.Draw();
					glPopMatrix();
				}
			}
			glPushMatrix();
			glColor3f(0, 1, 0);
			glTranslated(0.02, 0.07, -600);
			glScaled(5, 0.5, 0.5);
			glutSolidCube(1.0);
			glPopMatrix();

			glClearColor(1, 1, 1, 0);

			glutSwapBuffers();
		}
	}
	else if (flag==false) {
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		InitLightSource();
		if (level == 1) {
			glPushMatrix();
			glTranslated(0, 0.1, speZ);
			glColor3f(1, 1, 1);
			char* levelnum[20];
			sprintf((char*)levelnum, "LOSER", 0);
			print(0, 5, (char*)levelnum);
			char* myStr[20];
			glScaled(6, 1, 30);
			RenderGround();
			glPopMatrix();
		}
		else {
			glPushMatrix();
			glTranslated(0, 0.1, speZ);
			glColor3f(1, 1, 1);
			char* levelnum[20];
			sprintf((char*)levelnum, "LOSER", 0);
			print(-1, 2, (char*)levelnum);
			glScaled(0.3, 3, 6);
			RenderGround();
			glPopMatrix();
		}


		glutSwapBuffers();
	}
}

//=======================================================================
// Keyboard Function
//=======================================================================
void myKeyboard(unsigned char button, int x, int y)
{
	switch (button)
	{
	case 'w':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 'r':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case 't':
		//camera
	//	cout << "up";
		Eye.y = 20;
		At.y = 0;
		break;
	case 'f':
		//camera
		//cout << "original";
		Eye.y = 5;
		At.y = 0;
		break;
	case 27:
		//exit(0);
		break;
	default:
		break;
	}
	glLoadIdentity(); //Clear Model_View Matrix

	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z); //Setup Camera with modified paramters

	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glutPostRedisplay(); //Re-draw scene
}

//=======================================================================
// Motion Function
//=======================================================================
void myMotion(int x, int y)
{
	y = HEIGHT - y;

	if (cameraZoom - y > 0)
	{
		Eye.x += -0.1;
		Eye.z += -0.1;
	}
	else
	{
		Eye.x += 0.1;
		Eye.z += 0.1;
	}

	cameraZoom = y;
	//cout << cameraZoom;
	//cout << "cameraZoom";
	glLoadIdentity(); //Clear Model_View Matrix

	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z); //Setup Camera with modified paramters

	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glutPostRedisplay(); //Re-draw scene
}


//=======================================================================
// Mouse Function
//=======================================================================
void myMouse(int button, int state, int x, int y)
{
	y = HEIGHT - y;

	if (state == GLUT_DOWN)
	{
		cameraZoom = y;
	}
}
void spe(int k, int x, int y)// keyboard special key function takes 3 parameters
// int k: is the special key pressed such as the keyboard arrows the f1,2,3 and so on
{
	if (k == GLUT_KEY_LEFT) {//if the up arrow is pressed, then the object will be translated in the y axis by 10. (moving upwords)
		if (speX != -2) {
			speX -= 2;

		}
		else
			speX = -2;
	}
	if (k == GLUT_KEY_RIGHT) {//if the up arrow is pressed, then the object will be translated in the y axis by 10. (moving upwords)
		if (speX != 2) {
			speX += 2;
		}
		else
			speX = 2;
	}

	glLoadIdentity(); //Clear Model_View Matrix

	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z); //Setup Camera with modified paramters

	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glutPostRedisplay();//redisplay to update the screen with the changes
}
/*void exiting(int k) {
	if (!flag)
		exit(0);
	glutPostRedisplay();//redisplay to update the screen with the changes
	glutTimerFunc(100, exiting, 0);
}*/
void cameraMovement(int k) {
	if (speZ == -400 && level==1 && flag==true) {
		PlaySound(TEXT("levelup.wav"), NULL, SND_ASYNC | SND_FILENAME );
		
		level = 2;
		health = 5;
		speZ = 0;
		Eye.z = 20;
		At.z = 0;
		coins = 0;
		coinposZ = 0;
		coinposX = 0;
	}
	if (speZ == -600 && level == 2 && flag==true) {
		won = 1;
		PlaySound(TEXT("win.wav"), NULL, SND_ASYNC | SND_FILENAME| SND_LOOP);
		//flag = true;

	}
	speZ -= 10;
	Eye.z -= 10;
	At.z -= 10;

	glLoadIdentity(); //Clear Model_View Matrix

	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z); //Setup Camera with modified paramters

	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glutPostRedisplay();//redisplay to update the screen with the changes
	glutTimerFunc(1000, cameraMovement, 0);
}
void coinRotation(int k) {
	//PlaySound(TEXT("bike1.mp3"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);

	// << angle;
	if (angle < 360) {
		angle = angle + 90;

	}
	else {
		angle = 0;
	}

	glLoadIdentity(); //Clear Model_View Matrix

	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z); //Setup Camera with modified paramters

	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glutPostRedisplay();//redisplay to update the screen with the changes
	glutTimerFunc(100, coinRotation, 0);
}

void song(int k) {


	glLoadIdentity(); //Clear Model_View Matrix

	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z); //Setup Camera with modified paramters

	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glutPostRedisplay();//redisplay to update the screen with the changes
	glutTimerFunc(5000, song, 0);
}

/*
void collisionCone(int k) {
for (int i = 0; i <= 30; i += 2) {

if ((speX == n[i]) && (speZ == n[i + 1])) {
cout << "collision";
coins += 1;
n[i + 2] = 1;
cout << "coins:";
cout << coins;
}
}
for (int i = 0; i <= 30; i += 2) {

if ((speX == m[i]) && (speZ == m[i + 1])) {
cout << "collisionCONE";
health -= 1;
cout << health;
}
}
glutPostRedisplay();//redisplay to update the screen with the changes
glutTimerFunc(10, collisionCone, 0);
}
*/
void collisionCone(int k) {
	if (speY == 10) {
		speY = 10;
	}
	else {
		speY += 1;
	}
	if (flag==true){

		if (level == 1) {
			for (int i = 0; i <= 15; i += 3) {
				if ((speX == w[i]) && (speZ == w[i + 1])) {
					PlaySound(TEXT("powerup.wav"), NULL, SND_ASYNC);
					w[i + 2] = 1;
					cout << "collision powerupl1";
					if (health < 5) {
						health += 1;
					}

				}

			}
			for (int i = 0; i <= 60; i += 3) {

				if ((speX == n[i]) && (speZ == n[i + 1])) {
					PlaySound(TEXT("coinwin.wav"), NULL, SND_ASYNC);



					cout << "collisionCoinLevel1";
					coins += 1;
					n[i + 2] = 1;
					//cout << "coins:";
					//cout << coins;

				}
			}
			for (int i = 4; i < 14; i += 2) {
				if ((speX == c[i]) && (speZ == c[i + 1])) {
					PlaySound(TEXT("crash1.wav"), NULL, SND_ASYNC);
					cout << "collisionCactus";
					health -= 1;
					//cout << "health";
					//cout << health;
					//cout << "m[i]";
					//cout << c[i + 1];
					if (health == 0)
					{
						//PlaySound(TEXT("slowloss.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
						flag = false;

						//exit(0);
					}
				}
			}
			for (int i = 2; i < 10; i += 2) {
				if ((speX == r[i]) && (speZ == r[i + 1])) {
					PlaySound(TEXT("crash1.wav"), NULL, SND_ASYNC);
					cout << "collisionRock";
					health -= 1;
					//cout << "health";
					//cout << health;
					//cout << "r[i]";
					//cout << r[i + 1];
					if (health <= 0)
					{

						flag = false;
					}
				}

			}

		}
		else {
			for (int i = 0; i < 90; i += 3) {

				if ((speX == h[i]) && (speZ == h[i + 1])) {
					PlaySound(TEXT("coinwin.wav"), NULL, SND_ASYNC);
					cout << "collisionCoinLevel1";
					coins += 1;
					h[i + 2] = 1;
					//cout << "coins:";
					//cout << coins;

				}
			}
			for (int i = 0; i < 22; i += 2) {

				if ((speX == m[i]) && (speZ == m[i + 1])) {
					cout << "collisionCONE";
					PlaySound(TEXT("conescrashsound.wav"), NULL, SND_ASYNC);
					health -= 1;
					//	cout << "health";
					//	cout << health;
					//	cout << "m[i]";
					//	cout << m[i+1];
					if (health <= 0)
					{
						//exit(0);
						flag = false;
					}
				}
			}
			for (int i = 0; i <= 14; i += 2) {
				if (o[i] < 3) {
					o[i] += 1;
				}
				else {
					o[i] = -2;
				}
				if ((speX == o[i]) && (speZ == o[i + 1])) {
					PlaySound(TEXT("gunshot.wav"), NULL, SND_ASYNC);
					cout << "collisionCAR";
					health -= 1;
					//cout << "health";
					//cout << health;
					//cout << "o[i]";
					//cout << o[i+1];
					if (health <= 0)
					{
						//exit(0);
						flag = false;
					}
				}

			}
			for (int i = 0; i <= 15; i += 3) {
				if ((speX == q[i]) && (speZ == q[i + 1])) {
					PlaySound(TEXT("powerup.wav"), NULL, SND_ASYNC);
					q[i + 2] = 1;
					cout << "collision powerup";
					if (health < 5) {
						health += 1;
					}

				}

			}
		}
	}
	if (health == 1) {
		PlaySound(TEXT("loss.wav"), NULL, SND_ASYNC);
	}
	if (health <= 0) {
		//exit(0);
		flag = false;
		Eye.y = 10;

		PlaySound(TEXT("slowloss.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	}
	glutPostRedisplay();//redisplay to update the screen with the changes
	glutTimerFunc(1000, collisionCone, 0);
}


//=======================================================================
// Reshape Function
//=======================================================================
void myReshape(int w, int h)
{
	if (h == 0) {
		h = 1;
	}

	WIDTH = w;
	HEIGHT = h;

	// set the drawable region of the window
	glViewport(0, 0, w, h);

	// set up the projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, (GLdouble)WIDTH / (GLdouble)HEIGHT, zNear, zFar);

	// go back to modelview matrix so we can move the objects about
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
}

//=======================================================================
// Assets Loading Function
//=======================================================================
void LoadAssets()
{
	// Loading Model files
	model_house.Load("Models/car/taxi.3DS");
	model_tree.Load("Models/tree/Tree1.3ds");
	model_cone.Load("Models/Low-Poly-Cone/3DS/Cone.3ds");
	model_carobstacle.Load("Models/Car-Model/Car.3ds");
	model_cactus.Load("models/cactus2/cactus.3ds");
	model_flag.Load("Models/flag/lp_flag3ds.3DS");
	model_heart.Load("models/Heart1/Heart.3ds");
	model_coin2.Load("models/coin2/Coin2.3ds");
	model_rock.Load("models/rocks2/CavePlatform1_3ds.3ds");
	model_lamp.Load("models/park lamp/street light.3ds");
	model_powerup.Load("models/rocket/medbox.3DS");
	// Loading texture files
	//tex_ground.Load("Textures/ground.bmp");
	tex_asphalt.Load("Textures/Asphalt.bmp");
	tex_desert.Load("Textures/desert.bmp");

	loadBMP(&tex, "Textures/blu-sky-3.bmp", true);
	loadBMP(&ball, "Textures/coin.bmp", true);

}

//=======================================================================
// Main Function
//=======================================================================
void main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(WIDTH, HEIGHT);

	glutInitWindowPosition(100, 150);

	glutCreateWindow(title);
	InitializeCoinsArrayLevel1();
	InitializeCoinsArrayLevel2();
	InitializeRockArray();
	InitializeCactusArray();
	InitializePowerUpsArray();
	InitializePowerUpsArrayL1();
	InitializeConesArray();
	InitializeCarArray();
	InitializeBuildingsArray();
	glutDisplayFunc(myDisplay);
	glutSpecialFunc(spe);

	glutKeyboardFunc(myKeyboard);

	glutMotionFunc(myMotion);

	glutMouseFunc(myMouse);

	glutReshapeFunc(myReshape);
	glutTimerFunc(100, coinRotation, 0);
	glutTimerFunc(100, cameraMovement, 0);
	glutTimerFunc(1000, collisionCone, 0);
	glutTimerFunc(5000, song, 0);
	//glutTimerFunc(5000, exiting, 0);
	myInit();

	LoadAssets();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);
	//PlaySound(TEXT("bicycle1.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	glutMainLoop();
}