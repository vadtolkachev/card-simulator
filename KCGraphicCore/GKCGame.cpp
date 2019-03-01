#include "GKCGame.hpp"
#include "GKCRoomView.hpp"
#include "GKCViewsFactory.hpp"

GKCGame::GKCGame()
{

}

void GKCGame::newGame()
{
	GKCViewsFactory::sharedManager()->init();

	KCTable* table = new KCTable("t", nullptr);
	KCPlayer* owner = new KCPlayer("o", nullptr);
	KCRoom* room = new KCRoom(table, owner, nullptr);
	m_roomView = new GKCRoomView(room);
	m_roomView->setObserver(this);
    m_roomView->getTableView()->setTable(table);
	m_roomView->getOwnerView()->setPlayer(owner);
    m_controller = new GKCDragAndDropController(m_roomView);

	table->putCards();
	m_roomView->getTableView()->checkCollisions();
	GKCRoomView::setCardsCount(m_roomView->getTableView()->getCardViews().size());
	GKCRoomView::setMaxCardsZOrder(MinCardsZOrder + GKCRoomView::getCardsCount() - 1);
	
	/*
	GKCTextView* textView = GKCViewsFactory::makeTextView("some text");
	textView->setZOrder(200);
	textView->setFrame({200,400,100,50});
	*/
}

GKCDragAndDropController* GKCGame::getController() const
{
	return m_controller;
}

void GKCGame::propertyChanged(std::shared_ptr<KCCommand> command)
{
	m_controller->topMost();
}
