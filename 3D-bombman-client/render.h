#include "controls.h"

void display(void) {
	//Reset
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	glutSwapBuffers();
}

void reshape(int w, int h){
	// Prevent a divide by zero, when window is too short
	// (you can't make a window of zero width).
	if (h == 0)
		h = 1;
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