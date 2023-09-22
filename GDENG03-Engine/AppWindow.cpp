#pragma once
#include "AppWindow.h"


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


	////Drawing Vertices
	//vertex list[] =
	//{
	//	//X - Y - Z
	//	{-0.5f,-0.5f,0.0f,   0,0,0}, // POS1
	//	{-0.5f,0.5f,0.0f,    1,1,0}, // POS2
	//	{ 0.5f,-0.5f,0.0f,   0,0,1},// POS2
	//	{ 0.5f,0.5f,0.0f,    1,1,1}
	//};

	//Parameters for creeating vertex buffer
	m_vb = GraphicsEngine::get()->createVertexBuffer();
	onQuadMultipleCreate();

	/*UINT size_list = ARRAYSIZE(list);*/
	/*void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();


	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();*/



	/*
	 * Things Needed
	 * 1) vb
	 * 2) sizelist, shader_byte_code, size_shader
	 * 3) m_vs,
	 * 4) m_ps,
	 *
	 * Methods:
	 * 1) When loading try looping to see if it works -------------  Results: Only one primitive has been loaded
	 * 2) Try somehow combining the list before passing the load function
	 */


	//onTriangleMultipleCreate();
	//onQuadMultipleCreate();

}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.3f, 0.4f, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	//TODO: Create a loop to draw all the triangle

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);



	//onQuadUpdate();

	 //TODO: STOP HERE

	// FINALLY DRAW THE TRIANGLE
	
	m_swap_chain->present(true);
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



void AppWindow::onQuadMultipleCreate()
{
	quadList.push_back(new Quads(-0.5f, 0));
	quadList.push_back(new Quads(-0.2f, 0));
	quadList.push_back(new Quads(0.1f, 0));


	std::vector<vertex> VertixList;
	for (unsigned int i = 0; i < quadList.size(); i++)
	{
		quadList[i]->onCreate(m_vb);
		std::vector<vertex> copy = quadList[i]->RetrieveVertexList();
		for(int j = 0; j < copy.size(); j++)
		{
			VertixList.push_back(copy[i]);
		}

	}

	//vertex* list = &VertixList[0];

	vertex *list = new vertex [VertixList.size() * sizeof(vertex)];

	for (int i = 0; i < VertixList.size(); i++) {
		list[i] = VertixList[i];
	}
	/*std::copy(VertixList.begin(), VertixList.end(), list);*/


	UINT size_list = VertixList.size();
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();


	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();

	//delete[] list;
}

void AppWindow::onQuadUpdate()
{
	for (unsigned int i = 0; i < quadList.size(); i++)
	{
		quadList[i]->onUpdate(m_vb);
	}
}

void AppWindow::onQuadRelease()
{
	for (unsigned int i = 0; i < quadList.size(); i++)
	{
		quadList[i]->onDestroy();
	}
}

