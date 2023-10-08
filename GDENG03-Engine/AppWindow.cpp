#pragma once

#include <cmath>
#include "AppWindow.h"
#include "EngineTime.h"
#include "Vector3D.h"
#include "Matrix4x4.h"


//__declspec(align(16))
//
//struct constant
//{
//	Matrix4x4 m_world;
//	Matrix4x4 m_view;
//	Matrix4x4 m_proj;
//	unsigned int m_time;
//};

AppWindow::AppWindow()
{
}


AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	//Creating Windows and Background
	Window::onCreate();
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	Cube* copy = new Cube("Cube", shader_byte_code, size_shader);
	GameObjectList.push_back((AGameObject*)copy);


	GraphicsEngine::get()->releaseCompiledShader();

	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader(); 

	
	////Parameters for creeating Vertex buffer
	//m_vb = GraphicsEngine::get()->createVertexBuffer();
	//onQuadMultipleCreate();
	//onCubeCreate();


	/*
	UINT size_list = ARRAYSIZE(list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	m_vb->load(list, sizeof(Vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();


	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();*/

}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.3f, 0.4f, 1);
	RECT rc = this->getClientWindowRect();

	for (AGameObject* gameobject : GameObjectList )
	{
		gameobject->update(m_delta_time);
	}

	////SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	//RECT rc = this->getClientWindowRect();
	//GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);


	


	//TODO: Matrix
	

	//TODO: Drawing
	/*GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);*/

	
	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

	////SET THE VERTICES OF THE TRIANGLE TO DRAW
	//GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	////SET THE INDICES OF THE TRIANGLE TO DRAW
	//GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(m_ib);



	// FINALLY DRAW THE TRIANGLE

	

	//for (int i = 0; i < cubeList.size(); i++)
	//{
	//	UINT bufferSize = cubeList[0]->RetrieveIndexBufferSize();

	//	if (quadList.size() > 1)
	//		GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList((m_ib->getSizeIndexList()), i * bufferSize, i*bufferSize);

	//	//Edge Case for drawing single cases
	//	else
	//		GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList((m_ib->getSizeIndexList()), 0, 0);
	//}

	for (AGameObject* gameobject : GameObjectList)
	{
		gameobject->draw(rc.right - rc.left, rc.bottom - rc.top, m_vs, m_ps);
	}

	//GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);


	m_swap_chain->present(true);

	/*m_old_delta = m_new_delta;
	m_new_delta = ::GetTickCount();
	m_delta_time = (m_old_delta) ? ((m_new_delta - m_old_delta) / 1000.0f) : 0;*/

	m_delta_time = EngineTime::getDeltaTime(); // Engine Time Conversion
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_vb->release();
	//onQuadRelease();
	m_swap_chain->release();

	m_vs->release();
	m_ps->release();
	GraphicsEngine::get()->release();
}

//
//void AppWindow::onCubeCreate()
//{
//	cubeList.push_back(new Cube(-0.0f, 0.0f));
//	cubeList[0]->setPosAnimationOffset(0.0f, 0.0f);
//
//	std::vector<Vertex> VertixList;
//	for (unsigned int i = 0; i < cubeList.size(); i++)
//	{
//		
//		cubeList[i]->onCreate(m_vb);
//		std::vector<Vertex> copy = cubeList[i]->RetrieveVertexList();
//		for (int j = 0; j < copy.size(); j++)
//		{
//			Vertex copyV = copy[j];
//			VertixList.push_back(copyV);
//		}
//	}
//	//=== Option 1
//	Vertex* list = &VertixList[0];
//
//	std::vector<unsigned int> index_bufferList;
//	for (unsigned int i = 0; i < cubeList.size(); i++)
//	{
//
//		//Option 1 & 2
//		cubeList[i]->onCreate(m_vb);
//		std::vector<unsigned int> copy = cubeList[i]->RetrieveIndexList();
//		for (int j = 0; j < copy.size(); j++)
//		{
//			unsigned int copyIB = copy[j];
//			index_bufferList.push_back(copyIB);
//		}
//	}
//
//	unsigned int *index_list = &index_bufferList[0];
//
//	m_ib = GraphicsEngine::get()->createIndexBuffer();
//	UINT size_index_list = index_bufferList.size();
//
//	m_ib->load(index_list, size_index_list);
//
//
//	UINT size_list = VertixList.size();
//	void* shader_byte_code = nullptr;
//	size_t size_shader = 0;
//	//Vertex Shader
//	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
//
//	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
//	m_vb->load(list, sizeof(Vertex), size_list, shader_byte_code, size_shader);
//	GraphicsEngine::get()->releaseCompiledShader();
//	
//	//Pixel Shader
//	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
//	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
//	GraphicsEngine::get()->releaseCompiledShader();
//
	//constant cc;
//	cc.m_time = 0;
//
//	m_cb = GraphicsEngine::get()->createConstantBuffer();
//	m_cb->load(&cc, sizeof(constant));
//
//	//delete[] list;
//
//
//	
//}
//
//void AppWindow::onCubeUpdate()
//{
//	constant cc;
//	/*cc.m_time = ::GetTickCount();
//
//	m_delta_pos += m_delta_time / 10.0f;
//	if (m_delta_pos > 1.0f)
//		m_delta_pos = 0;*/
//
//		//Engine Time Conversion
//	cc.m_time = EngineTime::getDeltaTime();
//
//	m_delta_pos += EngineTime::getDeltaTime() / 10.0f;
//	if (m_delta_pos > 1.0f)
//		m_delta_pos = 0;
//
//
//
//	Matrix4x4 temp;
//
//	m_delta_scale += m_delta_time / 0.55f;
//
//	cc.m_world.setScale(Vector3D(1, 1, 1));
//
//	temp.setIdentity();
//	temp.setRotationZ(m_delta_scale);
//	cc.m_world *= temp;
//
//	temp.setIdentity();
//	temp.setRotationY(m_delta_scale);
//	cc.m_world *= temp;
//
//	temp.setIdentity();
//	temp.setRotationX(m_delta_scale);
//	cc.m_world *= temp;
//
//
//	cc.m_view.setIdentity();
//	cc.m_proj.setOrthoLH
//	(
//		(this->getClientWindowRect().right - this->getClientWindowRect().left) / 300.0f,
//		(this->getClientWindowRect().bottom - this->getClientWindowRect().top) / 300.0f,
//		-4.0f,
//		4.0f
//	);
//
//
//	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
//
//}
//
//void AppWindow::onCubeRelease()
//{
//}

float AppWindow::lerp(float min, float max, float f)
{
	return min * (1.0 - f) + (max * f);
}



