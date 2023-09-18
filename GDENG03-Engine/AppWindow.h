#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"

//Primitives
#include "Triangle.h"
#include "Quads.h"

class AppWindow : public Window
{
public:
	AppWindow();
	~AppWindow();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;

// Assignment Based Solution
	void onTriangleMultipleCreate();
	void onTriangleUpdate();
	void onTriangleRelease();

	void onQuadMultipleCreate();
	void onQuadUpdate();
	void onQuadRelease();


private:
	SwapChain* m_swap_chain;
	VertexBuffer* m_vb;

	std::vector<Triangle*> triangleList;
	std::vector<Quads*> quadList;

	Triangle* copy1;
	Triangle* copy2;
	Triangle* copy3;
	
	
};