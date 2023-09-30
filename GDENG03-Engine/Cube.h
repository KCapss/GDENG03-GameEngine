#pragma once
#include "GraphicsEngine.h"

class Cube
{
public:
	Cube(float xOffset, float yOffset);
	void setPosAnimationOffset(float xOffset, float yOffset);

	void onCreate(VertexBuffer* m_vb);
	void onUpdate(VertexBuffer* m_vb);
	void onDestroy();

	std::vector<vertex> RetrieveVertexList();
	std::vector<unsigned int> RetrieveIndexList();
	int RetrieveVertexSize();
	int RetrieveIndexBufferSize();


private:
	int numVertex = 0;
	int bufferSize = 0;
	std::vector<vertex> list;
	std::vector<unsigned int> index_list;
	int vertexSize;

	float xOffset = 0;
	float yOffset = 0;

	float xPosAnimation = 0;
	float yPosAnimation = 0;
};

