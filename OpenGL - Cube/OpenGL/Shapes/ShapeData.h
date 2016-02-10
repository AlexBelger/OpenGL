#pragma once
#include <glm\vec3.hpp>
#include <GL\glew.h>

class CVertex
{
public:
	glm::vec3 position;
	glm::vec3 color;
};

class CShapeData
{
public:
	CShapeData() :vertices(nullptr), numVertices(0), indices(nullptr), numIndices(0) {}
	CVertex* vertices;
	GLuint numVertices;
	GLushort* indices;
	GLuint numIndices;

	GLsizeiptr getVertexBufferSize() const
	{
		return numVertices * sizeof(CVertex);
	}

	GLsizeiptr getIndexBufferSize() const
	{
		return numIndices * sizeof(GLushort);
	}

	void cleanup()
	{
		delete[] vertices;
		delete[] indices;
		numVertices = numIndices = 0;
	}
};