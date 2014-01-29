#include "texture.h"
#include <GL\glut.h>


texture::texture(void* data, int w, int h, int format)
{
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_BGRA_EXT, w, h, 0, format, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


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
	char* headerField = new char[2];
	fread(headerField, 2, sizeof(char), fp);
	headerField[2] = 0;
	if (strcmp(headerField, "BM")) {
		//delete[] headerField;
		std::cout << "File is not a bitmap\n";
		fclose(fp);
		return NULL;
	}

	//delete[] headerField;

	unsigned int bmpDataLocation;
	unsigned int bmpWidth;
	unsigned int bmpHeight;
	unsigned short numColorPlanes;
	unsigned short bitsPerPixel;
	unsigned int compressionMethod;
	unsigned int bmpDataSize;
	
	fseek(fp, 0x000a, SEEK_SET);
	fread(&bmpDataLocation, 1, sizeof(unsigned int), fp);

	fseek(fp, 0x0012, SEEK_SET);
	fread(&bmpWidth, 1, sizeof(unsigned int), fp);
	fread(&bmpHeight, 1, sizeof(unsigned int), fp);
	fread(&numColorPlanes, 1, sizeof(unsigned short), fp);
	fread(&bitsPerPixel, 1, sizeof(unsigned short), fp);
	fread(&compressionMethod, 1, sizeof(unsigned int), fp);
	fread(&bmpDataSize, 1, sizeof(unsigned int), fp);

	if (numColorPlanes != 1 || bitsPerPixel != 24 || compressionMethod != 0) {
		std::cout << "File is not raw BMP24\n";
		fclose(fp);
		return NULL;
	}

	unsigned char* bmpData = new unsigned char[bmpDataSize];

	fseek(fp, bmpDataLocation, SEEK_SET);
	fread(bmpData, bmpDataSize, sizeof(unsigned char), fp);

	fclose(fp);
	return new texture(bmpData, bmpWidth, bmpHeight, GL_RGB);

	
}
texture::~texture()
{
}
