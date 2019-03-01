#include "GKCDragAndDropController.hpp"
#include "GKCTableView.hpp"
#include "GKCCardView.hpp"
#include "GKCViewsFactory.hpp"
#include "GKCRoomView.hpp"

#include <algorithm>


GKCDragAndDropController::GKCDragAndDropController(GKCRoomView* roomView)
{
    m_roomView = roomView;
	m_tableButton = GKCViewsFactory::makeButton();
	m_tableButton->setFrame({ TableRectX, TableRectY, TableRectWidth, TableRectHeight });

	m_ownerButton = GKCViewsFactory::makeButton();
	m_ownerButton->setFrame({ PlayerRectX, PlayerRectY, PlayerRectWidth, PlayerRectHeight });

	m_leftMenuButton = GKCViewsFactory::makeButton();
	m_leftMenuButton->setFrame({ 0, PlayerRectY, PlayerRectX, PlayerRectHeight });

	m_rightMenuButton = GKCViewsFactory::makeButton();
	m_rightMenuButton->setFrame({ PlayerRectX + PlayerRectWidth, PlayerRectY, ScreenWidth - (PlayerRectX + PlayerRectWidth), PlayerRectHeight });

	setupCallbacks();
}


GKCDragAndDropController::~GKCDragAndDropController()
{
	delete m_tableButton;
}


void GKCDragAndDropController::setupCallbacks()
{
	setupTableCallbacks();
	setupOwnerCallbacks();
	setupMenuButtonsCallbacks();
}


void GKCDragAndDropController::setupTableCallbacks()
{
	m_tableButton->onMouseDown = [=](GKCMouseButton button, const KCPoint& position) mutable {

		getRoomView()->getOwnerView()->freeSelectedCardViews();
		getRoomView()->getTableView()->checkForSelection(position);
	};


	m_tableButton->onMouseUp = [=](GKCMouseButton button, const KCPoint& poisition, int clickCount) mutable {

		getRoomView()->getTableView()->updateZOrders();
		getRoomView()->getTableView()->checkCollisions();
	};


	m_tableButton->onMouseDragged = [=](GKCMouseButton button, const KCPoint& position) mutable {

		getRoomView()->getTableView()->checkChangingOwner(this->getRoomView(), position);
		getRoomView()->getTableView()->checkForMoving(position);
	};


	m_tableButton->onMouseClicked = [=](GKCMouseButton button, const KCPoint& position) mutable {

		getRoomView()->getTableView()->updateZOrders();
	};


	m_tableButton->onMouseHold = [=](GKCMouseButton button, const KCPoint& position) mutable {

		getRoomView()->getTableView()->checkForGroupingCardViews();
	};
}


void GKCDragAndDropController::setupOwnerCallbacks()
{
	m_ownerButton->onMouseDown = [=](GKCMouseButton button, const KCPoint& position) mutable {

		KCPoint point = { position.getX() + PlayerRectX, position.getY() + PlayerRectY };

		getRoomView()->getTableView()->freeSelectedCardViews();
		m_roomView->getOwnerView()->checkForSelection(point);
	};


	m_ownerButton->onMouseUp = [=](GKCMouseButton button, const KCPoint& poisition, int clickCount) mutable {

		getRoomView()->getOwnerView()->placeCardViews();
		m_roomView->getOwnerView()->freeSelectedCardViews();
		getRoomView()->getOwnerView()->updateCardViewsZOrders();
	};


	m_ownerButton->onMouseDragged = [=](GKCMouseButton button, const KCPoint& position) mutable {

		KCPoint point = { position.getX() + PlayerRectX, position.getY() + PlayerRectY };

		getRoomView()->getOwnerView()->checkChangingOwner(getRoomView(), point);
		getRoomView()->getOwnerView()->checkForMoving(point);
	};


	m_ownerButton->onMouseClicked = [=](GKCMouseButton button, const KCPoint& position) mutable {

		KCPoint point = { position.getX() + PlayerRectX, position.getY() + PlayerRectY };

		m_roomView->getOwnerView()->freeSelectedCardViews();
		getRoomView()->getOwnerView()->updateCardViewsZOrders();
	};
}


void GKCDragAndDropController::setupMenuButtonsCallbacks()
{
	m_leftMenuButton->onMouseUp = [=](GKCMouseButton button, const KCPoint& poisition, int clickCount) mutable {

		m_ownerButton->onMouseUp(button, poisition, clickCount);
	};

	m_rightMenuButton->onMouseUp = [=](GKCMouseButton button, const KCPoint& poisition, int clickCount) mutable {

		m_ownerButton->onMouseUp(button, poisition, clickCount);
	};
}


void GKCDragAndDropController::topMost()
{
	m_tableButton->setZOrder(TableButtonZOrder);
	m_ownerButton->setZOrder(PlayerButtonZOrder);
	m_roomView->setMenuItemsButtonZOrder(MenuItemButtonZOrder);
}


GKCRoomView* GKCDragAndDropController::getRoomView()
{
	return m_roomView;
}


//	TODO::	1.	1)GKCFrameAnimationController, GKCOpacityAnimationController, GKCRotationAnimationController - наследники пункта 2
//				2)IKCAnimationController - у него будет protected virtual void animate(IKCView* view, float duration, callback completion),
//				public static void animate(IKCView* view, float duration, enum GKCAnimationType type, callback completion);
//
//			2.	textView
//			3.	cropImage