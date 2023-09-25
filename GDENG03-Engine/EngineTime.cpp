#include "EngineTime.h"

void EngineTime::initialize()
{
	if(sharedInstance == nullptr)
	{
		sharedInstance = new EngineTime;
	}

	
}

double EngineTime::getDeltaTime()
{
	return std::chrono::duration_cast<std::chrono::microseconds>(EngineTime::sharedInstance->start - EngineTime::sharedInstance->end).count();
}

EngineTime::EngineTime()
{
}

EngineTime::~EngineTime()
{
}

EngineTime::EngineTime(EngineTime const&)
{
}

void EngineTime::LogFrameStart()
{
	EngineTime::sharedInstance->start = std::chrono::system_clock::now();
}

void EngineTime::LogFrameEnd()
{
	EngineTime::sharedInstance->end = std::chrono::system_clock::now();
}
