#include "GKCPlayerView.hpp"
#include "GKCViewsFactory.hpp"
#include "GKCRoomView.hpp"

#include <algorithm>

//	TODO: критическии секции, mutex, семафоры

GKCPlayerView::GKCPlayerView(KCPlayer* player)
{
	m_player = player;
    m_playerDeckView = GKCViewsFactory::makeImageView("player_deck");
    m_playerDeckView->setFrame({PlayerRectX, PlayerRectY, PlayerRectWidth, PlayerRectHeight});
	m_playerDeckView->setZOrder(PlayerDeckViewZOrder);
//	m_playerAct = GKCChangeHidden;
}


GKCPlayerView::~GKCPlayerView()
{
    delete m_playerDeckView;
}


KCPlayer* GKCPlayerView::getPlayer() const
{
	return m_player;
}


std::vector<GKCCardView *> GKCPlayerView::getSortedByXPosCardViews() const
{
	std::vector<GKCCardView *> cardViews = getCardViews();

	for (GKCCardView* cardView : cardViews)
	{
		cardViews.erase(std::find(cardViews.begin(), cardViews.end(), cardView));

		std::stable_sort(cardViews.begin(), cardViews.end(), [](const GKCCardView* lhs, const GKCCardView* rhs) {

			return KCMinX(lhs->getFrame()) < KCMinX(rhs->getFrame());
		});

		bool isInserted = false;

		for (auto selectedIt = cardViews.begin(); selectedIt != cardViews.end(); ++selectedIt)
		{
			GKCCardView* view = *selectedIt;
			if (KCMinX(cardView->getFrame()) <= KCMinX(view->getFrame()))
			{
				cardViews.insert(selectedIt, cardView);
				isInserted = true;
				break;
			}
		}
		if (!isInserted)
			cardViews.push_back(cardView);
	}

	return cardViews;
}


GKCPlayerStatusView* GKCPlayerView::getPlayerStatusView() const
{
	return m_playerStatusView;
}


void GKCPlayerView::setPlayer(KCPlayer* player)
{
	if (m_player == player)
		return;

	m_player = player;
}


void GKCPlayerView::placeCardViews()
{
	const float dist1 = DistanceBetweenCardViews; 	
	const float dist2 = DistanceBetweenCardsRowAndPlayerRectSide; 

	if (PlayerRectHeight < CardHeight)
	{
		ASSERT();
	}

	const KCRect playerCardsRect = { PlayerRectX + dist2, PlayerRectY + (PlayerRectHeight - CardHeight)/2,
		PlayerRectWidth - 2*dist2, CardHeight }; 

	float step = CardWidth + dist1; //начальный период с учетом ширины карт
	const float cardsRowWidth = getCardViews().size() * step - dist1; //ширина ряда карт

	float xPos;

	if (cardsRowWidth > KCWidth(playerCardsRect)) 
	{
		xPos = KCMinX(playerCardsRect);
		step = (KCWidth(playerCardsRect) - CardWidth) / (getCardViews().size() - 1);
	}
	else
	{
		xPos = KCMidX(playerCardsRect);
		xPos -= (getCardViews().size() * step - dist1) / 2;
	}

	for (GKCCardView* cardView : getSortedByXPosCardViews())
	{
		cardView->setFrame({ xPos, KCMinY(playerCardsRect), KCWidth(cardView->getFrame()), KCHeight(cardView->getFrame()) });
		xPos += step;
	}
}


void GKCPlayerView::updateCardViewsZOrders()
{
	for (int i = 0; i < getCardViews().size(); ++i)
	{
		getSortedByXPosCardViews()[i]->setZOrder(MinCardsZOrder + i);
	}
}


void GKCPlayerView::checkForSelection(const KCPoint& position)
{
	for (GKCCardView* cardView : getSortedByHighestZOrderCardViews())
	{
		GKCCardView* selectedCardView = dynamic_cast<GKCCardView*>(cardView->findViewAtPoint(position));
		if (selectedCardView)
		{
			addSelectedCardView(selectedCardView);
			selectedCardView->setZOrder(GKCRoomView::getMaxCardsZOrder());
			cardView->setMousePosition(position);
			break;
		}
	}
}


void GKCPlayerView::checkChangingOwner(GKCRoomView* roomView, const KCPoint &point)
{
	if (roomView->getTableView()->getSelectedCardViews().size() > 0)
	{
		std::vector<GKCCardView*> selectedCardViews = roomView->getTableView()->getSelectedCardViews();
		for (GKCCardView* cardView : selectedCardViews)
		{
			roomView->getTableView()->getTable()->pushCard(roomView->getOwnerView()->getPlayer(), cardView->getCard());
			cardView->setMousePosition(point);
		}
	}
}


void GKCPlayerView::checkForHideCard(const KCPoint& position)
{
	for (GKCCardView* cardView : getSortedByHighestZOrderCardViews())
	{
		GKCCardView* findedCardView = dynamic_cast<GKCCardView*>(cardView->findViewAtPoint(position));
		if (findedCardView)
		{
			findedCardView->getCard()->setHidden(!findedCardView->getCard()->isHidden());
			break;
		}
	}
}


void GKCPlayerView::checkForMoving(const KCPoint& position)
{
	for (GKCCardView* cardView : getCardViews())
	{
		if (containsSelectedCardView(cardView))
		{
			float dist = PlayerRectSideWidth;
			float minCardX = KCMinX(cardView->getFrame());
			float minCardY = KCMinY(cardView->getFrame());
			float maxCardX = KCMaxX(cardView->getFrame());
			float maxCardY = KCMaxY(cardView->getFrame());
			float w = KCWidth(cardView->getFrame());
			float h = KCHeight(cardView->getFrame());
			float dX = (position.getX() - cardView->getMousePosition().getX());
			float dY = (position.getY() - cardView->getMousePosition().getY());
			float minX = PlayerRectX + dist;
			float maxX = PlayerRectX + PlayerRectWidth - dist;
			float maxY = PlayerRectY + PlayerRectHeight - dist;


			if ((minCardX + dX >= minX) && (maxCardY + dY <= maxY) && (maxCardX + dX <= maxX))
			{
				cardView->setFrame({ minCardX + dX, minCardY + dY, w, h });
			}
			else
			{
				if (minCardX + dX < minX)
				{
					if (maxCardY + dY > maxY)
					{
						cardView->setFrame({ minX, maxY - h, w, h });
					}
					else
					{
						cardView->setFrame({ minX, minCardY + dY, w, h });
					}
				}
				else
				{
					if (maxCardY + dY > maxY)
					{
						if (maxCardX + dX > maxX)
						{
							cardView->setFrame({ maxX - w, maxY - h, w, h });
						}
						else
						{
							cardView->setFrame({ minCardX + dX, maxY - h, w, h });
						}
					}
				}
			}
			cardView->setMousePosition(position);
		}
	}
}