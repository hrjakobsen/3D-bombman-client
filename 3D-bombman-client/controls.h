#include "variables.h"

bool FirstTime = true;
int lastX, lastY;

void MouseMotion(int x, int y) {
	if (FirstTime) {
		FirstTime = false;
		lastY = y;
		lastX = x;
	}
	else {
		FirstTime = true;
		CameraAngle.x += (x - lastX) / CameraSensitivity;
		CameraAngle.y += (y - lastY) / CameraSensitivity;
		SetCursorPos(ScreenWidth / 2, ScreenHeight / 2);
		lastY = ScreenHeight / 2;
		lastX = ScreenWidth / 2;
	}
	if (CameraAngle.y > 45) {
		CameraAngle.y = 45;
	}
	if (CameraAngle.y < -45) {
		CameraAngle.y = -45;
	}
}

void KeyBoardCallBackUp(unsigned char key, int x, int y) {
	KEYS[key] = false;
	if (key == 'W' || key == 'A' || key == 'S' || key == 'D') {
		KEYS[key + 32] = false;
	}
}

void KeyBoardCallBackDown(unsigned char key, int x, int y) {
	KEYS[key] = true;
	if (key == 'W' || key == 'A' || key == 'S' || key == 'D') {
		KEYS[key] = false;
		KEYS[key + 32] = true;
	}
}

void KeyBoardUpdate() {
	if (KEYS['w']) {
		vectorJB movement = { sinf(CameraAngle.x * DEC2RAD), 0, -1 * cosf(CameraAngle.x * DEC2RAD) };
		movement = Times(movement, MovementSpeed);
		BodyPosition = Subtract(BodyPosition, movement);
	}
	if (KEYS['s']) {
		vectorJB movement = { sinf(CameraAngle.x * DEC2RAD), 0, -1 * cosf(CameraAngle.x * DEC2RAD) };
		movement = Times(movement, MovementSpeed);
		BodyPosition = Add(BodyPosition, movement);
	}
	if (KEYS['a']) {
		vectorJB movement = { cosf(CameraAngle.x * DEC2RAD), 0, sinf(CameraAngle.x * DEC2RAD) };
		movement = Times(movement, MovementSpeed);
		BodyPosition = Add(BodyPosition, movement);
	}
	if (KEYS['d']) {
		vectorJB movement = { cosf(CameraAngle.x * DEC2RAD), 0, sinf(CameraAngle.x * DEC2RAD) };
		movement = Times(movement, MovementSpeed);
		BodyPosition = Subtract(BodyPosition, movement);
	}
	if (KEYS[27]) {
		glutDestroyWindow(glutGetWindow());
		exit(0);
	}
}
