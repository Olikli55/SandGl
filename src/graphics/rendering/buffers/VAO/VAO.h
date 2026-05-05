#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/gl.h>
#include "VBO/VBO.h"


//VERTEX  ARRAY OBJECT
class VAO
{
public:
	GLuint ID{};

	VAO();
	void init();

	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, const void* offset);
	void Bind() const;
	void Unbind() const;
	void Delete() const;
};

#endif