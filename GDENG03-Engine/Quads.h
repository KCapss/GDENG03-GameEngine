#pragma once

#include "GraphicsEngine.h"
#include "VertexBuffer.h"
#include "PixelShader.h"
#include "VertexShader.h"


class Quads
{
public:
	Quads(float xOffset, float yOffset);
	void onCreate(VertexBuffer* m_vb);
	void onUpdate(VertexBuffer* m_vb);
	void onDestroy();



private:

	float xOffset = 0;
	float yOffset = 0;

	VertexShader* m_vs;
	PixelShader* m_ps;
};

