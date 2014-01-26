#include "controls.h"
texture *Tex = texture::loadBMP("tiles.bmp");

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

void GenerateWorld(){
	glTranslatef(1, 0, 0);
	glTranslatef(WorldSize / 2, -(WorldSize / 2), WorldSize / 2);
	glutSolidCube(WorldSize);
	glTranslatef(-(WorldSize / 2), WorldSize / 2, -(WorldSize / 2));
	glTranslatef(0, 1, 0);

	for (int x = 0; x < WorldSize; x++) {
		for (int z = 0; z < WorldSize; z++) {
			if (!(World[z][x] == BLOCK_AIR)) {
				glutWireCube(1);
			}
			glTranslatef(1, 0, 0);
		}
		glTranslatef(WorldSize*-1, 0, 0);
		glTranslatef(0, 0, 1);
	}
}

void DrawCross() {
	glTranslatef(0, 0, -0.001);
	glColor3f(1, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, -0.00001, 0);
	glVertex3f(0, 0.00001, 0);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.00001, 0, 0);
	glVertex3f(0.00001, 0, 0);
	glEnd();
	glColor3f(1, 1, 1);
	glTranslatef(0, 0, 0.001);
}

void display(void) {
	//Reset
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	DrawCross();
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

	glBindTexture(GL_TEXTURE_2D, Tex->textureID);

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);

	glTexCoord2f(10, 10);
	glVertex3f(10, 0, 10);

	glTexCoord2f(-10, 10);
	glVertex3f(-10, 0, 10);

	glTexCoord2f(-10, -10);
	glVertex3f(-10, 0, -10);

	glTexCoord2f(10, -10);
	glVertex3f(10, 0, -10);

	glEnd();

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
	gluPerspective(45, ratio, 0.000001, 50);
	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
	display();
}