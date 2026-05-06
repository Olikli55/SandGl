
#include "EBO.h"

EBO::EBO()= default;

void EBO::setBufferData(const GLuint* indices, GLsizeiptr size)
{
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}
void EBO::init(){
	glGenBuffers(1, &ID);
}

void EBO::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Deletes the EBO
void EBO::Delete() const
{
	glDeleteBuffers(1, &ID);
}
