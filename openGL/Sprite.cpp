#include "Sprite.h"


Sprite::Sprite()
{
	_vboID = 0;
}


Sprite::~Sprite()
{
	//Free buffer on GPU
	if (_vboID != 0) {
		glDeleteBuffers(1, &_vboID);
	}
}


void Sprite::init(float x, float y, float width, float height) {
	_x = x;
	_y = y;
	_width = width;
	_height = height;

	if (_vboID == 0) {
		glGenBuffers(1, &_vboID);
	}

	//12 points to make a square (2 triangles)
	float vertexData[12];

	//First triangle
	//Top Right
	vertexData[0] = x + width;
	vertexData[1] = y + height;
	//Top Left
	vertexData[2] = x;
	vertexData[3] = y + height;
	//Bottom Left
	vertexData[4] = x;
	vertexData[5] = y;

	//Second triangle
	//Bottom Left
	vertexData[6] = x;
	vertexData[7] = y;
	//Bottom Right
	vertexData[8] = x + width;
	vertexData[9] = y;
	//Top Right
	vertexData[10] = x + width;
	vertexData[11] = y + height;

	//Upload data to GPU memory space
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	//Close buffer connection
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}


void Sprite::draw() {
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	glEnableVertexAttribArray(0);
	//Specify the data to draw: (index of buffer, number of values(x and y), 
	//data representation, norm???, stride???, innerleaved)
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	//GPU always works in triangles, thus using GL_Quads may not be supported on some systems.
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

