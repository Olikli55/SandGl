#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>
#include <glm/vec3.hpp>
#include <vector>
//VERTEX BUFFER OBJECT
class VBO
{	
public:
	GLuint ID{}; // 0
	VBO();

	void init();
	void setBufferData(const std::vector<float>* vertices, GLsizeiptr size);
	void setBufferData(const std::vector<unsigned int>* vertices, GLsizeiptr size);
	void setBufferData(const float* vertices, GLsizeiptr size);
	void setBufferData(const unsigned int* vertices, GLsizeiptr size);
	void Bind() const;
	void Unbind() const;
	void Delete() const;
};

#endif