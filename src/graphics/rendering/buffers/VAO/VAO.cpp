#include "VAO/VAO.h"


VAO::VAO()=default;

void VAO::init(){
	glGenVertexArrays(1, &ID);}

void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type,  GLsizeiptr stride, const void* offset)
{
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);


}

void VAO::Bind() const
{
	glBindVertexArray(ID);
}

void VAO::Unbind() const
{
	glBindVertexArray(0);
}

void VAO::Delete() const
{
	glDeleteVertexArrays(1, &ID);
}
