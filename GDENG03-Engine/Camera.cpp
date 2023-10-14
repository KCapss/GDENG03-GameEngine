#include "Camera.h"
#include "InputSystem.h"

Camera::Camera(string name) : AGameObject(name), InputListener()
{
	InputSystem::getInstance()->addListener(this);
}

Camera::~Camera()
{
}

void Camera::update(float deltaTime)
{
	m_delta_time = deltaTime;
	UpdateViewMatrix();

	Vector3D localPos = this->getLocalPosition();
	float x = localPos.m_x;
	float y = localPos.m_y;
	float z = localPos.m_z;
	float moveSpeed = 10.0f;

	if(InputSystem::getInstance()->isKeyDown('W'))
	{
		z += deltaTime * moveSpeed;
		this->setPosition(x, y, z);
		this->UpdateViewMatrix();
	}

	if (InputSystem::getInstance()->isKeyDown('S'))
	{
		z -= deltaTime * moveSpeed;
		this->setPosition(x, y, z);
		this->UpdateViewMatrix();
	}

	if (InputSystem::getInstance()->isKeyDown('A'))
	{
		x -= deltaTime * moveSpeed;
		this->setPosition(x, y, z);
		this->UpdateViewMatrix();
	}

	if (InputSystem::getInstance()->isKeyDown('D'))
	{
		x += deltaTime * moveSpeed;
		this->setPosition(x, y, z);
		this->UpdateViewMatrix();
	}

	

}

void Camera::draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader)
{
	
}

Matrix4x4 Camera::getViewMatrix()
{
	return this->localMatrix;
}

void Camera::onKeyDown(int key)
{
}

void Camera::onKeyUp(int key)
{
}

void Camera::onMouseMove(const Point deltaPos)
{
	if (isRightClick) {
		m_rot_x += (deltaPos.getY()) * m_delta_time * 0.3f;
		m_rot_y += (deltaPos.getX()) * m_delta_time * 0.3f;
	}
}

void Camera::onLeftMouseDown(const Point deltaPos)
{
}

void Camera::onLeftMouseUp(const Point deltaPos)
{
}

void Camera::onRightMouseDown(const Point deltaPos)
{
	isRightClick = true;
}

void Camera::onRightMouseUp(const Point deltaPos)
{
	isRightClick = false;
}

void Camera::UpdateViewMatrix()
{
	Matrix4x4 worldCam;
	worldCam.setIdentity();
	Matrix4x4 temp;
	temp.setIdentity();

	Vector3D localRot = this->getLocalRotation();

	temp.setRotationX(localRot.m_x);
	worldCam *= temp;

	temp.setIdentity();
	temp.setRotationY(localRot.m_y);
	worldCam *= temp;

	temp.setIdentity();
	temp.setRotationX(m_rot_x);
	worldCam *= temp;

	temp.setIdentity();
	temp.setRotationY(m_rot_y);
	worldCam *= temp;

	temp.setIdentity();
	temp.setTranslation(this->getLocalPosition());
	worldCam *= temp;

	worldCam.inverse();
	this->localMatrix = worldCam;
}
