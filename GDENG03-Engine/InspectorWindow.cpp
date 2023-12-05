#include "InspectorWindow.h"
#include "UIManager.h"

//Game Object
#include "GameObjectManager.h"

//Component System
#include "PhysicsComponent.h"

InspectorWindow::InspectorWindow(const String name) : AUIScreen(name)
{
}

InspectorWindow::~InspectorWindow()
{
}

void InspectorWindow::drawUI()
{
	bool dare = false;
	float copy[3] = { 0,0,0 };

	float xLength = UIManager::WINDOW_WIDTH * 0.2f;
	float yLength = UIManager::WINDOW_HEIGHT * (1.0f - 0.025f);

	float xPos = UIManager::WINDOW_WIDTH - ((UIManager::WINDOW_WIDTH * 0.22f));
	float yPos = UIManager::WINDOW_HEIGHT * 0.025f;

	float xButtonSize = UIManager::WINDOW_WIDTH * 0.19f;
	float yButtonSize = UIManager::WINDOW_HEIGHT * 0.025f;

	ImGui::Begin("Inspector Window", NULL, ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove);
	//Window Specificatioon
	ImGui::SetWindowSize(ImVec2(xLength, yLength));
	ImGui::SetWindowPos(ImVec2(xPos, yPos));


	AGameObject* selectedObject = GameObjectManager::getInstance()->getSelectedObject();

	if(selectedObject == nullptr)
		ImGui::TextWrapped("No Object Selected, Select an object");

	else
	{
		String text = "Object Selected: ";
		text.append(selectedObject->RetrieveName());

		ImGui::TextWrapped(text.c_str());

		//Transform Component
		UpdateTransformGameObject(selectedObject);

		//RigidBody
		DisplayRigidBody(selectedObject);
		
	}
	ImGui::End();
}

void InspectorWindow::UpdateChildrenEnableFlag(GameObjectManager::List selectedObjectsList, bool isEnable)
{

}

void InspectorWindow::UpdateTransformGameObject(AGameObject* aObject)
{
	//Transform Properties
	float t[3] = {
		aObject->getLocalPosition().m_x,
		aObject->getLocalPosition().m_y,
		aObject->getLocalPosition().m_z
	};
	float r[3] = {
		aObject->getLocalRotation().m_x,
		aObject->getLocalRotation().m_y,
		aObject->getLocalRotation().m_z
	};
	float s[3] = {
		aObject->getLocalScale().m_x,
		aObject->getLocalScale().m_y,
		aObject->getLocalScale().m_z
	};

	ImGui::DragFloat3("Position", t, 0.1f);
	ImGui::DragFloat3("Rotation", r, 0.01f);
	ImGui::DragFloat3("Scale", s, 0.1f);

	aObject->setPosition(t[0], t[1], t[2]);
	aObject->setRotation(r[0], r[1], r[2]);
	aObject->setScale(s[0], s[1], s[2]);
}

void InspectorWindow::DisplayRigidBody(AGameObject* aObject)
{
	bool isComponentActive = false;
	PhysicsComponent* pComponent = (PhysicsComponent*)aObject->findComponentByName("Physics_Component");

	if (pComponent == nullptr)
	{
		ImGui::Text("Rigid Body: None");
		if (ImGui::Button("Add RigidBody"))
		{
			PhysicsComponent* component = new PhysicsComponent("Physics_Component", aObject, BodyType::STATIC);
			aObject->attachComponent(component);
		}
	}

	else
	{
		

		RigidBody* rigidBody = pComponent->getRigidBody();
		bool isPEnabled = rigidBody->isActive();
		bool isStatic = rigidBody->getType() == BodyType::STATIC;
		bool isGravityEnabled = rigidBody->isGravityEnabled();
		float mass = rigidBody->getMass();

		float forceVector[3] = {
			pComponent->forceVector->x,
			pComponent->forceVector->y,
			pComponent->forceVector->z };


		ImGui::Text("Rigid Body:");
		if (ImGui::Button("Detach"))
		{
			aObject->detachComponent(pComponent);
			return;
		}
		ImGui::Checkbox("Is Enabled", &isPEnabled);
		ImGui::Checkbox("Is Static", &isStatic);
		ImGui::Checkbox("Enabled Gravity", &isGravityEnabled);

		ImGui::Text("Set Mass:");
		ImGui::DragFloat("kg", &mass, 0.5f, 1.0f, 1000000.0f);
		ImGui::DragFloat3("Apply Force Vector", forceVector, 0.1f);
		pComponent->forceVector->x = forceVector[0];
		pComponent->forceVector->y = forceVector[1];
		pComponent->forceVector->z = forceVector[2];
		if (ImGui::Button("Apply Force"))
		{
			//Do Something

			rigidBody->applyLocalForceAtCenterOfMass(*pComponent->forceVector);
		}


		if (rigidBody->isActive() != isPEnabled)
			rigidBody->setIsActive(isPEnabled);
		if (isStatic)
			rigidBody->setType(BodyType::STATIC);
		else
			rigidBody->setType(BodyType::DYNAMIC);

		rigidBody->enableGravity(isGravityEnabled);
		rigidBody->setMass(mass);

	}
}
