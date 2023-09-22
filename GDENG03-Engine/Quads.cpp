#include "Quads.h"
#include "DeviceContext.h"

Quads::Quads(float xOffset, float yOffset)
{
	this->xOffset = xOffset;
	this->yOffset = yOffset;
}

void Quads::onCreate(VertexBuffer* m_vb)
{
	vertex list[] =
	{
		//X - Y - Z
		{-0.1f + xOffset,-0.1f + yOffset,0.0f,0,0,0}, // POS1
		{-0.1f + xOffset,0.1f + yOffset, 0.0f,1,1,0}, // POS2
		{ 0.1f + xOffset,-0.1f + yOffset,0.0f,0,0,1},
		{ 0.1f + xOffset,0.1f + yOffset, 0.0f,1,1,1}
	};

	
	UINT size_list = ARRAYSIZE(list);
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();

}

void Quads::onUpdate(VertexBuffer* m_vb)
{
	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	
}

void Quads::onDestroy()
{
	m_vs->release();
	m_ps->release();
}



