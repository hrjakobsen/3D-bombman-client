#include <GL\glut.h>
#include <iostream>
#include <Windows.h>
#include "vectors.h"

#include "math.h"
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <string.h>
#include <deque>

#include <thread>
#include <time.h>
#include <chrono>
#include "blocks.h"
#include "texture.h"


//GAME SETUP
float FramesPerSecond = 60;
//VARS

float DEC2RAD = 3.14 / 180;

short GameState = 1;
/*
1 = Playing
2 = Paused
*/
bool FirstPersonView = true;

//WORLD
int WorldWidth = 100;
int WorldHeight = 3;
int WorldDepth = 100;
const int WorldSize = 15;
short World[WorldSize][WorldSize] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	};

//WINDOW
int ScreenWidth;
int ScreenHeight;

//BODY
vectorJB BodyPosition = { 1.5, 0, 1.5 }; // Center of feet
float BodyHeight = 0.75; //Camera is at 95% of height
float BodyWidth = .75; //Shoulderwidth
float BodyRadius = 0.2; // For colision detection if set to 0.2 a minimum of 0.4 space is required to pass through

//Propeties
float MovementSpeed = 1; // m/s

//CAMERA
vectorJB CameraAngle = { 0, 0, 0 };
float CameraSensitivity = 40;

//CONTROLS
bool KEYS[256];

