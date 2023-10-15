#pragma once

#include <cmath>
#include "AppWindow.h"
#include "EngineTime.h"
#include "Vector3D.h"
#include "Matrix4x4.h"

//Primitives
#include "Cube.h"
#include "InputSystem.h"
#include "SceneCameraHandler.h"

//Helper
#include "MathUtils.h"


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
	
	InputSystem::initialize();
	InputSystem::getInstance()->addListener(this);
	InputSystem::getInstance()->showCursor(true);

	
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();
	
	RECT rc = this->getClientWindowRect();

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	//Vertex Shader
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	//TODO: Draw create here
	onCubeCreate(shader_byte_code, size_shader);
	//TODO: STOP DRAWING

	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);
	
	GraphicsEngine::get()->releaseCompiledShader();

	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();



	SceneCameraHandler::initialize();
}

void AppWindow::onUpdate()
{
	m_delta_time = EngineTime::getDeltaTime(); // Engine Time Conversion
	Window::onUpdate();
	InputSystem::getInstance()->update();


	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.3f, 0.4f, 1);

	//VIEWPORT
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	SceneCameraHandler::getInstance()->update();

	//Other Primitive
	for (AGameObject* gameobject : GameObjectList)
	{
		gameobject->update(m_delta_time);
	}

	for (AGameObject* gameobject : GameObjectList)
	{
		gameobject->draw(rc.right - rc.left, rc.bottom - rc.top, m_vs, m_ps);
	}

	m_swap_chain->present(true);

}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_vb->release();
	m_ib->release(); 
	m_cb->release();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();
	GraphicsEngine::get()->release();
}



void AppWindow::onKeyDown(int key)
{
	//Sir Neil Template
	/*cout << "onkeydown:\n";
	if (InputSystem::getInstance()->isKeyDown('W'))
	{
		cout << "W pressed\n";
	}*/

	if (key == 'W')
	{
		//m_rot_x += 3.14f*m_delta_time;
		m_forward = 1.0f;
	}
	else if (key == 'S')
	{
		//m_rot_x -= 3.14f*m_delta_time;
		m_forward = -1.0f;
	}
	else if (key == 'A')
	{
		//m_rot_y += 3.14f*m_delta_time;
		m_rightward = -1.0f;
	}
	else if (key == 'D')
	{
		//m_rot_y -= 3.14f*m_delta_time;
		m_rightward = 1.0f;
	}


}

void AppWindow::onKeyUp(int key)
{
	/*cout << "onkeyup:\n";
	if (InputSystem::getInstance()->isKeyUp('W'))
	{
		cout << "W released\n";
	}*/

	m_forward = 0.0f;
	m_rightward = 0.0f;
}

void AppWindow::onMouseMove(const Point deltaPos)
{
	//Sir Neil Template
	/*cout << " mouse moved: " << deltaPos.getX() << ", " << deltaPos.getY() << "\n";*/

	int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);

	//Final
	if (isRightClick) {
		m_rot_x += (deltaPos.getY()) * m_delta_time * 0.3f;
		m_rot_y += (deltaPos.getX()) * m_delta_time * 0.3f;

		//Template
		/*m_rot_x += (deltaPos.getX() - (height / 2.0f)) * m_delta_time * 0.001f;
		m_rot_y += (deltaPos.getY() - (width / 2.0f)) * m_delta_time * 0.001f;*/

	}

	
}

void AppWindow::onLeftMouseDown(const Point deltaPos)
{
	m_scale_cube = 0.5f;
}

void AppWindow::onLeftMouseUp(const Point deltaPos)
{
	m_scale_cube = 1.0f;
}

void AppWindow::onRightMouseDown(const Point deltaPos)
{
	m_scale_cube = 2.0f;
	isRightClick = true;
}

void AppWindow::onRightMouseUp(const Point deltaPos)
{
	m_scale_cube = 1.0f;
	isRightClick = false;
}

void AppWindow::update()
{
	constant cc;
	cc.m_time = ::GetTickCount();

	m_delta_pos += m_delta_time / 10.0f;
	if (m_delta_pos > 1.0f)
		m_delta_pos = 0;


	Matrix4x4 temp;

	m_delta_scale += m_delta_time / 0.55f;

	

	cc.m_world.setIdentity();

	Matrix4x4 world_cam;
	world_cam.setIdentity();

	temp.setIdentity();
	temp.setRotationX(m_rot_x);
	world_cam *= temp;

	temp.setIdentity();
	temp.setRotationY(m_rot_y);
	world_cam *= temp;


	Vector3D new_pos = m_world_cam.getTranslation() + world_cam.getZDirection() * (m_forward * 0.1f);

	new_pos = new_pos + world_cam.getXDirection() * (m_rightward * 0.1f);

	world_cam.setTranslation(new_pos);

	m_world_cam = world_cam;


	world_cam.inverse();




	cc.m_view = world_cam;
	/*cc.m_proj.setOrthoLH
	(
		(this->getClientWindowRect().right - this->getClientWindowRect().left)/300.0f,
		(this->getClientWindowRect().bottom - this->getClientWindowRect().top)/300.0f,
		-4.0f,
		4.0f
	);*/

	int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);


	cc.m_proj.setPerspectiveFovLH(1.57f, ((float)width / (float)height), 0.1f, 100.0f);


	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
}


void AppWindow::onCubeCreate(void* shader_byte_code, size_t size_shader)
{

	for (int i = 0; i < 20; i++)
	{
		Cube* Copy = new Cube("1", shader_byte_code, size_shader);
		Copy->setPosition(Vector3D(MathUtils::randomFloat(-1, 1), 
			MathUtils::randomFloat(-1, 1),
			MathUtils::randomFloat(-3, 3)));
		Copy->setScale(Vector3D(0.5f, 0.5f, 0.5f));
		Copy->setRotation(Vector3D(MathUtils::randomFloat(-180, 180),
			MathUtils::randomFloat(-180, 180),
			MathUtils::randomFloat(-180, 180)));

		GameObjectList.push_back(Copy);
	}

}



float AppWindow::lerp(float min, float max, float f)
{
	return min * (1.0 - f) + (max * f);
}



