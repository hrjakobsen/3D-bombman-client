#define BLOCK_AIR 0
#define BLOCK_BLOCK 1
#define BLOCK_BOX 2

#include <GL\glut.h>
#include <Windows.h>
#include "vectors.h"
#include "math.h"
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <string.h>
#include <deque>
#include <iostream>
#include <thread>
#include <time.h>
#include <chrono>


//GAME SETUP
float FramesPerSecond = 20;
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
int WorldSize = 15;
short World[100][100] = { 
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
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

//Propeties
float MovementSpeed = 0.04; // 

//CAMERA
vectorJB CameraAngle = { 0, 0, 0 };
float CameraSensitivity = 40;

//CONTROLS
bool KEYS[256];

