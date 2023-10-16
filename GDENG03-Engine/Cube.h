#pragma once
#include "GraphicsEngine.h"
#include "AGameObject.h"

class VertexBuffer;
class IndexBuffer;
class ConstantBuffer;

class Cube : public AGameObject
{
public:
	Cube(string name, void* shaderByteCode, size_t sizeShader);
	~Cube();


	void update(float deltaTime) override;
	void draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader) override;
	void setAnimSpeed(float speed);

	void IncrementRot(float offsetIncrease) override;



private:
	//Buffers
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	ConstantBuffer* constantBuffer;

	constant cc;

	float ticks = 0.0f;
	float deltaPos = 0.0f;
	float deltaTime = 0.0f;
	float speed = 10.0f;

	//Buffer Size
	UINT size_list = 0;
	UINT size_index_list = 0;

	
	//Vid 2 specification
	float m_rot_x = 0;
	float m_rot_y = 0;
	float m_rot_z = 0;
	

	//Rendering system test case 3:
	Vector3D scale1 = Vector3D(1,  1, 1);
	Vector3D scale2 = Vector3D(0.25f, 0.25f, 0.25f);

	Vector3D translate1 = Vector3D(1, 1, 0);
	Vector3D translate2 = Vector3D(-1, -1, 0);


};

