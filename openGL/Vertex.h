#pragma once

#include <GL\glew.h>

struct Color {
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

struct Position {
	float x;
	float y;
};

struct Vertex {
	Position position;

	Color color;
	//struct should be multiple of 4 for speed reasons
};