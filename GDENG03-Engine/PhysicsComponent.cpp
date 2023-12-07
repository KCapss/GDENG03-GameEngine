#include "PhysicsComponent.h"
#include <iostream>
#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"
#include "AGameObject.h"
#include "Vector3D.h"

PhysicsComponent::PhysicsComponent(String name, AGameObject* owner, BodyType type) : AComponent(name, AComponent::ComponentType::Physics, owner)
{

	//whenever a new physics component is initialized. Register to physics system
	PhysicsSystem* physicsSystem = BaseComponentSystem::getInstance()->getPhysicsSystem();
	physicsSystem->registerComponent(this);
	PhysicsCommon* physicsCommon = physicsSystem->getPhysicsCommon();
	PhysicsWorld* physicsWorld = physicsSystem->getPhysicsWorld();

	// Create a rigid body in the world
	Vector3D scale = this->getOwner()->getLocalScale();
	Transform transform;
	transform.setFromOpenGL(this->getOwner()->getPhysicsLocalMatrix());
	BoxShape* boxShape;


	//Resolving Issues With Rigid Body Type
	boxShape = physicsCommon->createBoxShape(Vector3(scale.m_x / 2.0f,
		scale.m_y / 2.0f, scale.m_z / 2.0f)); //half extentP
	

	this->rigidBody = physicsWorld->createRigidBody(transform);
	//this->rigidBody->setLocalCenterOfMass(Vector3(owner->getLocalPosition().m_x, owner->getLocalPosition().m_y, owner->getLocalPosition().m_z));


	//Potential Issue with collider = only local
	Transform noTranslateTransform;
	transform.setFromOpenGL(this->getOwner()->getNoTranslationPhysicsMatrix());

	collider = this->rigidBody->addCollider(boxShape, noTranslateTransform);
	this->rigidBody->updateMassPropertiesFromColliders();
	this->rigidBody->setMass(this->mass);
	
	

	transform = this->rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	this->getOwner()->recomputeMatrix(matrix);

	//Collision Filtering 
	if (type == BodyType::DYNAMIC) 
	{
		this->rigidBody->setType(BodyType::DYNAMIC);
	}

	else
	{
		rigidBody->setType(BodyType::STATIC);
	}

	forceVector = new Vector3(0, 0, 0);
}

PhysicsComponent::~PhysicsComponent()
{
	BaseComponentSystem::getInstance()->getPhysicsSystem()->unregisterComponent(this);
	AComponent::~AComponent();
}

void PhysicsComponent::perform(float deltaTime)
{
	const Transform transform = this->rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	this->getOwner()->recomputeMatrix(matrix);

	//getOwner()->setRotation(transform.getOrientation().x, transform.getOrientation().y, transform.getOrientation().z);
	//getOwner()->setPosition(transform.getPosition().x, transform.getPosition().y, transform.getPosition().z);

	

	timer += deltaTime;
	
	
	//std::cout << "My component is updating: " << this->name << "\n";
}

RigidBody* PhysicsComponent::getRigidBody()
{
	return this->rigidBody;
}