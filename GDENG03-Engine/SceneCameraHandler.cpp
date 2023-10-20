#include "SceneCameraHandler.h"

SceneCameraHandler* SceneCameraHandler::sharedInstance = nullptr;

SceneCameraHandler* SceneCameraHandler::getInstance()
{
	if (sharedInstance == nullptr)
	{
		sharedInstance = new SceneCameraHandler;
	}
	return sharedInstance;
}

void SceneCameraHandler::initialize()
{
	if (sharedInstance == nullptr)
	{
		sharedInstance = new SceneCameraHandler;
	}
	SceneCameraHandler::sharedInstance->sceneCamera = new Camera("Default Camera");
	SceneCameraHandler::sharedInstance->sceneCamera->setPosition(0, 3, -5.0f);
}

void SceneCameraHandler::destroy()
{
}

void SceneCameraHandler::update()
{
	SceneCameraHandler::sharedInstance->sceneCamera->update(EngineTime::getDeltaTime());
}


Matrix4x4 SceneCameraHandler::getSceneCameraViewMatrix()
{
	return SceneCameraHandler::sharedInstance->sceneCamera->getViewMatrix();
}

SceneCameraHandler::SceneCameraHandler()
{
}

SceneCameraHandler::~SceneCameraHandler()
{
}
