#include "AGameObject.h"

#include "MathUtils.h"
#include "PhysicsComponent.h"

AGameObject::AGameObject(string name)
{
	this->name = name;
	this->localPosition = Vector3D::zeros();
	this->localRotation = Vector3D::zeros();
	this->localScale = Vector3D(1.0f, 1.0f, 1.0f);
}

AGameObject::~AGameObject()
{
}

void AGameObject::setPosition(float x, float y, float z)
{
	this->localPosition = Vector3D(x, y, z);
	this->overrideMatrix = false;
}

void AGameObject::setPosition(Vector3D pos)
{
	this->localPosition = pos;
	this->overrideMatrix = false;
}

Vector3D AGameObject::getLocalPosition()
{
	return this->localPosition;

}

void AGameObject::setScale(float x, float y, float z)
{
	this->localScale = Vector3D(x, y, z);
	this->overrideMatrix = false;
}

void AGameObject::setScale(Vector3D scale)
{
	this->localScale = scale;
	this->overrideMatrix = false;
}

Vector3D AGameObject::getLocalScale()
{
	return localScale;

}

void AGameObject::setRotation(float x, float y, float z)
{
	this->localRotation = Vector3D(x, y, z);
	this->overrideMatrix = false;
}

void AGameObject::setRotation(Vector3D rot)
{
	this->localRotation = rot;
	this->overrideMatrix = false;
}

Vector3D AGameObject::getLocalRotation()
{
	return this->localRotation;
	this->overrideMatrix = false;
}

void AGameObject::IncrementRot(float offset)
{
}

void AGameObject::updateLocalMatrix()
{
	//setup transformation matrix for drawing.
	Matrix4x4 allMatrix; allMatrix.setIdentity();
	Matrix4x4 translationMatrix; translationMatrix.setIdentity();  translationMatrix.setTranslation(this->getLocalPosition());
	Matrix4x4 scaleMatrix; scaleMatrix.setIdentity();  scaleMatrix.setScale(this->getLocalScale());
	Vector3D rotation = this->getLocalRotation();
	Matrix4x4 xMatrix; xMatrix.setRotationX(rotation.m_x);
	Matrix4x4 yMatrix; yMatrix.setRotationY(rotation.m_y);
	Matrix4x4 zMatrix; zMatrix.setRotationZ(rotation.m_z);

	//Scale --> Rotate --> Transform as recommended order.
	Matrix4x4 rotMatrix; rotMatrix.setIdentity();
	rotMatrix = rotMatrix.multiplyTo(xMatrix.multiplyTo(yMatrix.multiplyTo(zMatrix)));

	allMatrix = allMatrix.multiplyTo(scaleMatrix.multiplyTo(rotMatrix));
	allMatrix = allMatrix.multiplyTo(translationMatrix);

	this->localMatrix = allMatrix;
}

Matrix4x4 AGameObject::computeLocalMatrix()
{
	//setup transformation matrix for drawing.
	Matrix4x4 allMatrix; allMatrix.setIdentity();
	Matrix4x4 translationMatrix; translationMatrix.setIdentity();  translationMatrix.setTranslation(this->getLocalPosition());
	Matrix4x4 scaleMatrix; scaleMatrix.setIdentity();  scaleMatrix.setScale(this->getLocalScale());
	Vector3D rotation = this->getLocalRotation();
	Matrix4x4 xMatrix; xMatrix.setRotationX(rotation.m_x);
	Matrix4x4 yMatrix; yMatrix.setRotationY(rotation.m_y);
	Matrix4x4 zMatrix; zMatrix.setRotationZ(rotation.m_z);

	//Scale --> Rotate --> Transform as recommended order.
	Matrix4x4 rotMatrix; rotMatrix.setIdentity();
	rotMatrix = rotMatrix.multiplyTo(xMatrix.multiplyTo(yMatrix.multiplyTo(zMatrix)));

	allMatrix = allMatrix.multiplyTo(scaleMatrix.multiplyTo(rotMatrix));
	allMatrix = allMatrix.multiplyTo(translationMatrix);

	return localMatrix;
}

string AGameObject::RetrieveName()
{
	return this->name;
}

string AGameObject::RetrieveObjTypeName()
{
	return this->typeName;
}

void AGameObject::setObjectType(PrimitiveType type)
{
	this->objType = type;
}

AGameObject::PrimitiveType AGameObject::getObjectType()
{
	return this->objType;
}

void AGameObject::setEnabled(bool flag)
{
	isEnabled = flag;
}

bool AGameObject::IsEnabled()
{
	return this->isEnabled;
}


void AGameObject::attachComponent(AComponent* component)
{
	this->componentList.push_back(component);
	component->attachOwner(this);
}

void AGameObject::detachComponent(AComponent* component)
{
	int index = -1;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i] == component) {
			index = i;
			break;
		}
	}
	if (index != -1) {
		this->componentList.erase(this->componentList.begin() + index);
	}
}

AComponent* AGameObject::findComponentByName(string name)
{
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->getName() == name) {
			return this->componentList[i];
		}
	}

	return NULL;
}

AComponent* AGameObject::findComponentOfType(AComponent::ComponentType type, string name)
{
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->getName() == name && this->componentList[i]->getType() == type) {
			return this->componentList[i];
		}
	}

	return NULL;
}



AGameObject::ComponentList AGameObject::getComponentsOfType(AComponent::ComponentType type)
{
	ComponentList foundList;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->getType() == type) {
			foundList.push_back(this->componentList[i]);
		}
	}

	return foundList;
}

AGameObject::ComponentList AGameObject::getComponentsOfTypeRecursive(AComponent::ComponentType type)
{
	ComponentList foundList;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->getType() == type) {
			foundList.push_back(this->componentList[i]);
		}
	}

	return foundList;
}

void AGameObject::recomputeMatrix(float matrix[16])
{
	float matrix4x4[4][4];
	matrix4x4[0][0] = matrix[0];
	matrix4x4[0][1] = matrix[1];
	matrix4x4[0][2] = matrix[2];
	matrix4x4[0][3] = matrix[3];

	matrix4x4[1][0] = matrix[4];
	matrix4x4[1][1] = matrix[5];
	matrix4x4[1][2] = matrix[6];
	matrix4x4[1][3] = matrix[7];

	matrix4x4[2][0] = matrix[8];
	matrix4x4[2][1] = matrix[9];
	matrix4x4[2][2] = matrix[10];
	matrix4x4[2][3] = matrix[11];

	matrix4x4[3][0] = matrix[12];
	matrix4x4[3][1] = matrix[13];
	matrix4x4[3][2] = matrix[14];
	matrix4x4[3][3] = matrix[15];

	Matrix4x4 newMatrix; newMatrix.setIdentity(); newMatrix.setMatrix(matrix4x4);
	Matrix4x4 scaleMatrix; scaleMatrix.setIdentity(); scaleMatrix.setScale(this->localScale);
	Matrix4x4 transMatrix; transMatrix.setIdentity(); transMatrix.setTranslation(this->localPosition);

	//this->localMatrix = scaleMatrix.multiplyTo(transMatrix.multiplyTo(newMatrix));
	//Get Component
	ComponentList list = this->getComponentsOfType(AComponent::ComponentType::Physics);

	/*if(list.size() == 1)
	{
		PhysicsComponent* pObject = (PhysicsComponent*)list[0];
		this->localMatrix = scaleMatrix.multiplyTo((newMatrix));
	}*/

	
		this->localMatrix = scaleMatrix.multiplyTo((newMatrix));


	this->overrideMatrix = true;
}

float* AGameObject::getPhysicsLocalMatrix()
{
	Matrix4x4 allMatrix; allMatrix.setIdentity();
	Matrix4x4 translationMatrix; translationMatrix.setIdentity();

	translationMatrix.setTranslation(this->getLocalPosition());

	Matrix4x4 scaleMatrix; scaleMatrix.setIdentity();
	scaleMatrix.setScale(Vector3D(1, 1, 1)); //physics 3D only accepts uniform scale for rigidbody
	Vector3D rotation = this->getLocalRotation();


	Matrix4x4 xMatrix; xMatrix.setIdentity(); xMatrix.setRotationX(rotation.m_x);
	Matrix4x4 yMatrix; yMatrix.setIdentity(); yMatrix.setRotationY(rotation.m_y);
	Matrix4x4 zMatrix; zMatrix.setIdentity(); zMatrix.setRotationZ(rotation.m_z);

	//Scale --> Rotate --> Transform as recommended order.
	Matrix4x4 rotMatrix; rotMatrix.setIdentity();
	rotMatrix = rotMatrix.multiplyTo(xMatrix.multiplyTo(yMatrix.multiplyTo(zMatrix)));

	allMatrix = allMatrix.multiplyTo(scaleMatrix.multiplyTo(rotMatrix));
	allMatrix = allMatrix.multiplyTo(translationMatrix);

	//float* oneDMatrix = MathUtils::convertInto1D(allMatrix);

	/*allMatrix.debugPrint();
	this->localMatrix.debugPrint();*/

	return allMatrix.getFloatArray();// allMatrix.getMatrix();
}

float* AGameObject::getNoTranslationPhysicsMatrix()
{
	Matrix4x4 allMatrix; allMatrix.setIdentity();
	

	Matrix4x4 scaleMatrix; scaleMatrix.setIdentity();
	scaleMatrix.setScale(Vector3D(1, 1, 1)); //physics 3D only accepts uniform scale for rigidbody
	Vector3D rotation = this->getLocalRotation();


	Matrix4x4 xMatrix; xMatrix.setIdentity(); xMatrix.setRotationX(rotation.m_x);
	Matrix4x4 yMatrix; yMatrix.setIdentity(); yMatrix.setRotationY(rotation.m_y);
	Matrix4x4 zMatrix; zMatrix.setIdentity(); zMatrix.setRotationZ(rotation.m_z);

	//Scale --> Rotate --> Transform as recommended order.
	Matrix4x4 rotMatrix; rotMatrix.setIdentity();
	rotMatrix = rotMatrix.multiplyTo(xMatrix.multiplyTo(yMatrix.multiplyTo(zMatrix)));

	allMatrix = allMatrix.multiplyTo(scaleMatrix.multiplyTo(rotMatrix));

	//float* oneDMatrix = MathUtils::convertInto1D(allMatrix);

	/*allMatrix.debugPrint();
	this->localMatrix.debugPrint();*/

	return allMatrix.getFloatArray();// allMatrix.getMatrix();
}

void AGameObject::setOverride(bool flag)
{
	this->overrideMatrix = flag;
}
