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
#include "bomb.h"

texture *Tex;
texture *BombTex;
texture *FireTex;
GLUquadric *Bomb;

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
BombJB BombWorld[WorldSize][WorldSize];
int BombFireWorld[WorldSize][WorldSize];

//WINDOW
int ScreenWidth;
int ScreenHeight;

//BODY
vectorJB BodyPosition = { 1.5, 0, 1.5 }; // Center of feet
float BodyHeight = 0.75; //Camera is at 95% of height
float BodyWidth = .75; //Shoulderwidth
float BodyRadius = 0.2; // For colision detection if set to 0.2 a minimum of 0.4 space is required to pass through

//Propeties
float MovementSpeed = 2.5; // m/s
int PlayerPower = 2;

//CAMERA
vectorJB CameraAngle = { 0, 0, 0 };
float CameraSensitivity = 40;

//CONTROLS
bool KEYS[256];








void UpdateBombs(float Diff) {
	int BombID = 0;
	for (int i = 0; i < WorldSize; i++) {
		for (int ii = 0; ii < WorldSize; ii++) {
			BombID ++;
			if (BombWorld[i][ii].armed) {
				BombWorld[i][ii].age += Diff;
				if (BombWorld[i][ii].age > 5 && !BombWorld[1][ii].FireDrawen) {
					BombWorld[1][ii].FireDrawen = true;
					World[i][ii] = BLOCK_CFIRE;
					BombFireWorld[i][ii] = BombID;
					for (int f = 1; f <= BombWorld[i][ii].power; f++) {
						int Ni = i + f;
						int Nii = ii;
						if (Ni < 0 || Nii < 0 || Ni >= WorldSize || Nii >= WorldSize || World[Ni][Nii] != BLOCK_AIR) {
							break;
						}
						World[Ni][Nii] = BLOCK_XFIRE;
						BombFireWorld[Ni][Nii] = BombID;
					}
					for (int f = 1; f <= BombWorld[i][ii].power; f++) {
						int Ni = i - f;
						int Nii = ii;
						if (Ni < 0 || Nii < 0 || Ni >= WorldSize || Nii >= WorldSize || World[Ni][Nii] != BLOCK_AIR) {
							break;
						}
						World[Ni][Nii] = BLOCK_XFIRE;
						BombFireWorld[Ni][Nii] = BombID;
					}
					for (int f = 1; f <= BombWorld[i][ii].power; f++) {
						int Ni = i;
						int Nii = ii + f;
						if (Ni < 0 || Nii < 0 || Ni >= WorldSize || Nii >= WorldSize || World[Ni][Nii] != BLOCK_AIR) {
							break;
						}
						World[Ni][Nii] = BLOCK_ZFIRE;
						BombFireWorld[Ni][Nii] = BombID;
					}
					for (int f = 1; f <= BombWorld[i][ii].power; f++) {
						int Ni = i;
						int Nii = ii - f;
						if (Ni < 0 || Nii < 0 || Ni >= WorldSize || Nii >= WorldSize || World[Ni][Nii] != BLOCK_AIR) {
							break;
						}
						World[Ni][Nii] = BLOCK_ZFIRE;
						BombFireWorld[Ni][Nii] = BombID;
					}
				} else if (BombWorld[i][ii].age > 10) {
					BombWorld[i][ii].armed = false;
					BombWorld[i][ii].age = 0;
					BombWorld[i][ii].FireDrawen = false;
					for (int i = 0; i < WorldSize; i++) {
						for (int ii = 0; ii < WorldSize; ii++) {
							if (BombFireWorld[i][ii] == BombID) {
								World[i][ii] = BLOCK_AIR;
								BombFireWorld[i][ii] = 0;
							}
						}
					}
				}
			}
		}
	}
}
