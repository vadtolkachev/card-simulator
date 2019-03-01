#include "GKCTableView.hpp"
#include "GKCViewsFactory.hpp"
#include "GKCRoomView.hpp"

#include <algorithm>


GKCTableView::GKCTableView(KCTable* table)
{
	m_table = table;
	m_imageView = GKCViewsFactory::makeImageView("cards");

	//m, n - количество изображений по x и y соответственно
	int n = 1 + TableRectWidth / BackgroundWidth;
	int m = 1 + TableRectHeight / BackgroundHeight;
    
    for (int i = 0 ; i < n; ++i)
    {
		for (int j = 0; j < m; ++j)
		{
			GKCImageView* imageView = GKCViewsFactory::makeImageView("background_table");
			imageView->setFrame({ TableRectX + i * BackgroundWidth, TableRectY + j * BackgroundHeight, BackgroundWidth, BackgroundHeight });
			imageView->setZOrder(BackgroundTableViewZOrder);
			m_backgroundImageSet.insert(imageView);
		}
    }
}


GKCTableView:: ~GKCTableView()
{
	delete m_imageView;
    getSelectedCardViews().clear();
    
    for (GKCImageView* imageView : m_backgroundImageSet)
        delete imageView;
    m_backgroundImageSet.clear();
}


std::vector<GKCCardView*> GKCTableView::getIntersectingHigherCardViews(GKCCardView* selectedCardView) const
{
	std::vector <GKCCardView*> intersectingCardViews;

	for (GKCCardView* cardView : getSortedByHighestZOrderCardViews())
	{
		if (selectedCardView->getFrame().isIntersects(cardView->getFrame()) && (cardView != selectedCardView))
		{
			intersectingCardViews.push_back(cardView);
		}
	}

	return intersectingCardViews;
}


std::vector<GKCCardView*> GKCTableView::getIntersectingLowerCardViews(GKCCardView* selectedCardView) const
{
	std::vector <GKCCardView*> intersectingCardViews;

	for (GKCCardView* cardView : getSortedByLowestZOrderCardViews())
	{
		if (selectedCardView->getFrame().isIntersects(cardView->getFrame()) && (cardView != selectedCardView))
		{
			intersectingCardViews.push_back(cardView);
		}
	}

	return intersectingCardViews;
}


KCTable* GKCTableView::getTable() const
{
	return m_table;
}


void GKCTableView::setFrame(KCRect rect)
{
	IKCView::setFrame(rect);
	m_imageView->setFrame(rect);
}


void GKCTableView::setTable(KCTable* table)
{
    m_table = table;
}


void GKCTableView::checkCollisions()
{
	for (GKCCardView* cardView : getCardViews())
	{
		float dist = TableRectSideWidth;
		if (KCMinX(cardView->getFrame()) < TableRectX + dist)
			cardView->setFrame({ TableRectX + dist,KCMinY(cardView->getFrame()), KCWidth(cardView->getFrame()) , KCHeight(cardView->getFrame()) });

		if (KCMinY(cardView->getFrame()) < TableRectY + dist)
			cardView->setFrame({ KCMinX(cardView->getFrame()), TableRectY + dist, KCWidth(cardView->getFrame()) , KCHeight(cardView->getFrame()) });

		if (KCMaxX(cardView->getFrame()) > TableRectX + TableRectWidth - dist)
			cardView->setFrame({ TableRectX + TableRectWidth - dist - KCWidth(cardView->getFrame()),KCMinY(cardView->getFrame()),
				KCWidth(cardView->getFrame()) , KCHeight(cardView->getFrame()) });

		if (KCMaxY(cardView->getFrame()) > TableRectY + TableRectHeight - dist)
			cardView->setFrame({ KCMinX(cardView->getFrame()) , TableRectY + TableRectHeight - dist - KCHeight(cardView->getFrame()),
				KCWidth(cardView->getFrame()) , KCHeight(cardView->getFrame()) });
	}
}


void GKCTableView::groupCardViews(GKCCardView* selectedCardView)
{
	std::vector<GKCCardView*> intersectingLowerCardViews = getIntersectingLowerCardViews(selectedCardView);
	float step;

	if (KCMaxX(selectedCardView->getFrame()) + intersectingLowerCardViews.size() * CardGroupsOffset > ScreenWidth)
	{
		step = -CardGroupsOffset;
	}
	else
	{
		step = CardGroupsOffset;
	}

	float xOffset = step;


	KCRect selectedCardRect = selectedCardView->getFrame();

	//setting zOrders
	for (GKCCardView* cardView : intersectingLowerCardViews)
	{
		setHighestZOrder(cardView);
	}

	setHighestZOrder(selectedCardView);


	//setting frames
	std::vector<GKCCardView*> intersectingHigherCardViews = getIntersectingHigherCardViews(selectedCardView);


	for (GKCCardView* cardView : intersectingHigherCardViews)
	{
		cardView->setFrame({KCMinX(selectedCardRect) + xOffset, KCMinY(selectedCardRect), 
			KCWidth(cardView->getFrame()), KCHeight(cardView->getFrame())});
		addSelectedCardView(cardView);
		cardView->setMousePosition(selectedCardView->getMousePosition());
		xOffset += step;
	}
}


void GKCTableView::checkForGroupingCardViews()
{
	if (getSelectedCardViews().size() == 1)
	{
			groupCardViews(getSelectedCardViews()[0]);
	}
}

//old
/*
void GKCTableView::checkForSelection(const KCPoint& position)
{
	for (GKCCardView* cardView : getSortedByHighestZOrderCardViews())
	{
		GKCCardView* selectedCardView = dynamic_cast<GKCCardView*>(cardView->findViewAtPoint(position));
		if (selectedCardView)
		{
			if (!containsSelectedCardView(selectedCardView))
			{
				addSelectedCardView(selectedCardView);
			}

			setHighestZOrder(selectedCardView);
			cardView->setMousePosition(position);
			break;
		}
	}
}
*/

//new
void GKCTableView::checkForSelection(const KCPoint& position)
{
	bool cardIsFinded = false;
	for (GKCCardView* cardView : getSortedByHighestZOrderCardViews())
	{
		GKCCardView* findedCardView = dynamic_cast<GKCCardView*>(cardView->findViewAtPoint(position));
		if (findedCardView)
		{
			cardIsFinded = true;

			/*
			bool topMost = false;
			std::vector<GKCCardView*> intersectingHigherCardViews = getIntersectingHigherCardViews(selectedCardView);
			for (GKCCardView* cardView : intersectingHigherCardViews)
			{
				if (selectedCardView->getZOrder() < cardView->getZOrder())
				{
					setHighestZOrder(selectedCardView);
					topMost = true;
					break;
				}
			}

			if (topMost == true)
				break;*/

			if (!containsSelectedCardView(findedCardView))
			{
				freeSelectedCardViews();
				addSelectedCardView(findedCardView);
			}

			setHighestZOrder(findedCardView);
			for (GKCCardView* selectedCardView : getSelectedCardViews())
			{
				selectedCardView->setMousePosition(position);
			}
			break;
		}
	}

	if (!cardIsFinded)
	{
		freeSelectedCardViews();
	}
}


void GKCTableView::setHighestZOrder(GKCCardView* cardView)
{
	int z = cardView->getZOrder() + 1;

	std::vector<GKCCardView *> cardViews = getSortedByLowestZOrderCardViews();

	for (int i = z - MinCardsZOrder; i < getCardViews().size(); i++)
	{
		cardViews[i]->setZOrder(MinCardsZOrder + i - 1);
	}
	cardView->setZOrder(GKCRoomView::getMaxCardsZOrder());


	if ((cardView->getZOrder() > GKCRoomView::getMaxCardsZOrder()) || (cardView->getZOrder() < MinCardsZOrder) )
	{
		ASSERT();
	}

	for (int i = 0; i < cardViews.size() - 1; ++i)
	{
		if (getSortedByLowestZOrderCardViews()[i]->getZOrder() != MinCardsZOrder + i)
		{
			ASSERT();
		}
	}
}


void GKCTableView::checkChangingOwner(GKCRoomView* roomView, const KCPoint& position)
{
	if (roomView->getOwnerView()->getSelectedCardViews().size() > 0)
	{
		std::vector<GKCCardView*> selectedCardViews = roomView->getOwnerView()->getSelectedCardViews();
		for (GKCCardView* cardView : selectedCardViews)
		{
			roomView->getOwnerView()->getPlayer()->pushCard(roomView->getTableView()->getTable(), cardView->getCard());
			cardView->setMousePosition(position);
		}
	}
}


void GKCTableView::updateZOrders()
{
	if (getCardViews().size() == 0)
	{
		return;
	}
	getSortedByHighestZOrderCardViews()[0]->setZOrder(MinCardsZOrder + getCardViews().size() - 1);
}


//old
/*
void GKCTableView::checkForHideCard(const KCPoint& position)
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
*/


//new
void GKCTableView::checkForHideCard(const KCPoint& position)
{
	for (GKCCardView* cardView : getSelectedCardViews())
	{
		cardView->getCard()->setHidden(!cardView->getCard()->isHidden());
	}
}


//old
/*
void GKCTableView::checkForSetAligment(const KCPoint& position)
{
	for (GKCCardView* cardView : getSortedByHighestZOrderCardViews())
	{
		GKCCardView* findedCardView = dynamic_cast<GKCCardView*>(cardView->findViewAtPoint(position));
		if (findedCardView)
		{
			if (findedCardView->getCard()->getAligment() == KCCardAligmentVertical)
				findedCardView->getCard()->setAligment(KCCardAligmentHorizontal);
			else
				findedCardView->getCard()->setAligment(KCCardAligmentVertical);
			break;
		}
	}
}
*/


//new
void GKCTableView::checkForSetAligment(const KCPoint& position)
{
	for (GKCCardView* cardView : getSelectedCardViews())
	{
		if (cardView->getCard()->getAligment() == KCCardAligmentVertical)
			cardView->getCard()->setAligment(KCCardAligmentHorizontal);
		else
			cardView->getCard()->setAligment(KCCardAligmentVertical);
	}
}


void GKCTableView::checkForMoving(const KCPoint& position)
{
	for (GKCCardView* cardView : getCardViews())
	{
		if (containsSelectedCardView(cardView))
		{
			float dist = TableRectSideWidth;
			float minCardX = KCMinX(cardView->getFrame());
			float minCardY = KCMinY(cardView->getFrame());
			float maxCardX = KCMaxX(cardView->getFrame());
			float maxCardY = KCMaxY(cardView->getFrame());
			float w = KCWidth(cardView->getFrame());
			float h = KCHeight(cardView->getFrame());
			float dX = (position.getX() - cardView->getMousePosition().getX());
			float dY = (position.getY() - cardView->getMousePosition().getY());
			float minX = TableRectX + dist;
			float minY = TableRectY + dist;
			float maxX = TableRectX + TableRectWidth - dist;
			float maxY = TableRectY + TableRectHeight - dist;
			float minPlayerX = PlayerRectX + PlayerRectSideWidth;
			float maxPlayerX = PlayerRectX + PlayerRectWidth - PlayerRectSideWidth;

			
			if ((minCardX + dX >= minX) && (minCardY + dY >= minY) && (maxCardX + dX <= maxX) 
				&& ((maxCardY + dY <= maxY) || ((minCardX + dX > minPlayerX) && (maxCardX + dX < maxPlayerX))))
			{
				cardView->setFrame({ minCardX + dX, minCardY + dY, w, h });
			}
			else
			{
				if (minCardX + dX < minX)
				{
					if (minCardY + dY < minY)
					{
						cardView->setFrame({ minX, minY, w, h });
					}
					else
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
				}
				else
				{
					if (minCardY + dY < minY)
					{
						if (maxCardX + dX > maxX)
						{
							cardView->setFrame({ maxX - w, minY, w, h });
						}
						else
						{
							cardView->setFrame({ minCardX + dX, minY, w, h });
						}
					}
					else
					{
						if (maxCardX + dX > maxX)
						{
							if (maxCardY + dY > maxY)
							{
								cardView->setFrame({ maxX - w, maxY - h, w, h });
							}
							else
							{
								cardView->setFrame({ maxX - w, minCardY + dY, w, h });
							}
						}
						else
						{
							if ((maxCardY + dY > maxY) && ((minCardX + dX < minPlayerX) || (maxCardX + dX > maxPlayerX)))
							{
								if (maxCardY <= maxY)
								{
									cardView->setFrame({ minCardX + dX, maxY - h, w, h });
								}
								else
								{
									if (minCardX + dX < minPlayerX)
									{
										cardView->setFrame({ minPlayerX, minCardY + dY, w, h });
									}
									else
									{
										if (maxCardX + dX > maxPlayerX)
										{
											cardView->setFrame({ maxPlayerX - w, minCardY + dY, w, h });
										}
									}
								}
							}
						}
					}
				}
			}
			cardView->setMousePosition(position);
		}
	}
}