#pragma once

#include "GraphicsEngine.h"
#include "VertexBuffer.h"

class Quads
{
public:
	Quads(float xOffset, float yOffset);
	void onCreate();
	VertexBuffer* retrieveBuffer();

private:

	VertexBuffer* m_vb_copy;
	float xOffset = 0;
	float yOffset = 0;
};

