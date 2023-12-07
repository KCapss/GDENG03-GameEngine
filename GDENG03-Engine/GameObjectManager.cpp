#include "GameObjectManager.h"
#include <iostream>

#include "AGameObject.h"

//Primitives
#include "Cube.h"
#include "PhysicsPlane.h"
#include "MathUtils.h"
#include "PhysicsComponent.h"
#include "PhysicsSystem.h"
#include "Quads.h"

GameObjectManager* GameObjectManager::sharedInstance = nullptr;

GameObjectManager* GameObjectManager::getInstance()
{
	return sharedInstance;
}

void GameObjectManager::initialize()
{
	sharedInstance = new GameObjectManager;
}

void GameObjectManager::destroy()
{
	sharedInstance->aList.clear();
	sharedInstance->aTable.clear();

}

AGameObject* GameObjectManager::findObjectByName(String name)
{
	if(aTable[name] == nullptr)
	{
		std::cout << "Faied to Find Object" << std::endl;
		return nullptr;
	}

	return aTable[name];
}

GameObjectManager::List GameObjectManager::getAllObjects()
{
	return aList;
}

int GameObjectManager::activeObjects()
{
	//TODO: Retrieve the total number of object
	return aList.size();
}

void GameObjectManager::updateAll()
{
	for(AGameObject* gameobject: aList)
	{
		if(gameobject->IsEnabled())
			gameobject->update(EngineTime::getDeltaTime());
	}
}

void GameObjectManager::renderAll(int viewportWidth, int viewportHeight, VertexShader* vertexShader,
	PixelShader* pixels_shader)
{
	for (AGameObject* gameobject : aList)
	{
		if(gameobject->IsEnabled())
			gameobject->draw(viewportHeight, viewportWidth, vertexShader, pixels_shader);
	}
}

void GameObjectManager::addObject(AGameObject* gameObject)
{
	
	String Key = gameObject->RetrieveName();
	int i = 0;
	while (aTable[Key] != nullptr)
	{
		i++;
		Key = gameObject->RetrieveName();
		Key.append(std::to_string(i));
	}
	//std::pair<String, AGameObject*> pair(Key, gameObject);
	aTable[Key] = gameObject;
	aList.push_back(gameObject);
}

void GameObjectManager::createObject(PrimitiveType type, void* shaderByteCode, size_t sizeShader)
{
	switch (type)
	{
		case PrimitiveType::CUBE:
		{
			string objName = "Cube";
			if (cubeCount != 0)
			{
				objName.append(" (");
				objName.append(std::to_string(cubeCount));
				objName.append(") ");
			}

			Cube* cube = new Cube(objName, shaderByteCode, sizeShader);
			cube->setObjectType(AGameObject::CUBE);
			addObject((AGameObject*)cube);

			cubeCount++;
		}
		break;

		case PrimitiveType::PHYSICS_CUBE:
		{
			for (int i = 0; i < 1; i++)
			{
				string objName = "Physics Cube";
				if (pCubeCount != 0)
				{
					objName.append(" (");
					objName.append(std::to_string(pCubeCount));
					objName.append(") ");
				}

				Cube* cube = new Cube(objName, shaderByteCode, sizeShader);
				cube->setObjectType(AGameObject::PHYSICS_CUBE);
				cube->setPosition(0, 5.0f, 0);
				this->addObject(cube);

				// add the Physics Component
				string componentName = "Physics_Component ";
				PhysicsComponent* component = new PhysicsComponent( componentName.append(objName), 
					cube, BodyType::DYNAMIC);

				cube->setOverride(false);
				cube->updateLocalMatrix();
				cube->attachComponent((AComponent*)component);

				

				pCubeCount++;
			}
		}
		break;

		case PrimitiveType::PLANE:
		{
			string objName = "Plane";
			if (planeCount != 0)
			{
				objName.append(" (");
				objName.append(std::to_string(planeCount));
				objName.append(") ");
			}

			Quads* quads = new Quads(objName, shaderByteCode, sizeShader);
			quads->setObjectType(AGameObject::PLANE);
			addObject((AGameObject*)quads);

			planeCount++;
		}
		break;

		case PrimitiveType::PHYSICS_PLANE:
		{
			string objName = "Physics Plane";
			if (pPlaneCount != 0)
			{
				objName.append(" (");
				objName.append(std::to_string(pPlaneCount));
				objName.append(") ");
			}

			PhysicsPlane* plane = new PhysicsPlane(objName, shaderByteCode, sizeShader);
			plane->setObjectType(AGameObject::PHYSICS_PLANE);
			this->addObject(plane);

			// add the Physics Component
			string componentName = "Physics_Component ";
			PhysicsComponent* component = new PhysicsComponent(componentName.append(objName),
				plane, BodyType::STATIC);
			plane->attachComponent((AComponent*)component);

			plane->setOverride(false);
			plane->updateLocalMatrix();
			pPlaneCount++;
		}
		break;


		case PrimitiveType::SPHERE:
		{std::cout << "Choose Sphere" << std::endl;}
		break;

	}
	
}


void GameObjectManager::deleteObject(AGameObject* gameObject)
{


	//First Method
	for(int i = 0; i < aList.size(); i++)
	{
		if(aList[i] == gameObject)
		{
			//Potential Issue for the way how it destroyed
			//aTable.erase(pair);
			delete(aList[i]);
			aList.shrink_to_fit();
			break;
		}
	}

}

void GameObjectManager::deleteAllObjects()
{
	for (int i = 0; i < aList.size(); i++)
	{
		delete aList[i];
	}

	selectedObject = nullptr;
	aList.clear();
	aTable.clear();
}

void GameObjectManager::setSelectedObject(AGameObject* gameObject)
{
	String Key = gameObject->RetrieveName();
	int i = 0;
	while (aTable[Key] != gameObject)
	{
		i++;
		Key = gameObject->RetrieveName();
		Key.append(std::to_string(i));
	}
	selectedObject = aTable[Key];
}

AGameObject* GameObjectManager::getSelectedObject()
{
	return selectedObject;
}

void GameObjectManager::createObjectFromFile(std::string objectName, AGameObject::PrimitiveType objectType,
	Vector3D position, Vector3D rotation, Vector3D scale, float mass, bool isGravityEnabled)
{

	//Overriding from normal create objects
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	if (objectType == AGameObject::PrimitiveType::CUBE) {

		Cube* cube = new Cube(objectName, shader_byte_code, size_shader);
		cube->setPosition(position);
		cube->setRotation(rotation);
		cube->setScale(scale);
		cube->updateLocalMatrix();
		addObject(cube);
	}

	else if (objectType == AGameObject::PrimitiveType::PLANE) {
		Quads* plane = new Quads(objectName, shader_byte_code, size_shader);
		plane->setPosition(position);
		plane->setRotation(rotation);
		plane->setScale(scale);
		plane->updateLocalMatrix();
		addObject(plane);
	}

	
	else if (objectType == AGameObject::PrimitiveType::PHYSICS_CUBE) {
		Cube* cube = new Cube(objectName, shader_byte_code, size_shader);
		cube->setPosition(position);
		cube->setRotation(rotation);
		cube->setScale(scale);
		cube->update(EngineTime::getDeltaTime());
		// add the Physics Component

		string componentName = "Physics_Component ";
		PhysicsComponent* component = new PhysicsComponent(componentName.append(cube->RetrieveName()),
			cube, BodyType::DYNAMIC);

		component->getRigidBody()->setMass(mass);
		component->getRigidBody()->enableGravity(isGravityEnabled);

		cube->attachComponent((AComponent*)component);

		cube->setOverride(false);
		cube->updateLocalMatrix();
		addObject(cube);
	}

	else if (objectType == AGameObject::PrimitiveType::PHYSICS_PLANE) {
		PhysicsPlane* plane = new PhysicsPlane(objectName, shader_byte_code, size_shader);
		plane->setPosition(position);
		plane->setRotation(rotation);
		plane->setScale(scale);
		//plane->update(EngineTime::getDeltaTime());

		string componentName = "Physics_Component ";
		PhysicsComponent* component = new PhysicsComponent(componentName.append(plane->RetrieveName()),
			plane, BodyType::STATIC);

		component->getRigidBody()->setMass(mass);
		component->getRigidBody()->enableGravity(isGravityEnabled);

		plane->attachComponent((AComponent*)component);

		plane->setOverride(false);
		plane->updateLocalMatrix();
		addObject(plane);
	}
}

void GameObjectManager::batchInstantiate(void* shaderByteCode, size_t sizeShader)
{

	for(int i = 0; i < 5; i++)
	{
		string objName = "Physics Cube";
		if (pCubeCount != 0)
		{
			objName.append(" (");
			objName.append(std::to_string(pCubeCount));
			objName.append(") ");
		}

		Cube* cube = new Cube(objName, shaderByteCode, sizeShader);
		cube->setObjectType(AGameObject::PHYSICS_CUBE);
		cube->setPosition(
			MathUtils::randomFloat(-5.0f, 5.0f),
			MathUtils::randomFloat(6.0f, 8.0f),
			MathUtils::randomFloat(-5.0f, 5.0f)
		);
		cube->setRotation(
			MathUtils::randomFloat(-3.0f, 3.0f),
			MathUtils::randomFloat(-3.0f, 3.0f),
			MathUtils::randomFloat(-3.0f, 3.0f)
		);
		this->addObject(cube);

		// add the Physics Component
		string componentName = "Physics_Component ";
		PhysicsComponent* component = new PhysicsComponent(componentName.append(objName),
			cube, BodyType::DYNAMIC);

		switch(i)
		{
		case 0:
			component->getRigidBody()->setMass(1.0f);
			component->getRigidBody()->enableGravity(true);
			break;

		case 1:
			component->getRigidBody()->setMass(1.0f);
			component->getRigidBody()->enableGravity(false);
			break;

		case 2:
			component->getRigidBody()->setMass(2.0f);
			component->getRigidBody()->enableGravity(true);
			break;

		case 3:
			component->getRigidBody()->setMass(4.0f);
			component->getRigidBody()->enableGravity(true);
			break;

		case 4:
			component->getRigidBody()->setMass(5.0f);
			component->getRigidBody()->enableGravity(true);
			break;
		}
		cube->setOverride(false);
		cube->updateLocalMatrix();
		cube->attachComponent((AComponent*)component);

		pCubeCount++;
	}
}
