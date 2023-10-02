#include "Cube.h"

Cube::Cube(float xOffset, float yOffset)
{
	this->xOffset = xOffset;
	this->yOffset = yOffset;
}

Cube::~Cube()
{
}

void Cube::setPosAnimationOffset(float xOffset, float yOffset)
{
	this->xPosAnimation = xOffset;
	this->yPosAnimation = yOffset;
}

void Cube::onCreate(VertexBuffer* m_vb)
{

	list =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,0,0),  Vector3D(0.2f,0,0) },
		{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,1,0), Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,0),  Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,0,0), Vector3D(0.2f,0,0) },

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.5f),    Vector3D(0,1,0), Vector3D(0,0.2f,0) },
		{ Vector3D(0.5f,0.5f,0.5f),    Vector3D(0,1,1), Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.5f,0.5f,0.5f),   Vector3D(0,1,1),  Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(0,1,0), Vector3D(0,0.2f,0) }
	};

	index_list =

	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};

	bufferSize = index_list.size();
}

void Cube::onUpdate(VertexBuffer* m_vb)
{

}

void Cube::onDestroy()
{
}

std::vector<vertex> Cube::RetrieveVertexList()
{
	return list;
}

std::vector<unsigned> Cube::RetrieveIndexList()
{
	return index_list;
}

int Cube::RetrieveVertexSize()
{
	return vertexSize;
}

int Cube::RetrieveIndexBufferSize()
{
	return bufferSize;
}
