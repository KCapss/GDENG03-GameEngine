#include "AComponent.h"

AComponent::AComponent(String name, ComponentType type, AGameObject* owner)
{
}

AComponent::~AComponent()
{
}


void AComponent::attachOwner(AGameObject* owner)
{
}

void AComponent::detachOwner()
{
}

AGameObject* AComponent::getOwner()
{
	return this->owner;
}

AComponent::ComponentType AComponent::getType()
{
	return this->type;
}

AComponent::String AComponent::getName()
{
	return this->name;
}

