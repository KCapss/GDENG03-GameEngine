#include "Quads.h"

Quads::Quads(float xOffset, float yOffset)
{
	this->xOffset = xOffset;
	this->yOffset = yOffset;
}

void Quads::onCreate()
{
	vertex list[] =
	{
		//X - Y - Z
		{-0.1f + xOffset,-0.1f + yOffset,0.0f}, // POS1
		{-0.1f + xOffset,0.1f + yOffset,0.0f}, // POS2
		{ 0.1f + xOffset,-0.1f + yOffset,0.0f},
		{ 0.1f + xOffset,0.1f + yOffset,0.0f}
	};

	m_vb_copy = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(list);

	GraphicsEngine::get()->createShaders();

	void* shader_byte_code = nullptr;
	UINT size_shader = 0;
	GraphicsEngine::get()->getShaderBufferAndSize(&shader_byte_code, &size_shader);

	m_vb_copy->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);
}

VertexBuffer* Quads::retrieveBuffer()
{
	return m_vb_copy;
}
