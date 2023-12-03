#include "Cube.h"

#include <list>

#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "DeviceContext.h"
#include "SceneCameraHandler.h"
#include "ShaderLibrary.h"

Cube::Cube(string name): AGameObject(name)
{
	typeName = "Cube";
	

	ShaderNames shaderNames;
	void* shaderByteCode = NULL;
	size_t sizeShader = 0;
	ShaderLibrary::getInstance()->requestVertexShaderData(shaderNames.BASE_VERTEX_SHADER_NAME, &shaderByteCode, &sizeShader);


	//TODO: Rainbow Version of the Shaders
	Vertex cubeList[] =
	{
		//X - Y - Z
		{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,0,0),  Vector3D(0.2f,0,0) },
		{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,1,0), Vector3D(0.2f,0.2f,0) },
		{Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,0),  Vector3D(0.2f,0.2f,0) },
		{Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,0,0), Vector3D(0.2f,0,0) },

		//BACK FACE
		{Vector3D(0.5f,-0.5f,0.5f),    Vector3D(0,1,0), Vector3D(0,0.2f,0) },
		{Vector3D(0.5f,0.5f,0.5f),    Vector3D(0,1,1), Vector3D(0,0.2f,0.2f) },
		{Vector3D(-0.5f,0.5f,0.5f),   Vector3D(0,1,1),  Vector3D(0,0.2f,0.2f) },
		{Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(0,1,0), Vector3D(0,0.2f,0) }
	};


	//TODO: Custom Version of the Shaders Blue to Red
	//Vertex cubeList[] =
	//{
	//	//X - Y - Z
	//	//FRONT FACE
	//	{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(0,0,1),  Vector3D(1,0,0)},
	//	{Vector3D(-0.5f,0.5f,-0.5f),     Vector3D(0,0,1),  Vector3D(1,0,0) },
	//	{ Vector3D(0.5f,0.5f,-0.5f),    Vector3D(0,0,1),  Vector3D(1,0,0) },
	//	{ Vector3D(0.5f,-0.5f,-0.5f),    Vector3D(0,0,1),  Vector3D(1,0,0) },

	//	//BACK FACE
	//	{ Vector3D(0.5f,-0.5f,0.5f),    Vector3D(0,0,1),  Vector3D(1,0,0) },
	//	{ Vector3D(0.5f,0.5f,0.5f),    Vector3D(0,0,1),  Vector3D(1,0,0) },
	//	{ Vector3D(-0.5f,0.5f,0.5f),   Vector3D(0,0,1),  Vector3D(1,0,0) },
	//	{ Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(0,0,1),  Vector3D(1,0,0) }
	//};

	unsigned int index_list[] =
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

	vertexBuffer = GraphicsEngine::get()->createVertexBuffer();
	indexBuffer = GraphicsEngine::get()->createIndexBuffer();


	size_index_list = ARRAYSIZE(index_list);
	indexBuffer->load(index_list, size_index_list);

	size_list = ARRAYSIZE(cubeList);

	vertexBuffer->load(cubeList, sizeof(Vertex), size_list, shaderByteCode, sizeShader);


	
	cc.m_time = 0;

	constantBuffer = GraphicsEngine::get()->createConstantBuffer();
	constantBuffer->load(&cc, sizeof(constant));
}

Cube::~Cube()
{
}

void Cube::update(float deltaTime)
{
	this->deltaTime = deltaTime;

}

void Cube::draw(int width, int height)
{
	ShaderNames shaderNames;

	if(this->overrideMatrix)
	{
		cc.m_world = localMatrix;
	}

	else
	{
		this->updateLocalMatrix();
		cc.m_world = localMatrix;
	}

	cc.m_view = SceneCameraHandler::getInstance()->getSceneCameraViewMatrix();
	cc.m_proj.setPerspectiveFovLH(1.57f, ((float)height / (float)width), 0.1f, 100.0f);
	/*cc.m_proj.setOrthoLH
	(
		(width) / 300.0f,
		(height) / 300.0f,
		-4.0f,
		4.0f
	);*/

	constantBuffer->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
	GraphicsEngine::get()->getImmediateDeviceContext()->setRenderConfig(ShaderLibrary::getInstance()->getVertexShader(shaderNames.BASE_VERTEX_SHADER_NAME), ShaderLibrary::getInstance()->getPixelShader(shaderNames.BASE_PIXEL_SHADER_NAME));
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(constantBuffer); // Does both vertex + pixel



	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(vertexBuffer);

	//SET THE INDICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(indexBuffer);

	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(indexBuffer->getSizeIndexList(), 0, 0);

}

void Cube::setAnimSpeed(float speed)
{
	this->speed = speed;
}

void Cube::IncrementRot(float offsetIncrease)
{
	this->m_rot_x += offsetIncrease;
	this->m_rot_y += offsetIncrease;
	this->m_rot_z += offsetIncrease;
}
