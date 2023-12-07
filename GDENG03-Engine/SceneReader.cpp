#include "SceneReader.h"
#include <iostream>
#include <fstream>
#include "GameObjectManager.h"
#include "AGameObject.h"
#include "MathUtils.h"
#include "StringUtils.h"

SceneReader::SceneReader(String directory)
{
	this->directory = directory;
}

SceneReader::~SceneReader()
{
}

void SceneReader::readFromFile()
{
	String levelfileDir = this->directory + ".level";
	String unityfileDir = this->directory + ".unity";

	if (this->directory.find(".level") != String::npos) {
		readFromLevelFile();
	}

	else if (this->directory.find(".unity") != String::npos) {
		readFromUnityFile();
	}


	
}

void SceneReader::readFromLevelFile()
{
	String fileDir = this->directory + ".level";
	if (this->directory.find(".level") != String::npos) {
		fileDir = this->directory;
	}
	GameObjectManager::getInstance()->deleteAllObjects();
	FileReader  sceneFile;
	sceneFile.open(fileDir, std::ios::in);

	int index = 0;
	String readLine;

	String objectName;
	AGameObject::PrimitiveType objectType;
	Vector3D position;
	Vector3D rotation;
	Vector3D scale;
	String hasRigidbody = "0";


	float mass = 0;
	bool isGravityEnabled = true;
	while (std::getline(sceneFile, readLine)) {
		if (index == 0) {
			objectName = readLine;
			index++;
		}
		else if (index == 1) { // Type
			std::vector stringSplit = StringUtils::split(readLine, '|');

			objectType = (AGameObject::PrimitiveType)std::stoi(stringSplit[1]);

			hasRigidbody = stringSplit[2];

			mass = std::stof(stringSplit[3]);

			isGravityEnabled = std::stof(stringSplit[4]);

			if (objectType == AGameObject::PrimitiveType::CUBE && hasRigidbody == "1")
				objectType = AGameObject::PrimitiveType::PHYSICS_CUBE;

			if (objectType == AGameObject::PrimitiveType::PLANE && hasRigidbody == "1")
				objectType = AGameObject::PrimitiveType::PHYSICS_PLANE;
			index++;
		}
		else if (index == 2) { // Position
			std::vector stringSplit = StringUtils::split(readLine, '|');

			position = Vector3D(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]));

			index++;
		}
		else if (index == 3) { // Rotation
			std::vector stringSplit = StringUtils::split(readLine, '|');

			rotation = Vector3D(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]));

			index++;
		}
		else if (index == 4) { // Scale
			std::vector stringSplit = StringUtils::split(readLine, '|');

			scale = Vector3D(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]));

			index = 0;

			//std::cout << "Values: " << objectName << objectType << position.m_x << rotation.m_x << scale.m_x << mass << isGravityEnabled << "\n";
			GameObjectManager::getInstance()->createObjectFromFile(objectName, objectType, position, rotation, scale, mass, isGravityEnabled);
		}
	}
	sceneFile.close();
}

void SceneReader::readFromUnityFile()
{
	String fileDir = this->directory + ".unity";
	if (this->directory.find(".unity") != String::npos) {
		fileDir = this->directory;
	}

	FileReader sceneFile;
	sceneFile.open(fileDir, std::ios::in);
	String readLine;

	//Object Properties
	String objectName;
	AGameObject::PrimitiveType objectType = AGameObject::PrimitiveType::CUBE;
	Vector3D position;
	AGameObject::AQuaternion quaternion;
	Vector3D rotation;
	Vector3D scale;

	String hasRigidbody = "0";


	float mass = 0;
	bool isGravityEnabled = true;


	//Debugging Counter
	int gameObjectsCount = 0;
	int transformCount = 0;
	int rigidBodyCount = 0;

	bool isSceneSpawnerPresent = false;
	bool isValidGameObject = false; //determine if proper primitive or not
	bool isRigidBodyPresent = false;


	while (std::getline(sceneFile, readLine))
	{


		if (readLine == "GameObject:")
		{
			//omitting scenespawner
			isSceneSpawnerPresent = false;

			//Generate new object prior loading another one
			if (isValidGameObject)
			{
				GameObjectManager::getInstance()->createObjectFromFile(objectName, objectType, position, rotation, scale, mass, isGravityEnabled);
				isValidGameObject = false;
				isRigidBodyPresent = false;
			}
			
			//This a specific component
			while (std::getline(sceneFile, readLine))
			{
				bool foundName = false;
				std::vector stringSplit = StringUtils::split(readLine, ' ');
				for(string parts : stringSplit)
				{
					if (parts == "m_Name:")
					{
						foundName = true;
						readLine = readLine.substr(parts.size() + 3, readLine.size());

						if (readLine == "SceneSpawner")
						{
							isSceneSpawnerPresent = true;
							break;
						}
							
						else{
							std::cout << "Name: " << readLine << std::endl;
							isValidGameObject = true;
							objectName = readLine;

							//TODO: Do Some Filtering
							readLine = readLine.substr(0, 6);

							if(readLine == "Plane ")
								objectType = AGameObject::PLANE;

							readLine = readLine.substr(0, 5);

							if (readLine == "Cube ")
								objectType = AGameObject::CUBE;


							
						}
						break;
					}
				}
				if (foundName) break;
			}
		}
		

		if (readLine == "Transform:" && !isSceneSpawnerPresent)
		{
			//after scale
			
			transformCount++;

			while (std::getline(sceneFile, readLine))
			{
				bool isFinishedImportingTransform = false;
				std::vector stringSplit = StringUtils::split(readLine, ' ');
				for (string parts : stringSplit)
				{
					if (parts == "m_LocalRotation:")
					{
						double x = std::stof(stringSplit[4]);
						double y = std::stof(stringSplit[6]);
						double z = std::stof(stringSplit[8]);
						double w = std::stof(stringSplit[10]);

						rotation = MathUtils::convertQuateriontoEuler(w, x, y, z);

						//rotation = Vector3D(0, 0, 0);
					}

					if (parts == "m_LocalPosition:")
					{
						float x = std::stof(stringSplit[4]);
						float y = std::stof(stringSplit[6]);
						float z = std::stof(stringSplit[8]);

						position = Vector3D(x, y, z);
						
					}

					if (parts == "m_LocalScale:")
					{
						float x = std::stof(stringSplit[4]);
						float y = std::stof(stringSplit[6]);
						float z = std::stof(stringSplit[8]);

						scale = Vector3D(x, y, z);

						isFinishedImportingTransform = true;
						break;
					}
				}

				if (isFinishedImportingTransform) break;
			}

			
		}
			

		if (readLine == "Rigidbody:")
		{
			while (std::getline(sceneFile, readLine))
			{
				bool isFinishedPhysics = false;
				std::vector stringSplit = StringUtils::split(readLine, ' ');
				for (string parts : stringSplit)
				{
					if (parts == "m_Mass:")
					{
						mass = stoi(stringSplit[3]);
					}

					if (parts == "m_UseGravity:")
					{
						int flag = std::stoi(stringSplit[3]);
						if (flag == 1)
							isGravityEnabled = true;

						else isGravityEnabled = false;
						

					}

					if (parts == "m_IsKinematic:")
					{
						int flag = std::stoi(stringSplit[3]);
						if (flag == 1)
							objectType = AGameObject::PHYSICS_PLANE;

						else 
							objectType = AGameObject::PHYSICS_CUBE;

						isFinishedPhysics = true;
						break;
					}
				}

				if (isFinishedPhysics) break;
			}
		}
			rigidBodyCount++;
		//std::cout << readLine << std::endl;
	}

	//Generate new object prior loading another one
	if (isValidGameObject)
	{
		GameObjectManager::getInstance()->createObjectFromFile(objectName, objectType, position,
			rotation, scale, mass, isGravityEnabled);

		isValidGameObject = false;
		isRigidBodyPresent = false;
	}
	/*std::cout << "GOCount: " << gameObjectsCount << std::endl;
	std::cout << "TCount: " << transformCount << std::endl;
	std::cout << "RbCount: " << rigidBodyCount << std::endl;*/
}
