#include "variables.h"
#ifndef TEXTURE_H
#define TEXTURE_H

// add the content of the header file here



#pragma once

class texture
{
	unsigned int textureID;
public:
	texture(void* data, int w, int h, int format);
	static texture *loadBMP(const char* filename);
	~texture();
};

#endif 