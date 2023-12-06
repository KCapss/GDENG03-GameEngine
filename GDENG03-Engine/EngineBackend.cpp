#include "EngineBackend.h"
#include "GameObjectManager.h"

EngineBackend* EngineBackend::sharedInstance = nullptr;

EngineBackend* EngineBackend::getInstance()
{
}

void EngineBackend::initialize()
{
}

void EngineBackend::destroy()
{
}

void EngineBackend::setMode(EditorMode mode)
{
}

bool EngineBackend::insideFrameStep()
{
}

void EngineBackend::startFrameStep()
{
}

void EngineBackend::endFrameStep()
{
}

EngineBackend::EditorMode EngineBackend::getMode()
{
}

EngineBackend::EngineBackend()
{
}

EngineBackend::~EngineBackend()
{
}
