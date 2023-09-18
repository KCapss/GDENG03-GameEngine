#pragma once

#include "GraphicsEngine.h"
#include "VertexBuffer.h"


struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
};



class Triangle
{
public:
	Triangle(float offset);
	void onCreate();
	VertexBuffer *retrieveBuffer();

private:

	VertexBuffer* m_vb_copy;
	vertex list[];

	float offset = 0;
	
};

