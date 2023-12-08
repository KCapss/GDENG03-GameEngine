#include "EditorAction.h"

EditorAction::EditorAction(AGameObject* gameObject)
{
}

EditorAction::~EditorAction()
{
}

std::string EditorAction::getOwnerName()
{
	return this->objectName;
}

AGameObject* EditorAction::getOwner()
{
	return owner;
}

Vector3D EditorAction::getStorePos()
{
	return this->localPosition;
}

Vector3D EditorAction::getStoredScale()
{
	return this->localScale;
}

AGameObject::AQuaternion EditorAction::getStoredOrientation()
{
	return this->orientation;
}

Matrix4x4 EditorAction::getStoredMatrix()
{
	return this->localMatrix;
}
