#include "Quads.h"
#include "DeviceContext.h"



Quads::Quads(float xOffset, float yOffset)
{
	this->xOffset = xOffset;
	this->yOffset = yOffset;
}

void Quads::onCreate(VertexBuffer* m_vb)
{
	list =
	{
		//X - Y - Z
		{-0.1f + xOffset,-0.1f + yOffset,0.0f,0,0,0}, // POS1
		{-0.1f + xOffset,0.1f + yOffset, 0.0f,1,1,0}, // POS2
		{ 0.1f + xOffset,-0.1f + yOffset,0.0f,0,0,1},
		{ 0.1f + xOffset,0.1f + yOffset, 0.0f,1,1,1}
	};

	vertexSize = list.size();


}

void Quads::onUpdate(VertexBuffer* m_vb)
{
	////SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	//GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	//GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

	////SET THE VERTICES OF THE TRIANGLE TO DRAW
	//GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	//GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);

	
}

void Quads::onDestroy()
{
	/*m_vs->release();
	m_ps->release();*/
}

std::vector<vertex> Quads::RetrieveVertexList()
{
	return list;
}

int Quads::RetrieveVertexSize()
{
	return vertexSize;
}





