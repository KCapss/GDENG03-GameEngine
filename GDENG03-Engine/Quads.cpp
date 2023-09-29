#include "Quads.h"
#include "DeviceContext.h"



Quads::Quads(float xOffset, float yOffset)
{
	this->xOffset = xOffset;
	this->yOffset = yOffset;
}

void Quads::setPosAnimationOffset(float xOffset, float yOffset)
{
	this->xPosAnimation = xOffset;
	this->yPosAnimation = yOffset;
}

void Quads::onCreate(VertexBuffer* m_vb)
{
	list =
	{
		//X - Y - Z
		//X - Y - Z
		
		
		//Part 1: Simple Animation Sequences
		//{ -0.6f + xOffset, -0.8f + yOffset, 0.0f,  -0.3f + xPosAnimation, -0.1f + yPosAnimation, 0.0f, 0,0,0, 0,1,0 }, //POS4
		//{ -0.9f + xOffset, 0.1f + yOffset, 0.0f,   -0.1f + xPosAnimation, 0.75f + yPosAnimation, 0.0f, 1,1,0, 0,1,1 }, // POS1
		//{ 1.0f + xOffset, -0.3f + yOffset, 0.0f,  0.0f + xPosAnimation, -0.75f + yPosAnimation, 0.0f, 0,0,1,  1,0,0 }, //POS3
		//{- 0.20f + xOffset, -0.30f + yOffset, -0.0f, 0.8f + xPosAnimation, 0.75f + yPosAnimation, 0.0f, 1,0,0,  0,0,1 } // POS2
		

		//Part 2: Lerping Speed of the Animation
		{ -0.75f + xOffset, -0.9f + yOffset, 0.0f,  -0.25f + xPosAnimation, -0.1f + yPosAnimation, 0.0f, 0,0,0, 0,1,0 }, //POS4
		{ -0.9f + xOffset, 0.1f + yOffset, 0.0f,   -0.1f + xPosAnimation, 0.75f + yPosAnimation, 0.0f, 1,1,0, 0,1,1 }, // POS1
		{ 0.25f + xOffset, -0.25f + yOffset, 0.0f,  0.75f + xPosAnimation, -0.75f + yPosAnimation, 0.0f, 0,0,1,  1,0,0 }, //POS3
		{ 0.1f + xOffset, 0.1f + yOffset, -0.0f, 0.8f + xPosAnimation, 0.75f + yPosAnimation, 0.0f, 1,0,0,  0,0,1 } // POS2
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





