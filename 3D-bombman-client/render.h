using namespace std;
#include "controls.h"

void DrawSquare(float SquareSize, unsigned int TexID, float TexSize) {
	glBindTexture(GL_TEXTURE_2D, TexID);
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(SquareSize / (2 * TexSize), SquareSize / (2 * TexSize));
	glVertex3f(SquareSize / 2, SquareSize / 2, 0);
	glTexCoord2f(-SquareSize / (2 * TexSize), SquareSize / (2 * TexSize));
	glVertex3f(-SquareSize / 2, SquareSize / 2, 0);
	glTexCoord2f(-SquareSize / (2 * TexSize), -SquareSize / (2 * TexSize));
	glVertex3f(-SquareSize / 2, -SquareSize / 2, 0);
	glTexCoord2f(SquareSize / (2 * TexSize), -SquareSize / (2 * TexSize));
	glVertex3f(SquareSize / 2, -SquareSize / 2, 0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void DrawCubeWithText(float CubeSize, unsigned int TexID) {
	glBindTexture(GL_TEXTURE_2D, TexID);
	glBegin(GL_TRIANGLE_FAN); // UP
	glTexCoord2f(CubeSize / 2, CubeSize / 2);
	glVertex3f(CubeSize / 2, CubeSize / 2, CubeSize / 2);
	glTexCoord2f(-CubeSize / 2, CubeSize / 2);
	glVertex3f(-CubeSize / 2, CubeSize / 2, CubeSize / 2);
	glTexCoord2f(-CubeSize / 2, -CubeSize / 2);
	glVertex3f(-CubeSize / 2, CubeSize / 2, -CubeSize / 2);
	glTexCoord2f(CubeSize / 2, -CubeSize / 2);
	glVertex3f(CubeSize / 2, CubeSize / 2, -CubeSize / 2);
	glEnd();
	glBegin(GL_TRIANGLE_FAN); 
	glTexCoord2f(CubeSize / 2, CubeSize / 2);
	glVertex3f(CubeSize / 2, CubeSize / 2, CubeSize / 2);
	glTexCoord2f(-CubeSize / 2, CubeSize / 2);
	glVertex3f(-CubeSize / 2, CubeSize / 2, CubeSize / 2);
	glTexCoord2f(-CubeSize / 2, -CubeSize / 2);
	glVertex3f(-CubeSize / 2, -CubeSize / 2, CubeSize / 2);
	glTexCoord2f(CubeSize / 2, -CubeSize / 2);
	glVertex3f(CubeSize / 2, -CubeSize / 2, CubeSize / 2);
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(-CubeSize / 2, CubeSize / 2);
	glVertex3f(CubeSize / 2, CubeSize / 2, CubeSize / 2);
	glTexCoord2f(-CubeSize / 2, -CubeSize / 2);
	glVertex3f(CubeSize / 2, - CubeSize / 2, CubeSize / 2);
	glTexCoord2f(CubeSize / 2, -CubeSize / 2);
	glVertex3f(CubeSize / 2, - CubeSize / 2, -CubeSize / 2);
	glTexCoord2f(CubeSize / 2, CubeSize / 2);
	glVertex3f(CubeSize / 2, CubeSize / 2, -CubeSize / 2);
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(CubeSize / 2, CubeSize / 2);
	glVertex3f(CubeSize / 2, -CubeSize / 2, CubeSize / 2);
	glTexCoord2f(-CubeSize / 2, CubeSize / 2);
	glVertex3f(-CubeSize / 2, -CubeSize / 2, CubeSize / 2);
	glTexCoord2f(-CubeSize / 2, -CubeSize / 2);
	glVertex3f(-CubeSize / 2, -CubeSize / 2, -CubeSize / 2);
	glTexCoord2f(CubeSize / 2, -CubeSize / 2);
	glVertex3f(CubeSize / 2, -CubeSize / 2, -CubeSize / 2);
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(CubeSize / 2, CubeSize / 2);
	glVertex3f(CubeSize / 2, CubeSize / 2, -CubeSize / 2);
	glTexCoord2f(-CubeSize / 2, CubeSize / 2);
	glVertex3f(-CubeSize / 2, CubeSize / 2, -CubeSize / 2);
	glTexCoord2f(-CubeSize / 2, -CubeSize / 2);
	glVertex3f(-CubeSize / 2, -CubeSize / 2, -CubeSize / 2);
	glTexCoord2f(CubeSize / 2, -CubeSize / 2);
	glVertex3f(CubeSize / 2, -CubeSize / 2, -CubeSize / 2);
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(-CubeSize / 2, CubeSize / 2);
	glVertex3f(-CubeSize / 2, CubeSize / 2, CubeSize / 2);
	glTexCoord2f(-CubeSize / 2, -CubeSize / 2);
	glVertex3f(-CubeSize / 2, -CubeSize / 2, CubeSize / 2);
	glTexCoord2f(CubeSize / 2, -CubeSize / 2);
	glVertex3f(-CubeSize / 2, -CubeSize / 2, -CubeSize / 2);
	glTexCoord2f(CubeSize / 2, CubeSize / 2);
	glVertex3f(-CubeSize / 2, CubeSize / 2, -CubeSize / 2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void CreateBaseLayer() {
	glColor3f(0, 1, 0);
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			glutWireCube(1);
			glTranslatef(1, 0, 0);
		}
		glTranslatef(-10, 0, 0);
		glTranslatef(0, 0, 1);
	}
	glColor3f(1, 1, 1);

	glTranslatef(2, 1, 0);
	glutWireCube(1);
	glTranslatef(0, 1, 0);
	glutWireCube(1);
	glTranslatef(0, 1, 0);
	glutWireCube(1);
	glTranslatef(0, 0, 1);
	glutWireCube(1);
	glTranslatef(0, 0, 1);
	glutWireCube(1);
	glTranslatef(0, -1, 0);
	glutWireCube(1);
	glTranslatef(0, -1, 0);
	glutWireCube(1);
}

float powF(float num, int numT) {
	float N = num;
	for (int i = 1; i < numT; i++) {
		N *= num;
	}
	return N;
}

void GenerateWorld(){

	glTranslatef(1, 0, 0);
	glTranslatef(WorldSize / 2, -(WorldSize / 2), WorldSize / 2);
	glColor3f(1, 1 - LostLifeTimer / LostLifeTimerMaks, 1 - LostLifeTimer / LostLifeTimerMaks);
	glutSolidCube(WorldSize);
	glColor3f(1, 1, 1);
	glTranslatef(-(WorldSize / 2), WorldSize / 2, -(WorldSize / 2));
	glTranslatef(0, 1, 0);

	for (int i = 0; i < 3; i++) {
		if (OtherLifes[i] > 0) {
			glTranslatef(OtherPos[i].x - 0.5, -0.375, OtherPos[i].z - 0.5);
			DrawCubeWithText(0.25, LegsTex->textureID);
			glTranslatef(0, 0.250, 0);
			DrawCubeWithText(0.25, BodyTex->textureID);
			glTranslatef(0, 0.250, 0);
			DrawCubeWithText(0.25, HeadTex->textureID);
			glTranslatef(-OtherPos[i].x + 0.5, -0.125, -OtherPos[i].z + 0.5);
		}
	}

	for (int x = 0; x < WorldSize; x++) {
		for (int z = 0; z < WorldSize; z++) {
			if (BombWorld[z][x].armed && BombWorld[z][x].age < BombExplodeAge) {
				glRotatef(90, 1, 0, 0);
				glRotatef(powF(BombWorld[z][x].age * 5 / 3, 5) , 0, 0, 1);
				Bomb = gluNewQuadric();
				gluQuadricTexture(Bomb, GL_TRUE);
				glBindTexture(GL_TEXTURE_2D, BombTex->textureID);
				gluSphere(Bomb, BombWorld[z][x].age/10*(5/BombExplodeAge), 36, 72);
				glRotatef(powF(BombWorld[z][x].age * 5 / 3, 5), 0, 0, -1);
				glRotatef(90, -1, 0, 0);
			}
			if ((World[z][x] == BLOCK_WALL)) {
				glColor3f(1, 1 - LostLifeTimer / LostLifeTimerMaks, 1 - LostLifeTimer / LostLifeTimerMaks);
				DrawCubeWithText(1, WallTex->textureID);
				glColor3f(1, 1, 1);
			}
			if ((World[z][x] == BLOCK_CRATE)) {
				glColor3f(1, 1 - LostLifeTimer / LostLifeTimerMaks, 1 - LostLifeTimer / LostLifeTimerMaks);
				DrawCubeWithText(1, CrateTex->textureID);
				glColor3f(1, 1, 1);
			}
			////////////////////////////////////////////////////BOMB FIRE //////////////////////////////////////////////
			glTranslatef(0, -0.25, 0);
			if ((World[z][x] == BLOCK_XFIRE)) {
				glTranslatef(0.25, 0, 0);
				DrawCubeWithText(0.5, FireTex->textureID);
				glTranslatef(-0.5, 0, 0);
				DrawCubeWithText(0.5, FireTex->textureID);
				glTranslatef(0.25, 0, 0);
			}
			if ((World[z][x] == BLOCK_ZFIRE)) {
				glTranslatef(0, 0, 0.25);
				DrawCubeWithText(0.5, FireTex->textureID);
				glTranslatef(0, 0, -0.5);
				DrawCubeWithText(0.5, FireTex->textureID);
				glTranslatef(0, 0, 0.25);
			}
			if ((World[z][x] == BLOCK_CFIRE)) {
				glTranslatef(0, 0, 0.25);
				DrawCubeWithText(0.5, FireTex->textureID);
				glTranslatef(0, 0, -0.5);
				DrawCubeWithText(0.5, FireTex->textureID);
				glTranslatef(0, 0, 0.25);
				glTranslatef(0.25, 0, 0);
				DrawCubeWithText(0.5, FireTex->textureID);
				glTranslatef(-0.5, 0, 0);
				DrawCubeWithText(0.5, FireTex	->textureID);
				glTranslatef(0.25, 0, 0);
			}
			glTranslatef(0, 0.25, 0);
			////////////////////////////////////////////BOMB FIRE ////////////////////////////////////////////////////////////
			if (World[z][x] == BLOCK_BONUS_LIFE) {
				DrawCubeWithText(0.5, BonusLifeTex->textureID);
			}
			if (World[z][x] == BLOCK_BONUS_SPEED) {
				DrawCubeWithText(0.5, BonusSpeedTex->textureID);
			}
			if (World[z][x] == BLOCK_BONUS_POWER) {
				DrawCubeWithText(0.5, BonusPowerTex->textureID);
			}
			if (World[z][x] == BLOCK_BONUS_MOREBOMBS) {
				DrawCubeWithText(0.5, BonusBombTex->textureID);
			}
			glTranslatef(1, 0, 0);
		}
		glTranslatef(WorldSize*-1, 0, 0);
		glTranslatef(0, 0, 1);
	}
}

void DrawCross() {
	glTranslatef(0, 0, -0.01);
	glColor3f(1, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, -0.0001, 0);
	glVertex3f(0, 0.0001, 0);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.0001, 0, 0);
	glVertex3f(0.0001, 0, 0);
	glEnd();
	glColor3f(1, 1, 1);
	glTranslatef(0, 0, 0.01);
}

void Draw2DCircle(float Radius) {
	glBegin(GL_TRIANGLE_FAN);
	for (float i = 0; i < 6.28; i += 0.2) {
		glVertex2f(sinf(i) * Radius, cosf(i) * Radius);
	}
	glEnd();
}

void DrawMiniMap() {
	glTranslatef(0.00685, -0.00295, -0.01);
	glRotatef(CameraAngle.x, 0, 0, 1);
	for (int x = 0; x < WorldSize; x++) {
		for (int z = 0; z < WorldSize; z++) {
			if (!SolidBlock(World[z][x])) {
				glColor3f(0.3, 0.3, 0.3);
			} else if (World[z][x] == BLOCK_WALL) {
				glColor3f(0.15, 0.15, 0.15);
			} else if (World[z][x] == BLOCK_CRATE) {
				glColor3f(0.6, 0.3, 0.0);
			}
			glTranslatef(-0.00014 * z + BodyPosition.x * 0.00014, 0.00014 * x - BodyPosition.z * 0.00014, 0);
			glBegin(GL_TRIANGLE_FAN);
			glVertex2f(0.00007, 0.00007);
			glVertex2f(0.00007, -0.00007);
			glVertex2f(-0.00007, -0.00007);
			glVertex2f(-0.00007, 0.00007);
			glEnd();
			if (BombWorld[z][x].armed && World[z][x] == BLOCK_AIR) {
				glColor3f(0, 0, 0);
				Draw2DCircle(0.00005);
			}
			if (World[z][x] == BLOCK_BONUS_LIFE || World[z][x] == BLOCK_BONUS_MOREBOMBS || World[z][x] == BLOCK_BONUS_POWER || World[z][x] == BLOCK_BONUS_SPEED) {
				glBegin(GL_TRIANGLE_FAN);
				glColor3f(1, 0, 0);
				glVertex2f(0.000035, 0.000035);
				glColor3f(0, 1, 0);
				glVertex2f(0.000035, -0.000035);
				glColor3f(0, 0, 1);
				glVertex2f(-0.000035, -0.000035);
				glColor3f(1, 0, 1);
				glVertex2f(-0.000035, 0.000035);
				glEnd();
			}
			if (World[z][x] == BLOCK_XFIRE) {
				glBegin(GL_TRIANGLE_FAN);
				glColor3f(1, 0, 0);
				glVertex2f(0.00007, 0.000035);
				glVertex2f(0.00007, -0.000035);
				glVertex2f(-0.00007, -0.000035);
				glVertex2f(-0.00007, 0.000035);
				glEnd();
			} else if (World[z][x] == BLOCK_ZFIRE) {
				glBegin(GL_TRIANGLE_FAN);
				glColor3f(1, 0, 0);
				glVertex2f(0.000035, 0.00007);
				glVertex2f(0.000035, -0.00007);
				glVertex2f(-0.000035, -0.00007);
				glVertex2f(-0.000035, 0.00007);
				glEnd();
			} else if (World[z][x] == BLOCK_CFIRE) {
				glBegin(GL_TRIANGLE_FAN);
				glColor3f(1, 0, 0);
				glVertex2f(0.000035, 0.00007);
				glVertex2f(0.000035, -0.00007);
				glVertex2f(-0.000035, -0.00007);
				glVertex2f(-0.000035, 0.00007);
				glEnd();
				glBegin(GL_TRIANGLE_FAN);
				glVertex2f(0.00007, 0.000035);
				glVertex2f(0.00007, -0.000035);
				glVertex2f(-0.00007, -0.000035);
				glVertex2f(-0.00007, 0.000035);
				glEnd();
			}
			glTranslatef(0.00014 * z - BodyPosition.x * 0.00014, -0.00014 * x + BodyPosition.z * 0.00014, 0);
		}
	}
	glColor3f(0, 1, 0);
	glTranslatef(0.000075, -0.000075, 0);
	Draw2DCircle(0.00005);
	glTranslatef(-0.000075, 0.000075, 0);
	glColor3f(1, 1, 1);
	glRotatef(-CameraAngle.x, 0, 0, 1);
	glTranslatef(-0.00685, 0.00295, 0.01);
}

void DrawStatusBar() {
	glTranslatef(-0.0078, -0.0039, -0.01);
	for (int i = 0; i < LifesBack; i++) {
		glTranslatef(0.00045 * i, 0, 0);
		DrawSquare(0.0004, BonusLifeTex->textureID, 0.00072); 
		glTranslatef(-0.00045 * i, 0, 0);
	}
	glTranslatef(0, 0.00045, 0);
	for (int i = 0; i < MaksBombs; i++) {
		glTranslatef(0.00045 * i, 0, 0);
		DrawSquare(0.0004, BonusBombTex->textureID, 0.00072);
		glTranslatef(-0.00045 * i, 0, 0);
	}
	glTranslatef(0.0078, 0.00345, 0.01);
	glColor3f(1, 1, 1);
}

void display(void) {
	//Reset
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glLoadIdentity();
	DrawCross();
	DrawMiniMap();
	DrawStatusBar();
	if (LostLifeTimer > 0) {
		glColor4f(1, 0, 0, ((float)LostLifeTimer / LostLifeTimerMaks));
		glutSolidSphere(20, 100, 100);
		glColor3f(1, 1, 1);
	}
	

	glRotatef(CameraAngle.y, 1, 0, 0);
	glRotatef(CameraAngle.x, 0, 1, 0);
	if (FirstPersonView) {
		gluLookAt(0, 0, -1, 0, 0, 0, 0, 1, 0);
	}
	else {
		gluLookAt(0, 0, 3, 0, 0, 4, 0, 1, 0);
	}
	glTranslatef(-0.5, -BodyHeight*.95 - 0.5, -0.5);
	glTranslatef(-BodyPosition.x, -BodyPosition.y, -BodyPosition.z);

	GenerateWorld();

	//texture *Tex = texture::loadBMP("stone.bmp");
	Bomb = gluNewQuadric();
	gluQuadricTexture(Bomb, GL_TRUE);


	glBindTexture(GL_TEXTURE_2D, 0);
	glutSwapBuffers();
}

void reshape(int w, int h){
	// Prevent a divide by zero, when window is too short
	// (you can't make a window of zero width).
	if (h == 0)
		h = 1;
	ScreenHeight = h;
	ScreenWidth = w;
	float ratio = (float)w / h;
	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);
	// Reset Matrix
	glLoadIdentity();
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	// Set the correct perspective.
	gluPerspective(45, ratio, 0.01, 100);
	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
	display();
}