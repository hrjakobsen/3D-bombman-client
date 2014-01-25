#include "variables.h"
#pragma once

class texture
{
	unsigned int textureID;
public:
	texture(void* data, int w, int h, int format);
	static texture *loadBMP(const char* filename);
	~texture();
};

