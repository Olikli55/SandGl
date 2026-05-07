#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include "vertex.h"
#include<glad/glad.h>
//VERTEX BUFFER OBJECT
class VBO
{	
public:
	GLuint ID{}; // 0
	VBO();

	void init();
	void setBufferData(const Vertex* vertices, GLsizeiptr size);
	void setBufferData(const float* vertices, GLsizeiptr size);
	void Bind() const;
	void Unbind() const;
	void Delete() const;
};

#endif