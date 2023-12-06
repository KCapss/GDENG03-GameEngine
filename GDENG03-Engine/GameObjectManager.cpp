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
				cube->setPosition(0, 5.0f, 0);
				this->addObject(cube);

				// add the Physics Component
				string componentName = "Physics_Component ";
				PhysicsComponent* component = new PhysicsComponent( componentName.append(objName), 
					cube, BodyType::DYNAMIC);
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
			this->addObject(plane);

			// add the Physics Component
			string componentName = "Physics_Component ";
			PhysicsComponent* component = new PhysicsComponent(componentName.append(objName),
				plane, BodyType::STATIC);
			plane->attachComponent((AComponent*)component);
			
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
	/*for (auto it = aList.begin(); it != aList.end();)
	{
		if (it->first % 2 != 0)
			it = c.erase(it);
		else
			++it;
	}*/

	

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

	

	
	//for (AGameObject* aObject : aList)
	//{
	//	if (aObject == gameObject)
	//	{
	//		//Potential Issue for the way how it destroye
	//		aList.erase(aObject);
	//	}
	//}
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
