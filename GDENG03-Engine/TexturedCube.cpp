#include "TexturedCube.h"
#include "GraphicsEngine.h"
#include "ShaderLibrary.h"
#include "SceneCameraHandler.h"
#include "TextureManager.h"
#include "DeviceContext.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"

TexturedCube::TexturedCube(std::string name) : Cube(name)
{
	ShaderNames shaderNames;
	void* shaderByteCode = NULL;
	size_t sizeShader = 0;
	ShaderLibrary::getInstance()->requestVertexShaderData(shaderNames.TEXTURED_VERTEX_SHADER_NAME, &shaderByteCode, &sizeShader);

	//create buffers for drawing. vertex data that needs to be drawn are temporarily placed here.
	Vector3D position_list[] =
	{
		{ Vector3D(-0.5f,-0.5f,-0.5f)},
		{ Vector3D(-0.5f,0.5f,-0.5f) },
		{ Vector3D(0.5f,0.5f,-0.5f) },
		{ Vector3D(0.5f,-0.5f,-0.5f)},

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.5f) },
		{ Vector3D(0.5f,0.5f,0.5f) },
		{ Vector3D(-0.5f,0.5f,0.5f)},
		{ Vector3D(-0.5f,-0.5f,0.5f) }
	};

	Vector2D texcoord_list[] =
	{
		{ Vector2D(0.0f,0.0f) },
		{ Vector2D(0.0f,1.0f) },
		{ Vector2D(1.0f,0.0f) },
		{ Vector2D(1.0f,1.0f) }
	};

	TexturedCube::Vertex quadList[] =
	{
		//X - Y - Z
		//FRONT FACE
		{ position_list[0],texcoord_list[1] },
		{ position_list[1],texcoord_list[0] },
		{ position_list[2],texcoord_list[2] },
		{ position_list[3],texcoord_list[3] },


		{ position_list[4],texcoord_list[1] },
		{ position_list[5],texcoord_list[0] },
		{ position_list[6],texcoord_list[2] },
		{ position_list[7],texcoord_list[3] },


		{ position_list[1],texcoord_list[1] },
		{ position_list[6],texcoord_list[0] },
		{ position_list[5],texcoord_list[2] },
		{ position_list[2],texcoord_list[3] },

		{ position_list[7],texcoord_list[1] },
		{ position_list[0],texcoord_list[0] },
		{ position_list[3],texcoord_list[2] },
		{ position_list[4],texcoord_list[3] },

		{ position_list[3],texcoord_list[1] },
		{ position_list[2],texcoord_list[0] },
		{ position_list[5],texcoord_list[2] },
		{ position_list[4],texcoord_list[3] },

		{ position_list[7],texcoord_list[1] },
		{ position_list[6],texcoord_list[0] },
		{ position_list[1],texcoord_list[2] },
		{ position_list[0],texcoord_list[3] }

	};

	this->vertexBuffer = GraphicsEngine::get()->createTexturedBuffer();
	this->vertexBuffer->load(quadList, sizeof(Vertex), ARRAYSIZE(quadList), shaderByteCode, sizeShader);

	unsigned int indexList[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};
	this->indexBuffer = GraphicsEngine::get()->createIndexBuffer();
	this->indexBuffer->load(indexList, ARRAYSIZE(indexList));

	//create constant buffer
	constant cbData = {};
	cbData.m_time = 0;
	this->constantBuffer = GraphicsEngine::get()->createConstantBuffer();
	this->constantBuffer->load(&cbData, sizeof(constant));

	//set vertex shader and pixel shader for the object
	DeviceContext* deviceContext = GraphicsEngine::get()->getImmediateDeviceContext();
	deviceContext->setRenderConfig(ShaderLibrary::getInstance()->getVertexShader(shaderNames.TEXTURED_VERTEX_SHADER_NAME),
	ShaderLibrary::getInstance()->getPixelShader(shaderNames.TEXTURED_PIXEL_SHADER_NAME));

}

TexturedCube::~TexturedCube()
{
}

void TexturedCube::draw(int width, int height)
{
	ShaderNames shaderNames;
	DeviceContext* deviceContext = GraphicsEngine::get()->getImmediateDeviceContext();
	Texture* woodTex = (Texture*)TextureManager::getInstance()->createTextureFromFile(L"Assets/Textures/wood.jpg");

	//set vertex shader and pixel shader for the object
	deviceContext->setTexture(woodTex);
	deviceContext->setRenderConfig(ShaderLibrary::getInstance()->getVertexShader(shaderNames.TEXTURED_VERTEX_SHADER_NAME), ShaderLibrary::getInstance()->getPixelShader(shaderNames.TEXTURED_PIXEL_SHADER_NAME));

	constant cbData = {};

	Matrix4x4 allMatrix; allMatrix.setIdentity();
	Matrix4x4 translationMatrix; translationMatrix.setIdentity();  translationMatrix.setTranslation(this->getLocalPosition());
	Matrix4x4 scaleMatrix; scaleMatrix.setScale(this->getLocalScale());
	Vector3D rotation = this->getLocalRotation();
	Matrix4x4 zMatrix; zMatrix.setRotationZ(rotation.m_z);
	Matrix4x4 xMatrix; xMatrix.setRotationX(rotation.m_x);
	Matrix4x4 yMatrix; yMatrix.setRotationY(rotation.m_y);

	//Scale --> Rotate --> Transform as recommended order.
	Matrix4x4 rotMatrix; rotMatrix.setIdentity();
	rotMatrix = rotMatrix.multiplyTo(zMatrix.multiplyTo(yMatrix.multiplyTo(xMatrix)));
	allMatrix = allMatrix.multiplyTo(scaleMatrix.multiplyTo(rotMatrix));
	allMatrix = allMatrix.multiplyTo(translationMatrix);
	cbData.m_world = allMatrix;

	Matrix4x4 cameraMatrix = SceneCameraHandler::getInstance()->getSceneCameraViewMatrix();
	cbData.m_view = cameraMatrix;

	//cbData.projMatrix.setOrthoLH(width / 400.0f, height / 400.0f, -4.0f, 4.0f);
	float aspectRatio = (float)width / (float)height;
	cbData.m_proj.setPerspectiveFovLH(aspectRatio, aspectRatio, 0.1f, 1000.0f);

	this->constantBuffer->update(deviceContext, &cbData);
	deviceContext->setConstantBuffer(this->constantBuffer);
	deviceContext->setIndexBuffer(this->indexBuffer);
	deviceContext->setVertexBuffer(this->vertexBuffer);

	deviceContext->drawIndexedTriangleList(this->indexBuffer->getSizeIndexList(), 0, 0);
}
