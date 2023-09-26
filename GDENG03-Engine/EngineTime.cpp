#include "EngineTime.h"


EngineTime* EngineTime::sharedInstance = NULL;

void EngineTime::initialize()
{
	if (sharedInstance == nullptr)
	{
		EngineTime::sharedInstance = new EngineTime;
	}
	LogFrameStart();
	LogFrameEnd();
	
}

double EngineTime::getDeltaTime()
{
	//return 0;
	//std::chrono::duration_cast<std::chrono::microseconds> cast;

	double timeElapsed = std::chrono::duration_cast<std::chrono::microseconds>(EngineTime::sharedInstance->start - EngineTime::sharedInstance->end).count()/ 100.0f;
	std::cout << timeElapsed << std::endl;
	return  timeElapsed;
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

//EngineTime* EngineTime::get()
//{
//	if (sharedInstance == nullptr)
//		sharedInstance = new EngineTime;
//}

void EngineTime::LogFrameStart()
{
	EngineTime::sharedInstance->start = std::chrono::system_clock::now();
}

void EngineTime::LogFrameEnd()
{
	EngineTime::sharedInstance->end = std::chrono::system_clock::now();
}
