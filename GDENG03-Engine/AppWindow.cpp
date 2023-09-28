#pragma once

#include <cmath>
#include "AppWindow.h"
#include "EngineTime.h"


__declspec(align(16))

struct constant
{
	float m_angle;
};

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


	////Parameters for creeating vertex buffer
	m_vb = GraphicsEngine::get()->createVertexBuffer();
	onQuadMultipleCreate();

	

	/*
	UINT size_list = ARRAYSIZE(list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

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
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);


	transitionSpeed += 0.5f * EngineTime::getDeltaTime();
	float speed = lerp(0.25f, 5.5f, (sin(transitionSpeed) + 1.0f) / 2.0f) + 0.01f;

	//std::cout << "Current Speed: " << speed << std::endl;
	
	m_angle += (1.57f * (float) EngineTime::getDeltaTime()) * speed;
	constant cc;
	cc.m_angle = m_angle;

	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);

	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	
	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	// FINALLY DRAW THE TRIANGLE

	//Rendering all things into vertex buffer
	for(int i = 0; i < quadList.size(); i++)
	{
		UINT vertexSize = quadList[0]->RetrieveVertexSize();

		if (quadList.size() > 1)
			GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip((m_vb->getSizeVertexList() / vertexSize) + 1, i * vertexSize);

		//Edge Case for drawing single cases
		else
			GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip((m_vb->getSizeVertexList()),0);
	}
		

	//GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);

	

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
	quadList.push_back(new Quads(-0.0f, 0.0f));
	/*quadList.push_back(new Quads(-0.2f, -0.4f));
	quadList.push_back(new Quads(0.5f, 0.2f));*/

	quadList[0]->setPosAnimationOffset(0.0f, 0.0f);
	//quadList[1]->setPosAnimationOffset(0.1f, 0.2f);
	//quadList[2]->setPosAnimationOffset(0.2f, 0.5f);


	std::vector<vertex> VertixList;
	for (unsigned int i = 0; i < quadList.size(); i++)
	{

		//Option 1 & 2
		quadList[i]->onCreate(m_vb);
		std::vector<vertex> copy = quadList[i]->RetrieveVertexList();
		for(int j = 0; j < copy.size(); j++)
		{
			vertex copyV = copy[j];
			VertixList.push_back(copyV);
		}

		

	}
	//=== Option 1
	vertex* list = &VertixList[0];

	//=== Option 2.1
	/*vertex *list = (vertex*)malloc( VertixList.size());

	

	for (int i = 0; i < VertixList.size(); i++) {
		list[i] = VertixList[i];
	}*/

	


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

	constant cc;
	cc.m_angle = 0;

	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));

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

float AppWindow::lerp(float min, float max, float f)
{
	return min * (1.0 - f) + (max * f);
}



