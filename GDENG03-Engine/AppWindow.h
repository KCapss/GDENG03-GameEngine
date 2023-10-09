#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

//Primitives

#include "AGameObject.h"
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
	float lerp(float min, float max, float f);

	//Part 2: Cube
	void onCubeCreate(void* shader_byte_code, size_t size_shader);
	
	


private:
	SwapChain* m_swap_chain;
	VertexBuffer* m_vb;
	VertexShader* m_vs;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;
	IndexBuffer* m_ib;

	long m_old_delta;
	long m_new_delta;
	float m_delta_time;

	float m_delta_pos;
	float m_delta_scale;
	float m_delta_rot;

	
	/*std::vector<Quads*> quadList;
	std::vector<Cube*> cubeList;*/


	//extra
	//float transitionSpeed = 1.0f;

	std::vector<AGameObject*> GameObjectList;
};

