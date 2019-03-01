#include "GKCCardView.hpp"
#include "GKCViewsFactory.hpp"
#include "GKCDragAndDropController.hpp"

#include <string>


GKCCardView::GKCCardView(KCCard* card)
{
	m_card = card;
	std::string s;

	if (CardPictureSet == 1)
	{
		int rank;
		int suit;
		rank = card->getRank();
		suit = card->getSuit() + 1;
		m_frontImageName = std::to_string(suit) + "card" + std::to_string(rank);
	}
	else
	{
		if (CardPictureSet == 2)
		{
			int rank = card->getRank();;
			std::string suit;
			switch (card->getSuit())
			{
			case 0:
			{
				suit = "Diamond";
			}
			break;

			case 1:
			{
				suit = "Clubs";
			}
			break;

			case 2:
			{
				suit = "Hearts";
			}
			break;

			case 3:
			{
				suit = "Spades";
			}
			break;

			default:
				break;
			}

			m_frontImageName = suit + " " + std::to_string(rank);
		}
		else
		{
			ASSERT();
		}
	}

	m_imageView = GKCViewsFactory::makeImageView(m_frontImageName);

	m_zOrderTextView = GKCViewsFactory::makeTextView("zorder");
	m_selectTextView = GKCViewsFactory::makeTextView("");
}


GKCCardView::~GKCCardView()
{
	delete m_imageView;
	delete m_zOrderTextView;
	delete m_selectTextView;
}


KCPoint GKCCardView::getMousePosition() const
{
	return m_mousePosition;
}


KCCard* GKCCardView::getCard() const
{
	return m_card;
}


GKCImageView* GKCCardView::getImageView() const
{
	return m_imageView;
}


std::string GKCCardView::getFrontImageName() const
{
	return m_frontImageName;
}


GKCTextView* GKCCardView::getSelectTextView() const
{
	return m_selectTextView;
}


void GKCCardView::setFrame(KCRect rect)
{
	IKCView::setFrame(rect);
	m_imageView->setFrame(rect);
	m_zOrderTextView->setFrame(rect);
	m_selectTextView->setFrame({ KCMidX(rect) - 10,KCMidY(rect) - 20,KCWidth(rect),KCHeight(rect) });
}


void GKCCardView::setMousePosition(const KCPoint &mousePosition)
{
	if (m_mousePosition.isEquals(mousePosition))
		return;

	m_mousePosition = mousePosition;
}


void GKCCardView::setZOrder(int zOrder)
{
	IKCView::setZOrder(zOrder);
	m_imageView->setZOrder(zOrder);
	m_zOrderTextView->setZOrder(zOrder);
	m_selectTextView->setZOrder(zOrder);
	std::string z;
	z = std::to_string(getZOrder());
	m_zOrderTextView->setText(z);
}


void GKCCardView::changeRotatedCardFrame()
{
	float x = KCMinX(getFrame());
	float y = KCMinY(getFrame());
	float w = KCWidth(getFrame());
	float h = KCHeight(getFrame());
	setFrame({ x - (h - w) / 2, y - (w - h) / 2, h, w });
}


void GKCCardView::topMost()
{
	m_imageView->topMost();
}


void GKCCardView::move(KCPoint position)
{
	float minCardX = KCMinX(getFrame());
	float minCardY = KCMinY(getFrame());
	float maxCardX = KCMaxX(getFrame());
	float maxCardY = KCMaxY(getFrame());
	float w = KCWidth(getFrame());
	float h = KCHeight(getFrame());
	float dX = (position.getX() - getMousePosition().getX());
	float dY = (position.getY() - getMousePosition().getY());

	this->setFrame({ minCardX + dX, minCardY + dY, w, h });

	this->setMousePosition(position);
}


IKCView* GKCCardView::findViewAtPoint(KCPoint point)
{
	if (this->getFrame().isContainsPoint(point))
		return this;

	return nullptr;
}