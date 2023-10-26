#include "EngineTime.h"

#include <iomanip>


EngineTime* EngineTime::sharedInstance = nullptr;

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

	double timeElapsed = std::chrono::duration_cast<std::chrono::microseconds>
	(EngineTime::sharedInstance->start - EngineTime::sharedInstance->end).count()/ 100.0f;


	//std::cout << timeElapsed << std::endl;
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

void EngineTime::UpdateFrames()
{
	double timeElapsed = std::chrono::duration_cast<std::chrono::microseconds>
		(EngineTime::sharedInstance->end - EngineTime::sharedInstance->start).count() / 100.0f;

	deltaTime += timeElapsed;
	msPerFrame = timeElapsed;
	frames++;

	if (deltaTime > 1000.0) //One Second Worth
	{
		fps = (double)frames/msPerFrame;
		
		//std::cout << "FPS: " << fps << std::endl;
		frames = 0;
		deltaTime = 0;
	}
	msPerFrame = msPerFrame / 100.0f;

	//std::cout << "msPerFrame: " << timeElapsed << std::endl;
	
}

double EngineTime::GetFPS()
{
	
	return EngineTime::sharedInstance->fps;
}

double EngineTime::GetmsPerFrame()
{
	
	return EngineTime::sharedInstance->msPerFrame;
}


void EngineTime::LogFrameStart()
{
	EngineTime::sharedInstance->start = std::chrono::system_clock::now();
}

void EngineTime::LogFrameEnd()
{
	EngineTime::sharedInstance->end = std::chrono::system_clock::now();
	EngineTime::sharedInstance->UpdateFrames();
}
