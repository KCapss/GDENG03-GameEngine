#include "ActionHistory.h"

#include "ActionMomento.h"
#include "EditorAction.h"
ActionHistory* ActionHistory::sharedInstance = nullptr;
ActionHistory* ActionHistory::getInstance()
{
	return sharedInstance;
}

void ActionHistory::initialize()
{
}

void ActionHistory::destroy()
{
	delete sharedInstance;
}

void ActionHistory::startRecordAction(AGameObject* gameObject)
{
}

void ActionHistory::endRecordAction(AGameObject* gameObject)
{
}

bool ActionHistory::hasRemainingUndoActions()
{
	return false;
}

bool ActionHistory::hasRemainingRedoActions()
{
	return true;
}

EditorAction* ActionHistory::undoAction()
{
	return nullptr;
}

EditorAction* ActionHistory::redoAction()
{
	return nullptr;
}

void ActionHistory::clear()
{
}

ActionHistory::ActionHistory()
{
}

ActionHistory::~ActionHistory()
{
}
