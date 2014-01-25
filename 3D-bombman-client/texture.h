#include <iostream>
#ifndef __3D_bombman_client_texture__
#define __3D_bombman_client_texture__

#pragma once

class texture
{
	unsigned int textureID;
public:
	texture(void* data, int w, int h, int format);
	static texture *loadBMP(const char* filename);
	~texture();
};

#endif /* defined(__3D-bombman-client_texture) */__