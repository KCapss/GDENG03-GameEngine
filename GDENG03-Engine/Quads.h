#pragma once

#include "GraphicsEngine.h"
#include "VertexBuffer.h"
#include "PixelShader.h"
#include "VertexShader.h"


class Quads
{
public:
	Quads(float xOffset, float yOffset);
	void onCreate();
	VertexBuffer* retrieveBuffer();

private:

	VertexBuffer* m_vb_copy;
	ID3D11VertexShader* m_vs = nullptr;
	ID3D11PixelShader* m_ps = nullptr;
	float xOffset = 0;
	float yOffset = 0;
};

