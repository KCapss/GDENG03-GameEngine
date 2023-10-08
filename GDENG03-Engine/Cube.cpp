#include "Cube.h"

#include <list>

#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "DeviceContext.h"

Cube::Cube(string name, void* shaderByteCode, size_t sizeShader): AGameObject(name)
{
	Vertex cubeList[] =
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

	//void* shader_byte_code = nullptr;
	//size_t size_shader = 0;
	//Vertex Shader
	//GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	//m_vs = GraphicsEngine::get()->createVertexShader(shaderByteCode, sizeShader);
	vertexBuffer->load(cubeList, sizeof(Vertex), size_list, shaderByteCode, sizeShader);
	GraphicsEngine::get()->releaseCompiledShader();
	
	//Pixel Shader
	//GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	//m_ps = GraphicsEngine::get()->createPixelShader(shaderByteCode, sizeShader);
	GraphicsEngine::get()->releaseCompiledShader();

	cc.m_time = 0;

	constantBuffer = GraphicsEngine::get()->createConstantBuffer();
	constantBuffer->load(&cc, sizeof(constant));
}

void Cube::update(float deltaTime)
{
	/*cc.m_time = ::GetTickCount();

		m_delta_pos += m_delta_time / 10.0f;
		if (m_delta_pos > 1.0f)
			m_delta_pos = 0;*/

			//Engine Time Conversion
	cc.m_time = EngineTime::getDeltaTime();

	/*m_delta_pos += EngineTime::getDeltaTime() / 10.0f;
	if (m_delta_pos > 1.0f)
		m_delta_pos = 0;*/

	Matrix4x4 temp;

	ticks += EngineTime::getDeltaTime() / 0.55f;

	cc.m_world.setScale(this->getLocalScale());

	temp.setIdentity();
	temp.setRotationZ(ticks);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationY(ticks);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationX(ticks);
	cc.m_world *= temp;


	cc.m_view.setIdentity();
	
}

void Cube::draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader)
{
	cc.m_proj.setOrthoLH
	(
		(width) / 300.0f,
		(height) / 300.0f,
		-4.0f,
		4.0f
	);

	constantBuffer->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);

	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(vertexShader, constantBuffer);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(pixelShader, constantBuffer);

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(vertexBuffer);

	//SET THE INDICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(indexBuffer);

	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(indexBuffer->getSizeIndexList(), 0, 0);

}

void Cube::setAnimSpeed(float speed)
{
}
