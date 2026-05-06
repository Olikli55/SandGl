#include "VBO.h"


VBO::VBO() = default;

void VBO::setBufferData(const Vertex* vertices, GLsizeiptr size)
{
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}


void VBO::setBufferData(const float* vertices, GLsizeiptr size){
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::init(){
	glGenBuffers(1, &ID);

}

void VBO::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete() const
{
	glDeleteBuffers(1, &ID);
}