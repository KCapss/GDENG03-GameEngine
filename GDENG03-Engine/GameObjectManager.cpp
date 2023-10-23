#include "GameObjectManager.h"
#include <iostream>

#include "AGameObject.h"

//Primitives
#include "Cube.h"
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
	return 0;
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
	aList.push_back(gameObject);
	std::pair<String, AGameObject*> pair(gameObject->RetrieveName(), gameObject);
	aTable.insert(pair);
}

void GameObjectManager::createObject(PrimitiveType type, void* shaderByteCode, size_t sizeShader)
{
	switch (type)
	{
		case PrimitiveType::CUBE:
		{
			Cube* cube = new Cube("cube", shaderByteCode, sizeShader);
			addObject((AGameObject*)cube);
		}
		break;
		case PrimitiveType::PLANE:
		{
			Quads* quads = new Quads("Plane", shaderByteCode, sizeShader);
			addObject((AGameObject*)quads);
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
	selectedObject = gameObject;
}

AGameObject* GameObjectManager::getSelectedObject()
{

	return selectedObject;
}
