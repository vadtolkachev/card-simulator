#pragma once
#include "GKCButton.hpp"

class GKCRoomView;

class GKCDragAndDropController
{
public:

	GKCDragAndDropController(GKCRoomView* roomView);

	~GKCDragAndDropController();
	void setupCallbacks();
	void setupTableCallbacks();
	void setupOwnerCallbacks();
	void setupMenuButtonsCallbacks();
	void topMost();

	GKCRoomView* getRoomView();

private:
	GKCButton* m_ownerButton;
	GKCButton* m_tableButton;
	GKCButton* m_leftMenuButton;
	GKCButton* m_rightMenuButton;
	GKCRoomView* m_roomView;
};
