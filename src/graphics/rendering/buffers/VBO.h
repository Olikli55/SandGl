#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/gl.h>
//VERTEX BUFFER OBJECT
class VBO
{	
public:
	GLuint ID{}; // 0
	VBO();

	void init(const GLfloat* vertices, GLsizeiptr size);
	void Bind() const;
	void Unbind() const;
	void Delete() const;
};

#endif