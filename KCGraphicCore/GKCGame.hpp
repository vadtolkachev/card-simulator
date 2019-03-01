#pragma once
#include "IKCCompositionObserver.hpp"

class GKCRoomView;
class GKCDragAndDropController;

class GKCGame : public IKCCompositionObserver
{
public:
	GKCGame();
	void newGame();

	GKCDragAndDropController* getController() const;

	virtual void propertyChanged(std::shared_ptr<KCCommand> command);

private:
	GKCGame& operator=(const GKCGame& g);
	GKCGame(const GKCGame& g );

	GKCRoomView* m_roomView;
	GKCDragAndDropController* m_controller;
};