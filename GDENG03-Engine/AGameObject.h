#pragma once
#include <string>
#include <vector>

#include "Matrix4x4.h"
#include "Vector3D.h"
#include "EngineTime.h"
#include "AComponent.h"

__declspec(align(16))

struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	unsigned int m_time;
};


using namespace std;
class VertexShader;
class PixelShader;

class AGameObject
{
public:
	AGameObject(string name);
	~AGameObject();

	typedef vector<AComponent*> ComponentList;
	struct AQuaternion {
		float w = 0.0f;
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
	};
	enum PrimitiveType
	{
		CUBE,
		PHYSICS_CUBE,
		PLANE,
		PHYSICS_PLANE,
	};

	virtual void update(float deltaTime) = 0;
	virtual void draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader) = 0;

	void setPosition(float x, float y, float z);
	void setPosition(Vector3D pos);
	Vector3D getLocalPosition();

	void setScale(float x, float y, float z);
	void setScale(Vector3D scale);
	Vector3D getLocalScale();

	void setRotation(float x, float y, float z);
	void setRotation(Vector3D rot);
	Vector3D getLocalRotation();

	virtual void IncrementRot(float offset);
	void updateLocalMatrix();
	Matrix4x4 computeLocalMatrix();

	string RetrieveName();
	string RetrieveObjTypeName();

	void setObjectType(PrimitiveType type);
	PrimitiveType getObjectType();

	void setEnabled(bool flag);
	bool IsEnabled();

	//ComponentSystem
	void attachComponent(AComponent* component);
	void detachComponent(AComponent* component);

	AComponent* findComponentByName(string name);
	AComponent* findComponentOfType(AComponent::ComponentType type, string name);
	ComponentList getComponentsOfType(AComponent::ComponentType type);
	ComponentList getComponentsOfTypeRecursive(AComponent::ComponentType type);


	// openGL matrix to our matrix implementation
	void recomputeMatrix(float matrix[16]);
	// our matrix implementation to openGL matrix
	float* getPhysicsLocalMatrix();
	float* getNoTranslationPhysicsMatrix();

	void setOverride(bool flag);


	
private:
	string name;
	PrimitiveType objType;

	Vector3D localRotation;
	Vector3D localPosition;
	Vector3D localScale;
	bool isEnabled = true;

	//OpenGl Matrix
	float oneDLocalMatrix [16];

	

protected:
	Matrix4x4 localMatrix;
	string typeName;
	bool overrideMatrix = false;
	AQuaternion orientation;

	ComponentList componentList;

};

