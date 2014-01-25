#include "texture.h"
#include <GL\glut.h>

texture::texture(void* data, int w, int h, int format)
{
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, format, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	glBindTexture(GL_TEXTURE_2D, 0);
}

texture *texture::loadBMP(const char* filename){
	FILE* fp;
	fp = fopen(filename, "r");
	if (!fp) {
		std::cout << filename << " could not be opened\n";
		fclose(fp);
		return NULL;
	}
}
texture::~texture()
{
}
