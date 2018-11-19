#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<Windows.h>
#include<GL/glut.h>

double cameraAngle;

int canDrawGrid, canDrawAxis, manBullet, airBullet, airCraft, heliCopter;

double manX, manY, manZ, manAngle, rotor, launcherX, launcherY, launcherZ, helicopterDist= 35, aeroplaneDist = 70;

int helicopterDestroy, aeroplaneDestroy, wave1;
bool notLose;

int missileLenX = 1, missileLenY = 1, missileLenZ = 11;

int helicopterLenX = 75, helicopterLenY = 20, helicopterLenZ = 26;

int aeroplaneLenX = 72, aeroplaneLenY = 20, aeroplaneLenZ = 20;

int manLenX = 13, manLenY = 7, manLenZ = 42;

double cameraRadius, cameraHeight, cameraAngleDelta;

int num_texture = -1;
GLuint grassImg, militryHImg, skyImg, aircraftBodyImg, usImg, wingImg, manImg, hairImg, skinImg, clothImg, shoeImg, goldenImg, launcherImg,fireImg;


int LoadBitmapImage(char *filename)
{
	int i, j = 0;
	FILE *l_file;
	unsigned char *l_texture;

	BITMAPFILEHEADER fileheader;
	BITMAPINFOHEADER infoheader;
	RGBTRIPLE rgb;

	num_texture++;

	if ((l_file = fopen(filename, "rb")) == NULL) return (-1);

	fread(&fileheader, sizeof(fileheader), 1, l_file);

	fseek(l_file, sizeof(fileheader), SEEK_SET);
	fread(&infoheader, sizeof(infoheader), 1, l_file);

	l_texture = (byte *)malloc(infoheader.biWidth * infoheader.biHeight * 4);
	memset(l_texture, 0, infoheader.biWidth * infoheader.biHeight * 4);
	for (i = 0; i < infoheader.biWidth*infoheader.biHeight; i++)
	{
		fread(&rgb, sizeof(rgb), 1, l_file);

		l_texture[j + 0] = rgb.rgbtRed;
		l_texture[j + 1] = rgb.rgbtGreen;
		l_texture[j + 2] = rgb.rgbtBlue;
		l_texture[j + 3] = 255;
		j += 4;
	}
	fclose(l_file);

	glBindTexture(GL_TEXTURE_2D, num_texture);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

	// glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, infoheader.biWidth, infoheader.biHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, infoheader.biWidth, infoheader.biHeight, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);

	free(l_texture);

	return (num_texture);

}

void loadImage()
{
	fireImg = LoadBitmapImage("Image/fire.bmp");
	launcherImg = LoadBitmapImage("Image/launcher.bmp");
	goldenImg = LoadBitmapImage("Image/golden.bmp");
	shoeImg = LoadBitmapImage("Image/shoe.bmp");
	clothImg = LoadBitmapImage("Image/cloth.bmp");
	skinImg = LoadBitmapImage("Image/skin.bmp");
	hairImg = LoadBitmapImage("Image/hair.bmp");
	manImg = LoadBitmapImage("Image/man.bmp");
	wingImg = LoadBitmapImage("Image/wing.bmp");
	usImg = LoadBitmapImage("Image/us.bmp");
	aircraftBodyImg = LoadBitmapImage("Image/military.bmp");
	militryHImg = LoadBitmapImage("Image/military2.bmp");
	grassImg = LoadBitmapImage("Image/grass.bmp");
	skyImg = LoadBitmapImage("Image/sky.bmp");

}

void wing() {

	glColor3f(1, 1, 1);

	//1
	glPushMatrix(); {
		glTranslatef(0, 0, 10);
		glBegin(GL_QUADS); {
			glTexCoord2f(0, 0);
			glVertex3f(0, 0, 0);

			glTexCoord2f(0, 1);
			glVertex3f(4, -15, 0);

			glTexCoord2f(1, 0);
			glVertex3f(7, -15, 0);

			glTexCoord2f(1, 1);
			glVertex3f(8, 0, 0);
		}glEnd();
	}glPopMatrix();

	//2
	glPushMatrix(); {
		glTranslatef(0, 0, 10);
		glBegin(GL_QUADS); {
			glTexCoord2f(0, 0);
			glVertex3f(0, 0, 0);

			glTexCoord2f(0, 1);
			glVertex3f(4, -15, 0);

			glTexCoord2f(1, 0);
			glVertex3f(4, -15, 5);

			glTexCoord2f(1, 1);
			glVertex3f(0, 0, 5);
		}glEnd();
	}glPopMatrix();


	//3
	glPushMatrix(); {
		glTranslatef(0, 0, 10);
		glBegin(GL_QUADS); {
			glTexCoord2f(0, 0);
			glVertex3f(4, -15, 0);

			glTexCoord2f(0, 1);
			glVertex3f(4, -15, 5);

			glTexCoord2f(1, 0);
			glVertex3f(7, -15, 5);

			glTexCoord2f(1, 1);
			glVertex3f(7, -15, 0);
		}glEnd();
	}glPopMatrix();

	//4
	glPushMatrix(); {
		glTranslatef(0, 0, 10);
		glBegin(GL_QUADS); {
			glTexCoord2f(0, 0);
			glVertex3f(8, 0, 0);

			glTexCoord2f(0, 1);
			glVertex3f(7, -15, 0);

			glTexCoord2f(1, 0);
			glVertex3f(7, -15, 5);

			glTexCoord2f(1, 1);
			glVertex3f(8, 0, 5);
		}glEnd();
	}glPopMatrix();

	//5
	glPushMatrix(); {
		glTranslatef(0, 0, 10);
		glBegin(GL_QUADS); {
			glTexCoord2f(0, 0);
			glVertex3f(0, 0, 0);

			glTexCoord2f(0, 1);
			glVertex3f(0, 0, 5);

			glTexCoord2f(1, 0);
			glVertex3f(8, 0, 5);

			glTexCoord2f(1, 1);
			glVertex3f(8, 0, 0);
		}glEnd();
	}glPopMatrix();


	//6
	glPushMatrix(); {
		glTranslatef(0, 0, 10);
		glBegin(GL_QUADS); {
			glTexCoord2f(0, 0);
			glVertex3f(0, 0, 5);

			glTexCoord2f(0, 1);
			glVertex3f(4, -15, 5);

			glTexCoord2f(1, 0);
			glVertex3f(7, -15, 5);

			glTexCoord2f(1, 1);
			glVertex3f(8, 0, 5);
		}glEnd();
	}glPopMatrix();

}

void tail1() {

	glColor3f(1, 1, 1);

	//1
	glPushMatrix(); {
		glTranslatef(0, 0, 10);
		glBegin(GL_QUADS); {
			glTexCoord2f(0, 0);
			glVertex3f(0, 0, 0);

			glTexCoord2f(1, 0);
			glVertex3f(5, -10, 5);

			glTexCoord2f(0, 1);
			glVertex3f(9, -10, 5);

			glTexCoord2f(1, 1);
			glVertex3f(7, 0, 0);
		}glEnd();
	}glPopMatrix();

	//2
	glPushMatrix(); {
		glTranslatef(0, 0, 10);
		glBegin(GL_QUADS); {
			glTexCoord2f(0, 0);
			glVertex3f(0, 0, 0);

			glTexCoord2f(1, 0);
			glVertex3f(5, -10, 5);

			glTexCoord2f(0, 1);
			glVertex3f(5, -10, 9);

			glTexCoord2f(1, 1);
			glVertex3f(0, 0, 4);
		}glEnd();
	}glPopMatrix();


	//3
	glPushMatrix(); {
		glTranslatef(0, 0, 10);
		glBegin(GL_QUADS); {
			glTexCoord2f(0, 0);
			glVertex3f(5, -10, 5);

			glTexCoord2f(1, 0);
			glVertex3f(5, -10, 9);

			glTexCoord2f(0, 1);
			glVertex3f(9, -10, 9);

			glTexCoord2f(1, 1);
			glVertex3f(9, -10, 5);
		}glEnd();
	}glPopMatrix();

	//4
	glPushMatrix(); {
		glTranslatef(0, 0, 10);
		glBegin(GL_QUADS); {
			glTexCoord2f(0, 0);
			glVertex3f(7, 0, 0);

			glTexCoord2f(1, 0);
			glVertex3f(9, -10, 5);

			glTexCoord2f(0, 1);
			glVertex3f(9, -10, 9);

			glTexCoord2f(1, 1);
			glVertex3f(7, 0, 4);
		}glEnd();
	}glPopMatrix();

	//5
	glPushMatrix(); {
		glTranslatef(0, 0, 10);
		glBegin(GL_QUADS); {
			glTexCoord2f(0, 0);
			glVertex3f(0, 0, 0);

			glTexCoord2f(1, 0);
			glVertex3f(0, 0, 4);

			glTexCoord2f(0, 1);
			glVertex3f(7, 0, 4);

			glTexCoord2f(1, 1);
			glVertex3f(7, 0, 0);
		}glEnd();
	}glPopMatrix();


	//6
	glPushMatrix(); {
		glTranslatef(0, 0, 10);
		glBegin(GL_QUADS); {
			glTexCoord2f(0, 0);
			glVertex3f(0, 0, 4);

			glTexCoord2f(1, 0);
			glVertex3f(5, -10, 9);

			glTexCoord2f(0, 1);
			glVertex3f(9, -10, 9);

			glTexCoord2f(1, 1);
			glVertex3f(7, 0, 4);
		}glEnd();
	}glPopMatrix();

}

void tail2() {

	glColor3f(1, 1, 1);

	//1
	glPushMatrix(); {
		glTranslatef(0, 0, 10);
		glBegin(GL_QUADS); {
			glTexCoord2f(0, 0);
			glVertex3f(0, 0, 0);

			glTexCoord2f(1, 0);
			glVertex3f(5, 10, 5);

			glTexCoord2f(0, 1);
			glVertex3f(9, 10, 5);

			glTexCoord2f(1, 1);
			glVertex3f(7, 0, 0);
		}glEnd();
	}glPopMatrix();

	//2
	glPushMatrix(); {
		glTranslatef(0, 0, 10);
		glBegin(GL_QUADS); {
			glTexCoord2f(0, 0);
			glVertex3f(0, 0, 0);

			glTexCoord2f(1, 0);
			glVertex3f(5, 10, 5);

			glTexCoord2f(0, 1);
			glVertex3f(5, 10, 9);

			glTexCoord2f(1, 1);
			glVertex3f(0, 0, 4);
		}glEnd();
	}glPopMatrix();


	//3
	glPushMatrix(); {
		glTranslatef(0, 0, 10);
		glBegin(GL_QUADS); {
			glTexCoord2f(0, 0);
			glVertex3f(5, 10, 5);

			glTexCoord2f(1, 0);
			glVertex3f(5, 10, 9);

			glTexCoord2f(0, 1);
			glVertex3f(9, 10, 9);

			glTexCoord2f(1, 1);
			glVertex3f(9, 10, 5);
		}glEnd();
	}glPopMatrix();

	//4
	glPushMatrix(); {
		glTranslatef(0, 0, 10);
		glBegin(GL_QUADS); {
			glTexCoord2f(0, 0);
			glVertex3f(7, 0, 0);

			glTexCoord2f(1, 0);
			glVertex3f(9, 10, 5);

			glTexCoord2f(0, 1);
			glVertex3f(9, 10, 9);

			glTexCoord2f(1, 1);
			glVertex3f(7, 0, 4);
		}glEnd();
	}glPopMatrix();

	//5
	glPushMatrix(); {
		glTranslatef(0, 0, 10);
		glBegin(GL_QUADS); {
			glTexCoord2f(0, 0);
			glVertex3f(0, 0, 0);

			glTexCoord2f(1, 0);
			glVertex3f(0, 0, 4);

			glTexCoord2f(0, 1);
			glVertex3f(7, 0, 4);

			glTexCoord2f(1, 1);
			glVertex3f(7, 0, 0);
		}glEnd();
	}glPopMatrix();


	//6
	glPushMatrix(); {
		glTranslatef(0, 0, 10);
		glBegin(GL_QUADS); {
			glTexCoord2f(0, 0);
			glVertex3f(0, 0, 4);

			glTexCoord2f(1, 0);
			glVertex3f(5, 10, 9);

			glTexCoord2f(0, 1);
			glVertex3f(9, 10, 9);

			glTexCoord2f(1, 1);
			glVertex3f(7, 0, 4);
		}glEnd();
	}glPopMatrix();

}

void missile(){
	//lengthX = lengthY = 1
	//lengthZ = 11

	GLUquadricObj *obj = gluNewQuadric();

	//

	glColor3f(1,1,1);
	glTranslatef(1, 1,0);

	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, fireImg);
		glPushMatrix();
		{
			glTranslatef(0, 0, 1);
			gluQuadricTexture(obj, GL_TRUE);
			gluCylinder(obj, 0, .5, 4, 25, 25);

		}glPopMatrix();

	}glDisable(GL_TEXTURE_2D);


	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, goldenImg);

		glPushMatrix(); {

			glTranslatef(0, 0,4);
			glScalef(1, 1, 0);
			gluQuadricTexture(obj, GL_TRUE);
			gluSphere(obj, 1, 25, 25);

		}glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(0, 0, 4);
			gluQuadricTexture(obj, GL_TRUE);
			gluCylinder(obj, 1, 1, 4, 25, 25);

		}glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(0, 0, 8);
			gluQuadricTexture(obj, GL_TRUE);
			gluCylinder(obj, 1, 0, 3, 25, 25);

		}glPopMatrix();

	}glDisable(GL_TEXTURE_2D);

}

typedef struct ManMissile{

	double x, y, z, speed;

	int serial;

	struct ManMissile *next;

	void throwManMissile(){

		glPushMatrix();{
			glTranslatef(x,y,z);
			missile();

		}glPopMatrix();

	}

}manMissile;
manMissile *missileLauncherStart, *mMHead;

void insertManMissile(manMissile *t)
{
	manMissile *temp;
	if (mMHead == NULL)
	{
		mMHead = t;
		missileLauncherStart->next = mMHead;
		mMHead->next = NULL;
	}

	else
	{
		temp = missileLauncherStart->next;
		while(temp->next)
		{
			temp = temp->next;
		}

		temp->next = t;

	}

}

void removeManMissile(manMissile *t)
{
	manMissile *temp, *temp1;

	temp = missileLauncherStart->next;

	if (missileLauncherStart->next->serial == t->serial)
	{
		if (missileLauncherStart->next->next)
		{
			mMHead = mMHead->next;
			delete temp;
			missileLauncherStart->next = mMHead;
		}

		else
		{
			delete missileLauncherStart->next;
			mMHead = NULL;
			missileLauncherStart->next = mMHead;
		}
	}
	else
	{
		while(temp && temp->next)
		{
			if (temp->next->serial == t->serial)
			{
				if (temp->next->next)
				{
					temp1 = temp->next;
					temp->next = temp1->next;
					delete temp1;
				}
				else{
					delete temp->next;
					temp->next = NULL;
				}
			}
			temp = temp->next;
		}
	}
}


typedef struct AircraftMissile{

	double x, y, z, speed;

	int serial;

	struct AircraftMissile *next;

	void throwAircraftMissile(){

		glPushMatrix();{

			glTranslatef(x,y+2,z+11);
			glRotatef(180,1,0,0);
			missile();

		}glPopMatrix();
	}

}aircraftMissile;
aircraftMissile *aircraftMissileStart, *aMHead;

void insertMissile(aircraftMissile *t)
{
	aircraftMissile *temp;
	if (aMHead == NULL)
	{
		aMHead = t;
		aircraftMissileStart->next = aMHead;
		aMHead->next = NULL;
	}

	else
	{
		temp = aircraftMissileStart->next;
		while(temp->next)
		{
			temp = temp->next;
		}

		temp->next = t;

	}

}

void removeMissile(aircraftMissile *t)
{
	aircraftMissile *temp, *temp1;

	temp = aircraftMissileStart->next;

	if (aircraftMissileStart->next->serial == t->serial)
	{
		if (aircraftMissileStart->next->next)
		{
			aMHead = aMHead->next;
			delete temp;
			aircraftMissileStart->next = aMHead;
		}

		else
		{
			delete temp;
			aMHead = NULL;
			aircraftMissileStart->next = aMHead;
		}
	}
	else
	{
		while(temp && temp->next)
		{
			if (temp->next->serial == t->serial)
			{
				if (temp->next->next)
				{
					temp1 = temp->next;
					temp->next = temp1->next;
					delete temp1;
				}
				else{
					delete temp->next;
					temp->next = NULL;
				}
			}
			temp = temp->next;
		}

	}
}

typedef struct Aeroplane{

	double x, y, z, speed, tp1, tp2, tp3, tp4, tp5;

	int serial;

	struct Aeroplane *next;

	void drawAeroplane() {
		//lengthX = 72
		//lengthY = 20
		//lengthZ = 20

		GLUquadricObj *obj = gluNewQuadric();
		glColor3f(1, 1, 1);

		glPushMatrix();{

			glTranslatef(x+25,y+10,z+0);

			//head

			glEnable(GL_TEXTURE_2D); {
				glBindTexture(GL_TEXTURE_2D, aircraftBodyImg);
				glPushMatrix(); {
					glTranslatef(-25, 0, 10);
					glRotatef(90, 0, 1, 0);
					gluQuadricTexture(obj, GL_TRUE);
					gluCylinder(obj, 0, 10, 25, 25, 25);
				}glPopMatrix();


				//body

				glPushMatrix(); {
					glTranslatef(0, 0, 10);
					glRotatef(90, 0, 1, 0);
					gluQuadricTexture(obj, GL_TRUE);
					gluCylinder(obj, 10, 10, 30, 25, 25);
				}glPopMatrix();

				glPushMatrix(); {
					glTranslatef(7, 20, 8.1);
					glRotatef(90, 0, 1, 0);
					gluQuadricTexture(obj, GL_TRUE);
					gluCylinder(obj, 0, 2, 10, 25, 25);
				}glPopMatrix();

				glPushMatrix(); {
					glTranslatef(7, -20, 8.1);
					glRotatef(90, 0, 1, 0);
					gluQuadricTexture(obj, GL_TRUE);
					gluCylinder(obj, 0, 2, 10, 25, 25);
				}glPopMatrix();


				//back
				glPushMatrix(); {
					glTranslatef(30, 0, 10);
					glRotatef(90, 0, 1, 0);
					gluQuadricTexture(obj, GL_TRUE);
					gluCylinder(obj, 10, 3, 15, 25, 25);
				}glPopMatrix();

				glPushMatrix(); {
					glTranslatef(45, 0, 10);
					glScalef(0, 3, 3);
					gluQuadricTexture(obj, GL_TRUE);
					gluSphere(obj, 1, 25, 25);
				}glPopMatrix();

			}glDisable(GL_TEXTURE_2D);



			////


			glEnable(GL_TEXTURE_2D); {
				glBindTexture(GL_TEXTURE_2D, usImg);
				glPushMatrix(); {
					glTranslatef(40, -6.25, 13);
					glScalef(.5, .5, 1);
					glRotatef(-90, 1, 0, 0);
					gluQuadricTexture(obj, GL_TRUE);
					wing();
				}glPopMatrix();
			}glDisable(GL_TEXTURE_2D);

			glEnable(GL_TEXTURE_2D); {
				glBindTexture(GL_TEXTURE_2D, wingImg);

				glPushMatrix(); {
					glTranslatef(10, -9, 0);
					wing();

				}glPopMatrix();

				glPushMatrix(); {
					glTranslatef(10, 9, 25);
					glRotatef(180, 1, 0, 0);
					wing();

				}glPopMatrix();

				glPushMatrix(); {
					glTranslatef(38, -3, 0);
					tail1();

				}glPopMatrix();

				glPushMatrix(); {
					glTranslatef(38, 3, 0);
					tail2();

				}glPopMatrix();

			}glDisable(GL_TEXTURE_2D);

		}glPopMatrix();

	}

}aeroplane;
aeroplane *aeroplaneStart, *aeroplaneHead;

void insertAeroplane(aeroplane *t)
{
	aeroplane *temp;
	if (aeroplaneHead == NULL)
	{
		aeroplaneHead = t;
		aeroplaneStart->next = aeroplaneHead;
		aeroplaneHead->next = NULL;
	}

	else
	{
		temp = aeroplaneStart->next;
		while(temp->next)
		{
			temp = temp->next;
		}

		temp->next = t;

	}

}


void removeAeroplane(aeroplane *t)
{
	aeroplane *temp, *temp1;

	temp = aeroplaneStart->next;

	if (aeroplaneStart->next->serial == t->serial)
	{
		if (aeroplaneStart->next->next)
		{
			aeroplaneHead = aeroplaneHead->next;
			delete temp;
			aeroplaneStart->next = aeroplaneHead;
		}

		else
		{
			delete aeroplaneStart->next;
			aeroplaneHead = NULL;
			aeroplaneStart->next = aeroplaneHead;
		}
	}
	else
	{
		while(temp && temp->next)
		{
			if (temp->next->serial == t->serial)
			{
				if (temp->next->next)
				{
					temp1 = temp->next;
					temp->next = temp1->next;
					delete temp1;
				}
				else{
					delete temp->next;
					temp->next = NULL;
				}
			}
			temp = temp->next;
		}
	}
}


typedef struct Helicopter{

	double x, y, z, speed, tp1, tp2, tp3, tp4, tp5;

	int serial;

	struct Helicopter *next;

	void drawHelicopter()
	{
		//lengthX = 75
		//lengthY = 20
		//lengthZ = 26

		GLUquadricObj *obj = gluNewQuadric();
		glColor3f(1, 1, 1);

		glPushMatrix(); {
			glTranslatef(x+19,y+10,z);

			//head

			glPushMatrix(); {
				glTranslatef(0, 0, 10);

				glEnable(GL_TEXTURE_2D); {
					glBindTexture(GL_TEXTURE_2D, militryHImg);
					glPushMatrix(); {
						glTranslatef(-14, 0, 10);
						gluQuadricTexture(obj, GL_TRUE);
						gluSphere(obj, 5, 25, 25);
					}glPopMatrix();

					glPushMatrix(); {
						glTranslatef(-15, 0, 10);
						glRotatef(90, 0, 1, 0);
						gluQuadricTexture(obj, GL_TRUE);
						gluCylinder(obj, 5, 10, 15, 25, 25);
					}glPopMatrix();


					//body

					glPushMatrix(); {
						glTranslatef(0, 0, 10);
						glRotatef(90, 0, 1, 0);
						gluQuadricTexture(obj, GL_TRUE);
						gluCylinder(obj, 10, 10, 30, 25, 25);
					}glPopMatrix();

					//back
					glPushMatrix(); {
						glTranslatef(30, 0, 10);
						glRotatef(90, 0, 1, 0);
						gluQuadricTexture(obj, GL_TRUE);
						gluCylinder(obj, 10, 3, 25, 25, 25);
					}glPopMatrix();

					glPushMatrix(); {
						glTranslatef(55, 0, 10);
						glScalef(0, 3, 3);
						gluQuadricTexture(obj, GL_TRUE);
						gluSphere(obj, 1, 25, 25);
					}glPopMatrix();

				}glDisable(GL_TEXTURE_2D);



				////


				glEnable(GL_TEXTURE_2D); {
					glBindTexture(GL_TEXTURE_2D, usImg);
					glPushMatrix(); {
						glTranslatef(50, -6.25, 13);
						glScalef(.5, .5, 1.25);
						glRotatef(-90, 1, 0, 0);
						gluQuadricTexture(obj, GL_TRUE);
						wing();
					}glPopMatrix();
				}glDisable(GL_TEXTURE_2D);

				glPushMatrix(); {
					glTranslatef(15, 0, 20);
					glColor3f(0, 0, 0);
					gluCylinder(obj, 1, 1, 5, 25, 25);
				}glPopMatrix();

				glPushMatrix(); {
					glTranslatef(15, 0, 25);
					glRotatef(rotor, 0, 0, 1);

					glPushMatrix(); {
						glScalef(40, 2, 1);
						glutSolidCube(1);
					}glPopMatrix();

					glPushMatrix(); {
						glScalef(2, 40, 1);
						glutSolidCube(1);
					}glPopMatrix();

					glPushMatrix(); {
						glutSolidSphere(2, 25, 25);
					}glPopMatrix();
				}glPopMatrix();

				glPushMatrix(); {
					glTranslatef(52.5, -1, 25);
					glRotatef(90, 1, 0, 0);
					glColor3f(0, 0, 0);
					gluCylinder(obj, 1, 1, 2, 25, 25);
				}glPopMatrix();

				glPushMatrix(); {
					glTranslatef(52.5, -3, 25);
					glRotatef(rotor, 0, 1, 0);

					glPushMatrix(); {
						glScalef(1, 1, 10);
						glutSolidCube(1);
					}glPopMatrix();

					glPushMatrix(); {
						glScalef(10, 1, 1);
						glutSolidCube(1);
					}glPopMatrix();

					glPushMatrix(); {
						glutSolidSphere(1, 25, 25);
					}glPopMatrix();
				}glPopMatrix();

			}glPopMatrix();

			// lower part

			glPushMatrix(); {

				glTranslatef(0, 0, 6.5);

				glPushMatrix(); {
					glTranslatef(15, -15, 0);
					glScalef(30, 1, 1);
					glutSolidCube(1);
				}glPopMatrix();

				glPushMatrix(); {
					glTranslatef(5, -11.5, 4);
					glRotatef(45, 1, 0, 0);
					glScalef(1, 10, 1);
					glutSolidCube(1);
				}glPopMatrix();

				glPushMatrix(); {
					glTranslatef(25, -11.5, 4);
					glRotatef(45, 1, 0, 0);
					glScalef(1, 10, 1);
					glutSolidCube(1);
				}glPopMatrix();

				glPushMatrix(); {
					glTranslatef(15, 15, 0);
					glScalef(30, 1, 1);
					glutSolidCube(1);
				}glPopMatrix();

				glPushMatrix(); {
					glTranslatef(5, 11.5, 4);
					glRotatef(-45, 1, 0, 0);
					glScalef(1, 10, 1);
					glutSolidCube(1);
				}glPopMatrix();

				glPushMatrix(); {
					glTranslatef(25, 11.5, 4);
					glRotatef(-45, 1, 0, 0);
					glScalef(1, 10, 1);
					glutSolidCube(1);
				}glPopMatrix();

			}glPopMatrix();

			///

		}glPopMatrix();
	}

}helicopter;
helicopter *helicopterStart, *helicopterHead;

void insertHelicopter(helicopter *t)
{
	helicopter *temp;
	if (helicopterHead == NULL)
	{
		helicopterHead = t;
		helicopterStart->next = helicopterHead;
		helicopterHead->next = NULL;
	}

	else
	{
		temp = helicopterStart->next;
		while(temp->next)
		{
			temp = temp->next;
		}

		temp->next = t;

	}

}


void removeHelicopter(helicopter *t)
{
	helicopter *temp, *temp1;

	temp = helicopterStart->next;

	if (helicopterStart->next->serial == t->serial)
	{
		if (helicopterStart->next->next)
		{
			helicopterHead = helicopterHead->next;
			delete temp;
			helicopterStart->next = helicopterHead;
		}

		else
		{
			delete helicopterStart->next;
			helicopterHead = NULL;
			helicopterStart->next = helicopterHead;
		}
	}
	else
	{
		while(temp && temp->next)
		{
			if (temp->next->serial == t->serial)
			{
				if (temp->next->next)
				{
					temp1 = temp->next;
					temp->next = temp1->next;
					delete temp1;
				}
				else{
					delete temp->next;
					temp->next = NULL;
				}
			}
			temp = temp->next;
		}
	}
}


void missileLauncher(){
	GLUquadricObj *obj = gluNewQuadric();

	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, launcherImg);
		gluQuadricTexture(obj, GL_TRUE);

		glPushMatrix();{

			glColor3f(1,1,1);
			glTranslatef(-3.5,6,26);
			glRotatef(25,1,0,0);

			glPushMatrix(); {

				glTranslatef(0, 0, .5);
				glScalef(1, 1, 0);
				gluSphere(obj, 1, 25, 25);
			}glPopMatrix();

			glPushMatrix();{

				glTranslatef(0, 0, 0);
				gluCylinder(obj, 1, 1, 15, 25, 25);

			}glPopMatrix();

			glPushMatrix();{

				glTranslatef(0, 2.75, 18);
				gluCylinder(obj, .75, .5, 8, 25, 25);

			}glPopMatrix();

			glPushMatrix(); {

				glTranslatef(0, 2.75, 26);
				gluSphere(obj, .75, 5, 25);
			}glPopMatrix();

			glPushMatrix();{

				glTranslatef(0, 2.5, 22);
				glRotatef(90,1,0,0);
				gluCylinder(obj, .5, .5, 1, 25, 25);

			}glPopMatrix();

			glPushMatrix();{

				glTranslatef(0, -1.5, 18);
				glRotatef(90,1,0,0);
				gluCylinder(obj, .8, .8, 6, 25, 25);

			}glPopMatrix();

			glPushMatrix();{

				glTranslatef(0, 0, 15);
				gluCylinder(obj, 1, 1.5, 2, 25, 25);

			}glPopMatrix();

			glPushMatrix();{

				glTranslatef(0, 0, 17);
				gluCylinder(obj, 1.5, 1.5, 10, 25, 25);

			}glPopMatrix();

			glPushMatrix();{

				glTranslatef(0, 0, 27);
				gluCylinder(obj, 1.5, 2.5, 5, 25, 25);

			}glPopMatrix();

			glPushMatrix(); {

				glTranslatef(0, 0, 32);
				glScalef(.8,.8,2);
				gluSphere(obj, 2, 25, 25);
			}glPopMatrix();

		}glPopMatrix();

	}glDisable(GL_TEXTURE_2D);
}

void man()
{

	GLUquadricObj *obj = gluNewQuadric();
	glColor3f(1, 1, 1);

	glPushMatrix();{
		glTranslatef(manX+6,manY+3,manZ);
		glRotatef(manAngle,0,0,1);

		glPushMatrix(); {
			glTranslatef(0, 0, 20);

			glEnable(GL_TEXTURE_2D); {
				glBindTexture(GL_TEXTURE_2D, militryHImg);
				gluQuadricTexture(obj, GL_TRUE);

				//body
				glPushMatrix();
				{
					glTranslatef(0, 0, 0);
					glScalef(1, .6, 1);
					gluCylinder(obj, 5, 5, 15, 25, 25);

				}glPopMatrix();


				//shoulder
				glPushMatrix();
				{
					glTranslatef(0, 0, 15);
					glScalef(1, .6, 1);
					gluCylinder(obj, 5, 1.5, 5, 25, 25);

				}glPopMatrix();

			}glDisable(GL_TEXTURE_2D);


			//head f
			glEnable(GL_TEXTURE_2D); {
				glBindTexture(GL_TEXTURE_2D, manImg);
				glPushMatrix(); {

					double equ[4];
					equ[0] = 0;
					equ[1] = -1;
					equ[2] = 0;
					equ[3] = 0;

					glTranslatef(0, 0, 28);
					glScalef(.55, .4, 1.2);
					glClipPlane(GL_CLIP_PLANE0, equ);
					glEnable(GL_CLIP_PLANE0);
					gluQuadricTexture(obj, GL_TRUE);
					gluSphere(obj, 5, 25, 25);
					glDisable(GL_CLIP_PLANE0);

				}glPopMatrix();
			}glDisable(GL_TEXTURE_2D);

			//head b
			glEnable(GL_TEXTURE_2D); {
				glBindTexture(GL_TEXTURE_2D, hairImg);
				glPushMatrix(); {

					double equ[4];
					equ[0] = 0;
					equ[1] = 1;
					equ[2] = 0;
					equ[3] = 0;

					glTranslatef(0, 0, 28);
					glScalef(.55, .4, 1.2);
					glClipPlane(GL_CLIP_PLANE0, equ);
					glEnable(GL_CLIP_PLANE0);
					gluQuadricTexture(obj, GL_TRUE);
					gluSphere(obj, 5, 25, 25);
					glDisable(GL_CLIP_PLANE0);

				}glPopMatrix();
			}glDisable(GL_TEXTURE_2D);

			glEnable(GL_TEXTURE_2D); {
				glBindTexture(GL_TEXTURE_2D, skinImg);
				gluQuadricTexture(obj, GL_TRUE);

				//neck
				glPushMatrix();
				{
					glTranslatef(0, 0, 20);
					glScalef(1, .6, 1);
					gluCylinder(obj, 1.5, 1.5, 3, 25, 25);

				}glPopMatrix();

				glPushMatrix();{

					glRotatef(0, 0, 0, 0);

					// hand l
					glPushMatrix(); {
						glTranslatef(0, 2, 0);
						glRotatef(5, 0, 0, 1);
						glPushMatrix();
						{
							glTranslatef(-5.5, -2, 14);
							glRotatef(50, 1, 0, 0);
							glScalef(.8, .6, 1);
							gluCylinder(obj, 1, 1, 10, 25, 25);

						}glPopMatrix();

						glPushMatrix(); {
							glTranslatef(-5.2, -10, 20.5);
							glRotatef(-45, 0, 0, 1);
							glScalef(1.2, .6, 1);
							gluSphere(obj, 1, 25, 25);
						}glPopMatrix();
					}glPopMatrix();

					glPushMatrix(); {

						glTranslatef(-5, 0, 14);
						glScalef(1, 1, 1);
						gluSphere(obj, 1, 25, 25);
					}glPopMatrix();



					glPushMatrix(); {
						glTranslatef(5, 0, 14);
						glScalef(1, 1, 1);
						gluSphere(obj, 1, 25, 25);
					}glPopMatrix();

					// hand r
					glPushMatrix(); {
						glTranslatef(0, 2, 0);
						glRotatef(-40, 0, 0, 1);
						glPushMatrix();
						{
							glTranslatef(5.5, 1.6, 14);
							glRotatef(60, 1, 0, 0);
							glScalef(.8, .6, 1);
							gluCylinder(obj, 1, 1, 12, 25, 25);

						}glPopMatrix();

						glPushMatrix(); {

							glTranslatef(5.2, -9, 20);
							glRotatef(45, 0, 0, 1);
							glScalef(1.2, .6, 1);
							gluSphere(obj, 1, 25, 25);

						}glPopMatrix();
					}glPopMatrix();

				}glPopMatrix();
			}glDisable(GL_TEXTURE_2D);


		}glPopMatrix();

		///
		glEnable(GL_TEXTURE_2D); {
			glBindTexture(GL_TEXTURE_2D, clothImg);
			gluQuadricTexture(obj, GL_TRUE);
			//leg
			glPushMatrix();
			{
				glTranslatef(-2.5, 0, 2);
				glScalef(.8, 1, 1);
				gluCylinder(obj, 2, 2, 18, 25, 25);

			}glPopMatrix();

			glPushMatrix();
			{
				glTranslatef(2.5, 0, 2);
				glScalef(.8, 1, 1);
				gluCylinder(obj, 2, 2, 18, 25, 25);

			}glPopMatrix();
		}glDisable(GL_TEXTURE_2D);

		glEnable(GL_TEXTURE_2D); {
			glBindTexture(GL_TEXTURE_2D, shoeImg);
			gluQuadricTexture(obj, GL_TRUE);
			//foot
			glPushMatrix(); {

				glTranslatef(-2.5, -1, 2);
				glScalef(.8, 1.5, 1);
				gluSphere(obj, 2, 25, 25);

			}glPopMatrix();

			glPushMatrix(); {

				glTranslatef(2.5, -1, 2);
				glScalef(.8, 1.5, 1);
				gluSphere(obj, 2, 25, 25);

			}glPopMatrix();

		}glDisable(GL_TEXTURE_2D);


		//missile launcher

		missileLauncher();

	}glPopMatrix();
	glPushMatrix();{
		glColor3f(1,0,0);
		glTranslatef(launcherX,launcherY,launcherZ);
		glutSolidSphere(1,25,25);
	}glPopMatrix();
}

bool collision(double x1, double y1, int w1, int h1, double x2, double y2, int w2, int h2){

	if (x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && h1 + y1 > y2) {
		return true;
	}
	return false;
}


/****************************** GridLines and Axes ***********************************/

void gridAndAxis() {
	// draw the three major AXES
	if (canDrawAxis == 1) {
		glBegin(GL_LINES);
		//X axis
		glColor3f(0, 1, 0);	//100% Green
		glVertex3f(-150, 0, 0);
		glVertex3f(150, 0, 0);

		//Y axis
		glColor3f(0, 0, 1);	//100% Blue
		glVertex3f(0, -150, 0);	// intentionally extended to -150 to 150, no big deal
		glVertex3f(0, 150, 0);

		//Z axis
		glColor3f(0, 0, 0);	//100% White
		glVertex3f(0, 0, -150);
		glVertex3f(0, 0, 150);
		glEnd();
	}

	if (canDrawGrid == 1) {
		//some gridlines along the field
		int i;

		glColor3f(1, 0.5, 0.5);	//grey
		glBegin(GL_LINES);
		for (i = -60; i <= 60; i++) {

			if (i == 0)
				continue;	//SKIP the MAIN axes

			//lines parallel to Y-axis
			glVertex3f(i * 5, -300, 0);
			glVertex3f(i * 5, 300, 0);

			//lines parallel to X-axis
			glVertex3f(-300, i * 5, 0);
			glVertex3f(300, i * 5, 0);
		}
		glEnd();

	}
}


void display(){
	//codes for Models, Camera

	//clear the display
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//clear buffers to preset values

	/***************************
	/ set-up camera (view) here
	****************************/ 
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);		//specify which matrix is the current matrix

	//initialize the matrix
	glLoadIdentity();				//replace the current matrix with the identity matrix [Diagonals have 1, others have 0]

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera looking?
	//3. Which direction is the camera's UP direction?

	//gluLookAt(0,-150,20,	0,0,0,	0,0,1);
	gluLookAt(cameraRadius*sin(cameraAngle), -cameraRadius*cos(cameraAngle), cameraHeight,		0,0,100,		0,0,1);

	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/**************************************************
	/ Grid and axes Lines(You can remove them if u want)
	***************************************************/
	// draw the three major AXES

	gridAndAxis();



	/****************************
	/ Add your objects from here
	****************************/

	GLUquadricObj *obj = gluNewQuadric();

	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, skyImg);
		glPushMatrix(); {
			glColor3f(1, 1, 1);

			gluQuadricTexture(obj, GL_TRUE);
			gluSphere(obj, 600, 25, 25);
		}glPopMatrix();
	}glDisable(GL_TEXTURE_2D);

	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D); {
		glBindTexture(GL_TEXTURE_2D, grassImg);
		glBegin(GL_QUADS); {
			glTexCoord2f(0, 0);
			glVertex3f(-350, 350, 0);

			glTexCoord2f(1, 0);
			glVertex3f(-350, -350, 0);

			glTexCoord2f(0, 1);
			glVertex3f(350, -350, 0);

			glTexCoord2f(1, 1);
			glVertex3f(350, 350, 0);
		}glEnd();
	}glDisable(GL_TEXTURE_2D);


	aeroplane *tempA;
	tempA = aeroplaneStart;
	while (tempA != NULL)
	{
		tempA->drawAeroplane();
		tempA = tempA->next;
	}


	helicopter *tempH;
	tempH = helicopterStart;
	while (tempH != NULL)
	{
		tempH->drawHelicopter();
		tempH = tempH->next;
	}

	manMissile * tempmM;
	tempmM = missileLauncherStart->next;
	while(tempmM){
		tempmM->throwManMissile();
		tempmM = tempmM->next;
	}


	aircraftMissile * tempaM;
	tempaM = aircraftMissileStart->next;
	while(tempaM){
		tempaM->throwAircraftMissile();
		tempaM = tempaM->next;
	}

	if (!notLose){
		glPushMatrix(); {
			man();
		}glPopMatrix();
	}
	else{
		glPushMatrix(); {
			glTranslatef(0,0,manLenZ*2);
			glRotatef(90,1,0,0);
			man();
		}glPopMatrix();

	}






	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}

void animate(){

	//codes for any changes in Models, Camera
	//cameraAngle += cameraAngleDelta;	// camera will rotate at 0.002 radians per frame.
	if (!notLose){
		rotor += 5;

		if (helicopterDestroy == 1 && aeroplaneDestroy == 1 && wave1 == 0){
			aeroplane *a1;
			int i,j;

			for(i = 0, j = 0 ;i < 4; i++){
				a1 = new aeroplane;
				a1->serial = airCraft++;
				a1->speed = (double) ((rand() % 5) / 5) + .3;
				a1->x = 350;
				a1->y = -170 + j;
				a1->z = 220;
				a1->tp1 = 150;a1->tp2 = 80; a1->tp3 = 10; a1->tp4 = -60; a1->tp5 = -130;
				a1->next = NULL;
				insertAeroplane(a1);
				j += 70;
			}


			helicopter *h1;

			for(i = 0, j = 0;i < 4; i++){
				h1 = new helicopter;
				h1->serial = heliCopter++;
				h1->speed = (double) ((rand() % 5)) / 5 + .2;
				h1->x = 350;
				h1->y = 90+j;
				h1->z = 220;
				h1->tp1 = 150;h1->tp2 = 80; h1->tp3 = 10; h1->tp4 = -60; h1->tp5 = -130;
				h1->next = NULL;
				insertHelicopter(h1);
				j += 40;
			}


			wave1 = 1;
		}

		aircraftMissile *am;

		aeroplane *a, *a1, *a2;

		a = aeroplaneStart->next;
		while(a){
			a1 = a->next;
			if (a->x > -400){

				a->x -= a->speed;

				if (a->tp1 && a->x <= a->tp1){
				am = new aircraftMissile;
				am->serial = airBullet++;
				am->speed = (double) ((rand() % 5)) / 5 + .2;
				am->x = a->x;
				am->y = a->y;
				am->z = a->z;
				am->next = NULL;
				insertMissile(am);
				a->tp1 = 0;
				}
				else if (a->tp2 && a->x <= a->tp2){
				am = new aircraftMissile;
				am->serial = airBullet++;
				am->speed = (double) ((rand() % 5)) / 5 + .2;
				am->x = a->x;
				am->y = a->y;
				am->z = a->z;
				am->next = NULL;
				insertMissile(am);
				a->tp2 = 0;
				}
				else if (a->tp3 && a->x <= a->tp3){
				am = new aircraftMissile;
				am->serial = airBullet++;
				am->speed = (double) ((rand() % 5)) / 5 + .2;
				am->x = a->x;
				am->y = a->y;
				am->z = a->z;
				am->next = NULL;
				insertMissile(am);
				a->tp3 = 0;
				}
				else if (a->tp4 && a->x <= a->tp4){
				am = new aircraftMissile;
				am->serial = airBullet++;
				am->speed = (double) ((rand() % 5)) / 5 + .2;
				am->x = a->x;
				am->y = a->y;
				am->z = a->z;
				am->next = NULL;
				insertMissile(am);
				a->tp4 = 0;
				}
				else if (a->tp5 && a->x <= a->tp5){
				am = new aircraftMissile;
				am->serial = airBullet++;
				am->speed = (double) ((rand() % 5)) / 5 + .2;
				am->x = a->x;
				am->y = a->y;
				am->z = a->z;
				am->next = NULL;
				insertMissile(am);
				a->tp5 = 0;
				}

				a = a->next;
			}

			else{
				a->x = 350;
				a->tp1 = 150;a->tp2 = 80; a->tp3 = 10; a->tp4 = -60; a->tp5 = -130;

			}	
		}

		helicopter *h, *h1, *h2;

		h = helicopterStart->next;
		while(h){
			h1 = h->next;
			if (h->x > -400){

				h->x -= h->speed;

				if (h->tp1 && h->x <= h->tp1){
				am = new aircraftMissile;
				am->serial = airBullet++;
				am->speed = (double) ((rand() % 5)) / 5 + .2;
				am->x = h->x;
				am->y = h->y;
				am->z = h->z;
				am->next = NULL;
				insertMissile(am);
				h->tp1 = 0;
				}
				else if (h->tp2 && h->x <= h->tp2){
				am = new aircraftMissile;
				am->serial = airBullet++;
				am->speed = (double) ((rand() % 5)) / 5 + .2;
				am->x = h->x;
				am->y = h->y;
				am->z = h->z;
				am->next = NULL;
				insertMissile(am);
				h->tp2 = 0;
				}
				else if (h->tp3 && h->x <= h->tp3){
				am = new aircraftMissile;
				am->serial = airBullet++;
				am->speed = (double) ((rand() % 5)) / 5 + .2;
				am->x = h->x;
				am->y = h->y;
				am->z = h->z;
				am->next = NULL;
				insertMissile(am);
				h->tp3 = 0;
				}
				else if (h->tp4 && h->x <= h->tp4){
				am = new aircraftMissile;
				am->serial = airBullet++;
				am->speed = (double) ((rand() % 5)) / 5 + .2;
				am->x = h->x;
				am->y = h->y;
				am->z = h->z;
				am->next = NULL;
				insertMissile(am);
				h->tp4 = 0;
				}
				else if (h->tp5 && h->x <= h->tp5){
				am = new aircraftMissile;
				am->serial = airBullet++;
				am->speed = (double) ((rand() % 5)) / 5 + .2;
				am->x = h->x;
				am->y = h->y;
				am->z = h->z;
				am->next = NULL;
				insertMissile(am);
				h->tp5 = 0;
				}

				h = h->next;
			}

			else{
				h->x = 350;
				h->tp1 = 150;h->tp2 = 80; h->tp3 = 10; h->tp4 = -60; h->tp5 = -130;

			}	
		}


		manMissile *mM, *mM1, *mM2;
		mM = missileLauncherStart->next;
		while(mM){
			mM1 = mM->next;

			a = aeroplaneStart->next;
			while (a){
				a1 = a->next;
				if (abs(a->z - (mM->z+missileLenZ)) <= 2.0 && collision(mM->x,mM->y,missileLenX,missileLenY,a->x,a->y,aeroplaneLenX,aeroplaneLenY) ){
					a2 = a;
					removeAeroplane(a2);
					aeroplaneDestroy++;
					a = a1;
				}
				else
					a = a->next;
			}

			h = helicopterStart->next;
			while (h){
				h1 = h->next;
				if (abs(h->z - (mM->z+missileLenZ)) <= 2.0 && collision(mM->x,mM->y,missileLenX,missileLenY,h->x,h->y,helicopterLenX,helicopterLenY) ){
					h2 = h;
					removeHelicopter(h2);
					helicopterDestroy++;
					h = h1;
				}
				else
					h = h->next;
			}


			if (mM->z < 250){
				mM->z += mM->speed;
				mM = mM->next;
			}
			else{
				mM2 = mM;
				removeManMissile(mM2);
				mM = mM1;

			}	
		}


		aircraftMissile *aM, *aM1, *aM2;
		aM = aircraftMissileStart->next;
		while(aM){
			aM1 = aM->next;
			if (abs(aM->z - (manZ+manLenZ)) <= 5 && collision(aM->x,aM->y,missileLenX,missileLenY,manX,manY,manLenX,manLenY) ){
				notLose = true;
				aM->z = 40;
				aM = aM->next;
			}
			else if (aM->z > 20){
				aM->z -= aM->speed;
				aM = aM->next;
			}
			else{
				aM2 = aM;
				removeMissile(aM2);
				aM = aM1;

			}	
		}
	}

	//codes for any changes in Models
	printf("H: %d, A: %d\n",helicopterDestroy,aeroplaneDestroy);

	//MISSING SOMETHING? -- YES: add the following
	glutPostRedisplay();	//this will call the display AGAIN

}

void init(){
	srand(time(NULL));

	//codes for initialization
	loadImage();
	cameraAngle = 0;	//angle in radian

	manX=0, manY=0, manZ=0;
	launcherX = 2.6;
	launcherY = -7.6;
	launcherZ = 62;

	missileLauncherStart = new manMissile;
	missileLauncherStart->next = NULL;

	aircraftMissileStart = new aircraftMissile;
	aircraftMissileStart->next = NULL;

	aeroplaneStart = new aeroplane;
	aeroplaneStart->next = NULL;

	helicopterStart = new helicopter;
	helicopterStart->next = NULL;

	aeroplane *a1;
	a1 = new aeroplane;
	a1->serial = airCraft++;
	a1->speed = (double) ((rand() % 5) / 5) + .3;
	a1->x = 350;
	a1->y = -70;
	a1->z = 220;
	a1->tp1 = 150;a1->tp2 = 80; a1->tp3 = 10; a1->tp4 = -60; a1->tp5 = -130;
	a1->next = NULL;
	insertAeroplane(a1);

	helicopter *h1;
	h1 = new helicopter;
	h1->serial = heliCopter++;
	h1->speed = (double) ((rand() % 5)) / 5 + .2;
	h1->x = 350;
	h1->y = 70;
	h1->z = 220;
	h1->tp1 = 150;h1->tp2 = 80; h1->tp3 = 10; h1->tp4 = -60; h1->tp5 = -130;
	h1->next = NULL;
	insertHelicopter(h1);

	cameraAngleDelta = .001;

	cameraRadius = 380;
	cameraHeight = 180;

	//clear the screen
	glClearColor(0,0,0, 0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	/*
	gluPerspective() — set up a perspective projection matrix

	fovy -         Specifies the field of view angle, in degrees, in the y direction.
	aspect ratio - Specifies the aspect ratio that determines the field of view in the x direction. The aspect ratio is the ratio of x (width) to y (height).
	zNear -        Specifies the distance from the viewer to the near clipping plane (always positive).
	zFar  -        Specifies the distance from the viewer to the far clipping plane (always positive).
	*/

	gluPerspective(70,	1,	0.1,	10000.0);

}

void keyboardListener(unsigned char key, int x,int y){
	if (!notLose){
		switch(key){

		case '1':
			manAngle = 0;
			manAngle = -45;
			if (manX > -200 && manY > -200){
				manX -= 2;
				launcherX = manX - 5.6;
				manY -= 2;
				launcherY = manY - 2.5;
			}
			break;

		case '2':
			manAngle = 0;
			if (manY > -200){
				manY -= 2;
				launcherX = manX + 2.6;
				launcherY = manY - 7.6;
			}
			break;

		case '3':
			manAngle = 0;
			manAngle = 45;
			if (manX < 200 && manY > -200){
				manX += 2;
				launcherX = manX + 10.6;
				manY -= 2;
				launcherY = manY - 6.5;
			}
			break;
		case '4':
			manAngle = 0;
			manAngle = -90;
			if (manX > -200){
				manX -= 2;
				launcherX = manX - 3.6;
				launcherY = manY + 5.6;
			}
			break;

		case '5':
			manMissile *t;
			t = new manMissile;
			t->x = launcherX;
			t->y = launcherY;
			t->z = launcherZ;
			t->speed = .25;
			t->serial = manBullet++;
			t->next = NULL;
			insertManMissile(t);
			break;
		case '6':
			manAngle = 0;
			manAngle = 90;	
			if (manX < 200){
				manX += 2;
				launcherX = manX + 15.6;
				launcherY = manY - .6;
			}
			break;
		case '8':
			manAngle = 0;
			manAngle = 180;
			if (manY < 200){
				manY += 2;
				launcherX = manX + 9.6;
				launcherY = manY +12.6;
			}
			break;

		case 'g':
			canDrawGrid = !canDrawGrid;
			break;

		case 'h':
			canDrawAxis = !canDrawAxis;
			break;

		case '9':
			manAngle = 0;
			manAngle = 135;
			if (manX < 200 && manY < 200){
				manY += 2;
				launcherY = manY + 7.6;
				manX += 2;
				launcherX = manX + 15.5;
			}
			break;

		case '7':
			manAngle = 0;
			manAngle = -135;
			if (manX > -200 && manY < 200){
				manX -= 2;
				launcherX = manX + 1.5;
				manY += 2;
				launcherY = manY + 10.5;
			}
			break;

		case 'f':

			break;
		case 'k':
			break;
		case 'l':

			break;

		default:
			break;
		}
	}
}

void specialKeyListener(int key, int x,int y){
	switch(key){
	case GLUT_KEY_DOWN:		//down arrow key
		cameraRadius += 10;
		break;
	case GLUT_KEY_UP:		// up arrow key
		if(cameraRadius > 10)
			cameraRadius -= 10;
		break;

	case GLUT_KEY_RIGHT:
		cameraAngle += 0.01;
		break;
	case GLUT_KEY_LEFT:
		cameraAngle -= 0.01;
		break;

	case GLUT_KEY_PAGE_UP:
		cameraHeight += 10;
		break;
	case GLUT_KEY_PAGE_DOWN:
		cameraHeight -= 10;
		break;

	case GLUT_KEY_INSERT:
		break;

	case GLUT_KEY_HOME:
		cameraAngleDelta = 0.001; 
		break;
	case GLUT_KEY_END:
		cameraAngleDelta = 0;
		break;

	default:
		break;
	}
}

void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
	case GLUT_LEFT_BUTTON:
		if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
			cameraAngleDelta = -cameraAngleDelta;	
		}
		break;

	case GLUT_RIGHT_BUTTON:
		//........
		break;

	case GLUT_MIDDLE_BUTTON:
		//........
		break;

	default:
		break;
	}
}

int main(int argc, char **argv){

	glutInit(&argc,argv);							//initialize the GLUT library

	glutInitWindowSize(1400, 750);
	glutInitWindowPosition(50, 50);

	/*
	glutInitDisplayMode - inits display mode
	GLUT_DOUBLE - allows for display on the double buffer window
	GLUT_RGBA - shows color (Red, green, blue) and an alpha
	GLUT_DEPTH - allows for depth buffer
	*/
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	

	glutCreateWindow("Air Attack 3D");

	init();						//codes for initialization
	
	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)
	
	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);

	glutMouseFunc(mouseListener);

	

	glutMainLoop();		//The main loop of OpenGL
	
	

	return 0;
}
