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
	Window::onCreate();
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);


	//onTriangleMultipleCreate();
	onQuadMultipleCreate();

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
	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::get()->setShaders();

	//TODO: Create a loop to draw all the triangle

	//onTriangleUpdate();
	onQuadUpdate();


	 //TODO: STOP HERE


	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	/*m_vb->release();*/
	//onTriangleRelease();
	onQuadRelease();
	m_swap_chain->release();
	GraphicsEngine::get()->release();
}

void AppWindow::onTriangleMultipleCreate()
{
	triangleList.push_back(new Triangle(-0.5f, 0));
	triangleList.push_back(new Triangle(-0.2f, 0));
	triangleList.push_back(new Triangle(0.1f, 0));

	for (unsigned int i = 0; i < triangleList.size(); i++)
	{
		triangleList[i]->onCreate();
	}
}

void AppWindow::onTriangleUpdate()
{
	
	for (unsigned int i = 0; i < triangleList.size(); i++)
	{
		GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(triangleList[i]->retrieveBuffer());
		GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleList(triangleList[i]->retrieveBuffer()->getSizeVertexList(), 0);
	}
}

void AppWindow::onTriangleRelease()
{
	for (unsigned int i = 0; i < triangleList.size(); i++)
	{
		triangleList[i]->retrieveBuffer()->release();
	}
}

void AppWindow::onQuadMultipleCreate()
{
	quadList.push_back(new Quads(-0.5f, 0));
	quadList.push_back(new Quads(-0.2f, 0));
	quadList.push_back(new Quads(0.1f, 0));

	for (unsigned int i = 0; i < quadList.size(); i++)
	{
		quadList[i]->onCreate();
	}
}

void AppWindow::onQuadUpdate()
{
	for (unsigned int i = 0; i < quadList.size(); i++)
	{
		GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(quadList[i]->retrieveBuffer());
		GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleList(quadList[i]->retrieveBuffer()->getSizeVertexList(), 0);
	}
}

void AppWindow::onQuadRelease()
{
	for (unsigned int i = 0; i < quadList.size(); i++)
	{
		quadList[i]->retrieveBuffer()->release();
	}
}

