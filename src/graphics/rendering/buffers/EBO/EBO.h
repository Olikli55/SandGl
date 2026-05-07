#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>

class EBO
{
public:
	GLuint ID{}; // automatically initialized to zero

	EBO();

	void setBufferData(const GLuint* indices, GLsizeiptr size);
	void init();
	void Bind() const;
	void Unbind() const;
	void Delete() const;
};

#endif