#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/gl.h>

class EBO
{
public:
	GLuint ID{}; // automatically initialized to zero

	EBO();

	void init(const GLuint* indices, GLsizeiptr size);
	void Bind() const;
	void Unbind() const;
	void Delete() const;
};

#endif