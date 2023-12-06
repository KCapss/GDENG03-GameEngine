#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "AGameObject.h"


class Quads;
//Primitive
class Cube;
class PixelShader;
class VertexShader;
class AGameObject;

//Graphics



class GameObjectManager
{
public:
	typedef std::string String;
	typedef std::vector<AGameObject*> List;
	typedef std::unordered_map<String, AGameObject*> HashTable;

	enum PrimitiveType
	{
		CUBE,
		PHYSICS_CUBE,
		PLANE,
		PHYSICS_PLANE,
		SPHERE
	};

	static GameObjectManager* getInstance();
	static void initialize();
	static void destroy();

	AGameObject* findObjectByName(String name);
	List getAllObjects();
	int activeObjects();

	void updateAll();
	void renderAll(int viewportWidth, int viewportHeight, VertexShader* vertexShader, PixelShader* pixels_shader);
	void addObject(AGameObject* gameObject);

	void createObject(PrimitiveType type, void* shaderByteCode, size_t sizeShader);
	void deleteObject(AGameObject* gameObject);
	void deleteAllObjects();
	void setSelectedObject(AGameObject* gameObject);
	AGameObject* getSelectedObject();

	//Scene Saving Section
	void createObjectFromFile(std::string objectName, AGameObject::PrimitiveType objectType, 
		Vector3D position, Vector3D rotation, Vector3D scale, float mass, bool isGravityEnabled);


private:
	static GameObjectManager* sharedInstance;

	HashTable aTable;
	List aList;
	AGameObject* selectedObject = nullptr;

	// Object counts
	int cubeCount = 0;
	int planeCount = 0;
	int pCubeCount = 0;
	int pPlaneCount = 0;


	


};

