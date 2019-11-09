//
//  Texture.h
//
//  Copyright © 2018 Alun Evans. All rights reserved.
//
#pragma once
#include "includes.h"

class Texture
{
	struct TGAInfo //stores info about TGA file
	{
		GLuint width;
		GLuint height;
		GLuint bpp; //bits per pixel
		GLubyte* data; //bytes with the pixel information
	};

public:
	Texture();
	~Texture();
	Texture(std::string file); //loads a texture with filename

	GLuint texture_id; // GL id to identify the texture in opengl, every texture must have its own id
	float width;
	float height;
	std::string filename;

	bool load(std::string file); //loads a texture with filename

protected: 
	//permit any derived classes to access this function, without it being publi
	TGAInfo* loadTGA(std::string filename);
};

