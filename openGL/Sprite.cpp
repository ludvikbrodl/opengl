#include "Sprite.h"
#include "Vertex.h"

#include <cstddef>

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
	Vertex vertexData[6];

	//First triangle
	//Top Right
	vertexData[0].position.x = x + width;
	vertexData[0].position.y = y + height;
	//Top Left
	vertexData[1].position.x = x;
	vertexData[1].position.y = y + height;
	//Bottom Left
	vertexData[2].position.x = x;
	vertexData[2].position.y = y;

	//Second triangle
	//Bottom Left
	vertexData[3].position.x = x;
	vertexData[3].position.y = y;
	//Bottom Right
	vertexData[4].position.x = x + width;
	vertexData[4].position.y = y;
	//Top Right
	vertexData[5].position.x = x + width;
	vertexData[5].position.y = y + height;

	for (int i = 0; i < 6; i++) {
		vertexData[i].color.r = 255;
		vertexData[i].color.g = 0;
		vertexData[i].color.b = 255;
		vertexData[i].color.a = 255;
	}

	vertexData[1].color.r = 0;
	vertexData[1].color.g = 0;
	vertexData[1].color.b = 255;
	vertexData[1].color.a = 255;

	vertexData[4].color.r = 150;
	vertexData[4].color.g = 150;
	vertexData[4].color.b = 0;
	vertexData[4].color.a = 150;

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
	//position attribute pointer
	//last paramenter - offset of the positions inside the struct
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	//color attribute pointer
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	
	//GPU always works in triangles, thus using GL_Quads may not be supported on some systems.
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

