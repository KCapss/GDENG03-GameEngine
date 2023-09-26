#pragma once

#include "GraphicsEngine.h"
#include "VertexBuffer.h"
#include "PixelShader.h"
#include "VertexShader.h"


class Quads
{
public:

	

	Quads(float xOffset, float yOffset);
	void setPosAnimationOffset(float xOffset, float yOffset);
	
	void onCreate(VertexBuffer* m_vb);
	void onUpdate(VertexBuffer* m_vb);
	void onDestroy();

	std::vector<vertex> RetrieveVertexList();
	int RetrieveVertexSize();


private:
	int numVertex = 0;
	std::vector<vertex> list;
	int vertexSize;





	float xOffset = 0;
	float yOffset = 0;

	float xPosAnimation = 0;
	float yPosAnimation = 0;

};

