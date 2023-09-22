#pragma once

#include <iostream>
#include <FreeImage.h>
#include "glsl.h"
#include "glm.h"

class Mesh
{
private:
	GLMmodel* mesh = NULL;
	GLuint textId = -1;

public:
	Mesh();
	Mesh(char* meshPath);
	Mesh(char* meshPath, char* textPath);
	
	void draw();
};

