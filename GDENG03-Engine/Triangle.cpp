#include "Triangle.h"


Triangle::Triangle(float offset)
{
	this->offset = offset;
}


void Triangle::onCreate()
{
	
	vertex list[] =
	{
		//X - Y - Z
		{-0.1f * offset,-0.1f * offset,0.0f}, // POS1
		{-0.1f * offset,0.1f * offset,0.0f}, // POS2
		{ 0.1f * offset,-0.1f * offset,0.0f}
	};

	m_vb_copy = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(list);

	GraphicsEngine::get()->createShaders();

	void* shader_byte_code = nullptr;
	UINT size_shader = 0;
	GraphicsEngine::get()->getShaderBufferAndSize(&shader_byte_code, &size_shader);

	m_vb_copy->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);
}

VertexBuffer *Triangle::retrieveBuffer()
{
	return m_vb_copy;
}

