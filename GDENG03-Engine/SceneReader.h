#pragma once
#include <string>

class SceneReader
{
public:
	typedef std::string String;
	typedef std::fstream FileReader;

	enum FileType
	{
		Levels,
		Unity
	};

	SceneReader(String directory);
	~SceneReader();

	void readFromFile();

private:
	String directory;
	void readFromLevelFile();
	void readFromUnityFile();
};