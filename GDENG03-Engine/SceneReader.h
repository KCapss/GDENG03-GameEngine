#pragma once
#include <string>

class SceneReader
{
public:
	typedef std::string String;
	typedef std::fstream FileReader;
	SceneReader(String directory);
	~SceneReader();

	void readFromFile();

private:
	String directory;
};