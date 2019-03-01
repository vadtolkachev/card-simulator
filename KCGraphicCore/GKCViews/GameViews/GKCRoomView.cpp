#include "GKCRoomView.hpp"
#include "GKCMenuItem.hpp"


static int CardsCount;
static int MaxCardsZOrder;


GKCRoomView::GKCRoomView(KCRoom* room)
{
    m_tableView = new GKCTableView(nullptr);
	m_ownerView = new GKCPlayerView(room->getOwner());
	m_room = room;
	m_room->setObserver(this);

	m_menuItem1 = new GKCMenuItem;
	m_menuItem2 = new GKCMenuItem;
	m_menuItem3 = new GKCMenuItem;
	m_menuItem4 = new GKCMenuItem;
	m_menuItem5 = new GKCMenuItem;
	menuItemInit();
	setupCallbacks();
}


GKCRoomView::~GKCRoomView()
{
	delete m_tableView;
	delete m_ownerView;

	while (m_playerViews.size())
	{
		delete *m_playerViews.begin();
		m_playerViews.erase(m_playerViews.begin());
	}

	delete m_menuItem1;
	delete m_menuItem2;
	delete m_menuItem3;
	delete m_menuItem4;
	delete m_menuItem5;
}


int GKCRoomView::getCardsCount()
{
	return CardsCount;
}


int GKCRoomView::getMaxCardsZOrder()
{
	return MaxCardsZOrder;
}


GKCTableView* GKCRoomView::getTableView() const
{
	return m_tableView;
}


GKCPlayerView* GKCRoomView::getOwnerView() const
{
	return m_ownerView;
}


IKCCompositionObserver* GKCRoomView::getObserver() const
{
	return m_observer;
}


std::set<GKCPlayerView*> GKCRoomView::getPlayerViews() const
{
	return m_playerViews;
}


GKCMenuItem* GKCRoomView::getMenuItem1() const
{
	return m_menuItem1;
}


GKCMenuItem* GKCRoomView::getMenuItem2() const
{
	return m_menuItem2;
}


GKCMenuItem* GKCRoomView::getMenuItem3() const
{
	return m_menuItem3;
}


GKCMenuItem* GKCRoomView::getMenuItem4() const
{
	return m_menuItem4;
}


GKCMenuItem* GKCRoomView::getMenuItem5() const
{
	return m_menuItem5;
}


void GKCRoomView::setCardsCount(int cardsCount)
{
	if (CardsCount == cardsCount)
		return;

	CardsCount = cardsCount;
}


void GKCRoomView::setMaxCardsZOrder(int cardsZOrder)
{
	if (MaxCardsZOrder == cardsZOrder)
		return;

	MaxCardsZOrder = cardsZOrder;
}


void GKCRoomView::addPlayerView(GKCPlayerView* playerView)
{
	if (m_playerViews.find(playerView) != m_playerViews.end())
	{
		ASSERT();
		return;
	}

	m_playerViews.insert(playerView);
}


void GKCRoomView::removePlayerView(GKCPlayerView* playerView)
{
	if (m_playerViews.find(playerView) == m_playerViews.end())
	{
		ASSERT();
		return;
	}


	while (playerView->getCardViews().size())
		playerView->pushCard(m_tableView, *playerView->getCardViews().begin());

	m_playerViews.erase(playerView);
	delete playerView;
}


void GKCRoomView::setObserver(IKCCompositionObserver* observer)
{
	if (observer == nullptr)
		ASSERT();

	if (m_observer == observer)
		return;

	m_observer = observer;
}


void GKCRoomView::setMenuItemsButtonZOrder(int zOrder)
{
	m_menuItem1->getButton()->setZOrder(zOrder);
	m_menuItem2->getButton()->setZOrder(zOrder);
	m_menuItem3->getButton()->setZOrder(zOrder);
	m_menuItem4->getButton()->setZOrder(zOrder);
	m_menuItem5->getButton()->setZOrder(zOrder);
}


void GKCRoomView::setMenuItemsTextViewZOrder(int zOrder)
{
	getMenuItem1()->getTextView()->setZOrder(zOrder);
	getMenuItem2()->getTextView()->setZOrder(zOrder);
	getMenuItem3()->getTextView()->setZOrder(zOrder);
	getMenuItem4()->getTextView()->setZOrder(zOrder);
	getMenuItem5()->getTextView()->setZOrder(zOrder);
}


void GKCRoomView::setMenuItemsImageViewZOrder(int zOrder)
{
	m_menuItem1->getImageView()->setZOrder(zOrder);
	m_menuItem2->getImageView()->setZOrder(zOrder);
	m_menuItem3->getImageView()->setZOrder(zOrder);
	m_menuItem4->getImageView()->setZOrder(zOrder);
	m_menuItem5->getImageView()->setZOrder(zOrder);
}


void GKCRoomView::propertyChanged(std::shared_ptr<KCCommand> command)
{
	switch (command->getProperty())
	{
	case KCOP_CARDS_PUT:
	{
		KCTable* table = dynamic_cast<KCTable*>(command->getDriven());
        for (float i = 0; i < table->getCards().size(); ++i)
		{
            KCCard* card = table->getCards()[i];
			GKCCardView* cardView = new GKCCardView(card);

			float suit = card->getSuit();
			float rank = card->getRank();
			float dist1 = CardWidth + DistanceBetweenCardViews;
			float dist2 = CardHeight + DistanceBetweenCardViews;
			float dist3 = TableRectSideWidth + TableRectX;
			float dist4 = TableRectSideWidth + TableRectY;
			m_tableView->addCardView(cardView);
			cardView->setFrame({ (dist3 + (rank - 2) * dist1 ), (dist4 + suit * dist2), CardWidth, CardHeight });
			cardView->setZOrder(MinCardsZOrder + i);
		}
	}
	break;

	case KCOP_CARD_PUSHING:
	{
		KCCard* card = dynamic_cast<KCCard*>(command->getDriven());
		KCStringCommand* stringCommand = dynamic_cast<KCStringCommand*>(command.get());
		GKCCardView* cardView = m_tableView->getCardView(stringCommand->getOldValue());

		if (cardView != nullptr)
		{
			m_tableView->removeSelectedCardView(cardView);
			m_tableView->removeCardView(cardView);

			if (stringCommand->getNewValue() == m_ownerView->getPlayer()->getID())
			{
				m_ownerView->addCardView(cardView);
				m_ownerView->addSelectedCardView(cardView);
			}
		}
		else
		{
			cardView = m_ownerView->getCardView(stringCommand->getOldValue());
			if (cardView != nullptr)
			{
				m_ownerView->removeSelectedCardView(cardView);
				m_ownerView->removeCardView(cardView);

				if (stringCommand->getNewValue() == m_tableView->getTable()->getID())
				{
					m_tableView->addCardView(cardView);
					m_tableView->addSelectedCardView(cardView);
					m_tableView->setHighestZOrder(cardView);
				}
			}
		}
	}
	break;

	case KCOP_CARD_HIDDEN:
	{
		KCCard* card = dynamic_cast<KCCard*>(command->getDriven());
		KCBoolCommand* boolCommand = dynamic_cast<KCBoolCommand*>(command.get());
		GKCCardView* cardView;

		cardView = getTableView()->getCardView(card->getID());
		if (cardView != nullptr)
		{
			if (boolCommand->getNewValue() == true)
			{
				cardView->getImageView()->setImage(BackCardImageID);
			}
			else
			{
				cardView->getImageView()->setImage(cardView->getFrontImageName());
			}

		}
		else
		{
			cardView = m_ownerView->getCardView(card->getID());
			if (cardView != nullptr)
			{
				if (boolCommand->getNewValue() == true)
				{
					cardView->getImageView()->setImage(BackCardImageID);
				}
				else
				{
					cardView->getImageView()->setImage(cardView->getFrontImageName());
				}
			}
		}

	}
	break;


	case KCOP_CARD_ALIGMENT:
	{
		KCCard* card = dynamic_cast<KCCard*>(command->getDriven());
		KCLongCommand* longCommand = dynamic_cast<KCLongCommand*>(command.get());
		GKCCardView* cardView;

		cardView = getTableView()->getCardView(card->getID());
		if (cardView != nullptr)
		{
			if (longCommand->getNewValue() == KCCardAligmentVertical)
			{
				cardView->getImageView()->setViewAligmnet(GKCViewAligmentVertical);
				cardView->changeRotatedCardFrame();
				cardView->getImageView()->rotate(0);
			}
			else
			{
				cardView->getImageView()->setViewAligmnet(GKCViewAligmentHorizontal);
				cardView->changeRotatedCardFrame();
				cardView->getImageView()->rotate(90);
			}
		}
		else
		{
			cardView = m_ownerView->getCardView(card->getID());
			if (cardView != nullptr)
			{
				if (longCommand->getNewValue() == KCCardAligmentVertical)
				{
					cardView->getImageView()->rotate(0);
				}
				else
				{
					cardView->getImageView()->rotate(90);
				}
			}
		}
	}
	break;

	default:
		break;
	}



	m_observer->propertyChanged(command);
}


void GKCRoomView::menuItemInit()
{
	m_menuItem1->getTextView()->setText("hide/unhide");
	m_menuItem2->getTextView()->setText("rotate");
	float dist1 = PlayerRectX + PlayerRectWidth + (ScreenWidth - PlayerRectX - PlayerRectWidth - MenuItemWidth) / 2;
	float dist2 = (PlayerRectX - MenuItemWidth) / 2;
	float dist3 = (PlayerRectHeight - MenuItemHeight * 3) / 4;
	float dist4 = (PlayerRectHeight - MenuItemHeight * 2) / 3;

	m_menuItem1->setFrame({ dist1, PlayerRectY + dist3 * 1 + MenuItemHeight * 0, MenuItemWidth, MenuItemHeight });
	m_menuItem2->setFrame({ dist1, PlayerRectY + dist3 * 2 + MenuItemHeight * 1, MenuItemWidth, MenuItemHeight });
	m_menuItem3->setFrame({ dist1, PlayerRectY + dist3 * 3 + MenuItemHeight * 2, MenuItemWidth, MenuItemHeight });
	m_menuItem4->setFrame({ dist2, PlayerRectY + dist4 * 1 + MenuItemHeight * 0, MenuItemWidth, MenuItemHeight });
	m_menuItem5->setFrame({ dist2, PlayerRectY + dist4 * 2 + MenuItemHeight * 1, MenuItemWidth, MenuItemHeight });

	setMenuItemsTextViewZOrder(MenuItemTextZOrder);
	setMenuItemsImageViewZOrder(MenuItemImageZOrder);
	setMenuItemsButtonZOrder(MenuItemButtonZOrder);
}


void GKCRoomView::setupCallbacks()
{
	m_menuItem1->onClicked = [=](GKCMouseButton button, const KCPoint& position) mutable {

		getTableView()->checkForHideCard(position);
	};

	m_menuItem2->onClicked = [=](GKCMouseButton button, const KCPoint& position) mutable {

		getTableView()->checkForSetAligment(position);
		getTableView()->checkCollisions();
	};
}


GKCPlayerView* GKCRoomView::findPlayerView(KCPlayer* player)
{
	if (m_ownerView->getPlayer() == player)
		return m_ownerView;

	for (GKCPlayerView* playerView : m_playerViews)
		if (playerView->getPlayer() == player)
			return playerView;

	ASSERT();
	return nullptr;
}