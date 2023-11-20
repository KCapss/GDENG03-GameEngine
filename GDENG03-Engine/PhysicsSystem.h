#pragma once
#include <unordered_map>
#include <vector>
#include "BaseComponentSystem.h"
#include <reactphysics3d/reactphysics3d.h>

class PhysicsComponent;

using namespace reactphysics3d;

class PhysicsSystem
{
public:
	typedef std::string String;
	typedef std::unordered_map<String, PhysicsComponent*> ComponentTable;
	typedef std::vector<PhysicsComponent*> ComponentList;

	PhysicsSystem();
	~PhysicsSystem();

	void registerComponent(PhysicsComponent* component);
	void unregisterComponent(PhysicsComponent* component);
	void unregisterComponentByName(String name);
	PhysicsComponent* findComponentByName(String name);
	ComponentList getAllComponents();

	void updateAllComponents();
	PhysicsWorld* getPhysicsWorld();
	PhysicsCommon* getPhysicsCommon();

private:
	ComponentTable componentTable;
	ComponentList componentList;

	PhysicsCommon* physicsCommon;
	PhysicsWorld* physicsWorld;
};
