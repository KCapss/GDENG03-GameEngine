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

	//Window::onCreate();
	//GraphicsEngine::get()->init();

	//InputSystem::initialize();
	//InputSystem::getInstance()->addListener(this);
	//InputSystem::getInstance()->showCursor(true);
	//m_swap_chain = GraphicsEngine::get()->createSwapChain();

	//RECT rc = this->getClientWindowRect();
	//m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	//m_world_cam.setTranslation(Vector3D(0, 0, -2));

	//Vertex vertex_list[] =
	//{
	//	//X - Y - Z
	//	//FRONT FACE
	//	{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,0,0),  Vector3D(0.2f,0,0) },
	//	{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,1,0), Vector3D(0.2f,0.2f,0) },
	//	{ Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,0),  Vector3D(0.2f,0.2f,0) },
	//	{ Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,0,0), Vector3D(0.2f,0,0) },

	//	//BACK FACE
	//	{ Vector3D(0.5f,-0.5f,0.5f),    Vector3D(0,1,0), Vector3D(0,0.2f,0) },
	//	{ Vector3D(0.5f,0.5f,0.5f),    Vector3D(0,1,1), Vector3D(0,0.2f,0.2f) },
	//	{ Vector3D(-0.5f,0.5f,0.5f),   Vector3D(0,1,1),  Vector3D(0,0.2f,0.2f) },
	//	{ Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(0,1,0), Vector3D(0,0.2f,0) }

	//};

	//m_vb = GraphicsEngine::get()->createVertexBuffer();
	//UINT size_list = ARRAYSIZE(vertex_list);


	//unsigned int index_list[] =
	//{
	//	//FRONT SIDE
	//	0,1,2,  //FIRST TRIANGLE
	//	2,3,0,  //SECOND TRIANGLE
	//	//BACK SIDE
	//	4,5,6,
	//	6,7,4,
	//	//TOP SIDE
	//	1,6,5,
	//	5,2,1,
	//	//BOTTOM SIDE
	//	7,0,3,
	//	3,4,7,
	//	//RIGHT SIDE
	//	3,2,5,
	//	5,4,3,
	//	//LEFT SIDE
	//	7,6,1,
	//	1,0,7
	//};


	//m_ib = GraphicsEngine::get()->createIndexBuffer();
	//UINT size_index_list = ARRAYSIZE(index_list);

	//m_ib->load(index_list, size_index_list);


	//void* shader_byte_code = nullptr;
	//size_t size_shader = 0;
	//GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	//m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	//m_vb->load(vertex_list, sizeof(Vertex), size_list, shader_byte_code, size_shader);

	//GraphicsEngine::get()->releaseCompiledShader();


	//GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	//m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	//GraphicsEngine::get()->releaseCompiledShader();

	//constant cc;
	//cc.m_time = 0;

	//m_cb = GraphicsEngine::get()->createConstantBuffer();
	//m_cb->load(&cc, sizeof(constant));


	
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


	//Window::onUpdate();

	//InputSystem::getInstance()->update();

	////CLEAR THE RENDER TARGET 
	//GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
	//	0, 0.3f, 0.4f, 1);

	////SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	//RECT rc = this->getClientWindowRect();
	//GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);


	//update();

	//GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	//GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	////SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	//GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	//GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);


	////SET THE VERTICES OF THE TRIANGLE TO DRAW
	//GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	////SET THE INDICES OF THE TRIANGLE TO DRAW
	//GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(m_ib);


	//// FINALLY DRAW THE TRIANGLE
	//GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
	//m_swap_chain->present(true);


	//m_old_delta = m_new_delta;
	//m_new_delta = ::GetTickCount();

	//m_delta_time = (m_old_delta) ? ((m_new_delta - m_old_delta) / 1000.0f) : 0;
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



