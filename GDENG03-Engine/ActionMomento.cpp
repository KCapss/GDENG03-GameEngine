#include "ActionMomento.h"

ActionMemento::ActionMemento(EditorAction* oldAction, EditorAction* newAction)
{
}

ActionMemento::~ActionMemento()
{
}

EditorAction* ActionMemento::getOldAction()
{
	return oldAction;
}

EditorAction* ActionMemento::getNewAction()
{
	return newAction;
}

std::string ActionMemento::getOwnerName()
{
	return "Null";
}
