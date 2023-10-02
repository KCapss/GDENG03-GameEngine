#include "AGameObject.h"

AGameObject::AGameObject(string name)
{
	this->name = name;
	this->localPosition = Vector3D::zeros();
	this->localRotation = Vector3D::zeros();
	this->localScale = Vector3D::zeros();
}

AGameObject::~AGameObject()
{
}

void AGameObject::setPosition(float x, float y, float z)
{
}

void AGameObject::setPosition(Vector3D pos)
{
}

Vector3D AGameObject::getLocalPosition()
{
}

void AGameObject::setScale(float x, float y, float z)
{
}

void AGameObject::setScale(Vector3D scale)
{
}

Vector3D AGameObject::getLocalScale()
{
}

void AGameObject::setRotation(float x, float y, float z)
{
}

void AGameObject::setRotation(Vector3D rot)
{
}

Vector3D AGameObject::getLocalRotation()
{
}
