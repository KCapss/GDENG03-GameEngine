#pragma once

#include <cmath>
#include "AppWindow.h"
#include "EngineTime.h"
#include "Vector3D.h"
#include "Matrix4x4.h"

//Primitives
#include "Cube.h"


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
	
	

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	//Vertex Shader
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	onCubeCreate(shader_byte_code, size_shader);
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);
	
	GraphicsEngine::get()->releaseCompiledShader();

	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();


	
}

void AppWindow::onUpdate()
{
	m_delta_time = EngineTime::getDeltaTime(); // Engine Time Conversion
	Window::onUpdate();
	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.3f, 0.4f, 1);
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	for (AGameObject* gameobject : GameObjectList)
	{
		gameobject->update(m_delta_time);
	}
	
	


	for (AGameObject* gameobject : GameObjectList)
	{
		gameobject->draw(rc.right - rc.left, rc.bottom - rc.top, m_vs, m_ps);
	}

	//GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);

	/*copy->update(m_delta_time);
	copy->draw(rc.right - rc.left, rc.bottom - rc.top, m_vs, m_ps);*/

	m_swap_chain->present(true);

	/*m_old_delta = m_new_delta;
	m_new_delta = ::GetTickCount();
	m_delta_time = (m_old_delta) ? ((m_new_delta - m_old_delta) / 1000.0f) : 0;*/

	
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	//m_vb->release();
	//onQuadRelease();
	m_swap_chain->release();

	m_vs->release();
	m_ps->release();
	GraphicsEngine::get()->release();
}


void AppWindow::onCubeCreate(void* shader_byte_code, size_t size_shader)
{

	//First Copy
	Cube* FirstCube = new Cube("1", shader_byte_code, size_shader);
	FirstCube->setPosition(Vector3D(0.30f, -0.20f, 1.0f));
	FirstCube->setScale(Vector3D(0.3f, 0.3f, 0.3f));
	FirstCube->setRotation(Vector3D(0, 0, 0));
	FirstCube->setAnimSpeed(1.20f);



	Cube* Second = new Cube("2", shader_byte_code, size_shader);
	Second->setPosition(Vector3D(0, 1, 3));
	Second->setScale(Vector3D(0.6f, 0.6f, 0.6f));
	Second->setAnimSpeed(.3f);


	Cube* Third = new Cube("3", shader_byte_code, size_shader);
	Third->setPosition(Vector3D(-.2f, -.5f, 0));
	Third->setRotation(Vector3D(0, 0, 0));
	Third->setAnimSpeed(-1.20f);


	Cube* Fourth = new Cube("4", shader_byte_code, size_shader);
	Fourth->setPosition(Vector3D(0.0f, -0.60f, 2.0f));
	Fourth->setScale(Vector3D(0.3f, 0.4f, 0.5f));
	Fourth->setRotation(Vector3D(0, 0, 0));
	Fourth->setAnimSpeed(2.20f);


	Cube* Fifth = new Cube("5", shader_byte_code, size_shader);
	Fifth->setPosition(Vector3D(0.5f, 0.5f, 1.0f));
	Fifth->setScale(Vector3D(0.5f, 0.5f, 0.5f));
	Fifth->setRotation(Vector3D(0, 0, 0));
	Fifth->setAnimSpeed(0.20f);






	GameObjectList.push_back(FirstCube);
	GameObjectList.push_back(Second);
	GameObjectList.push_back(Third);
	GameObjectList.push_back(Fourth);
	GameObjectList.push_back(Fifth);

}



float AppWindow::lerp(float min, float max, float f)
{
	return min * (1.0 - f) + (max * f);
}



