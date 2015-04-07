#pragma once
#include <GL\glew.h>

class Sprite
{
public:
	Sprite();
	~Sprite();

	void init(float x, float y, float width, float height);

	void draw();

private:
	int _x, _y, _width, _height;
	GLuint _vboID;
	

};

