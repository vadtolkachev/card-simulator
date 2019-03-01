#include "GKCCardsOwnerView.hpp"

#include <algorithm>


GKCCardsOwnerView::GKCCardsOwnerView()
{

}


GKCCardsOwnerView::~GKCCardsOwnerView()
{
	for (GKCCardView* cardView : m_cardViews)
		delete cardView;
    
    m_cardViews.clear();
	m_selectedCardViews.clear();
}


void GKCCardsOwnerView::pushCard(GKCCardsOwnerView* ownerView, GKCCardView *cardView)
{
	if (ownerView->getCardsOwner()->getID() == this->getCardsOwner()->getID())
	{
		ASSERT();
		return;
	}

	std::string oldOwner;
	oldOwner = ownerView->getCardsOwner()->getID();
	removeCardView(cardView);
	ownerView->addCardView(cardView);
}


void GKCCardsOwnerView::addCardView(GKCCardView* cardView)
{
	if (this->containsCardView(cardView))
	{
		ASSERT();
		return;
	}

	m_cardViews.push_back(cardView);
}


void GKCCardsOwnerView::removeCardView(GKCCardView* cardView)
{
	if (!this->containsCardView(cardView))
	{
		ASSERT();
		return;
	}

	m_cardViews.erase(std::find(m_cardViews.begin(), m_cardViews.end(), cardView));
}


void GKCCardsOwnerView::addSelectedCardView(GKCCardView* selectedCardView)
{
	if (this->containsSelectedCardView(selectedCardView))
	{
		ASSERT();
		return;
	}

	m_selectedCardViews.push_back(selectedCardView);
	selectedCardView->getSelectTextView()->setText("s");
}


void GKCCardsOwnerView::removeSelectedCardView(GKCCardView* selectedCardView)
{
	if (!this->containsSelectedCardView(selectedCardView))
	{
		ASSERT();
		return;
	}

	m_selectedCardViews.erase(std::find(m_selectedCardViews.begin(), m_selectedCardViews.end(), selectedCardView));
	selectedCardView->getSelectTextView()->setText("");
}


void GKCCardsOwnerView::freeSelectedCardViews()
{
	for (GKCCardView* selectedCardView : m_selectedCardViews)
	{
		selectedCardView->getSelectTextView()->setText("");
	}

	while (m_selectedCardViews.size() != 0)
	{
		m_selectedCardViews.pop_back();
	}
}


KCCardsOwner* GKCCardsOwnerView::getCardsOwner() const
{
	return m_cardsOwner;
}


bool GKCCardsOwnerView::containsCardView(GKCCardView* cardView) const
{
	for (int i = 0; i < m_cardViews.size(); ++i)
		if (m_cardViews[i] == cardView)
			return true;
	return false;
}


bool GKCCardsOwnerView::containsSelectedCardView(GKCCardView* selectedCardView) const
{
	for (int i = 0; i < (int)m_selectedCardViews.size(); ++i)
		if (m_selectedCardViews[i] == selectedCardView)
			return true;
	return false;
}


GKCCardView* GKCCardsOwnerView::getCardView(std::string cardID) const
{
	for (GKCCardView* cardView : m_cardViews)
	{
		if (cardView->getCard()->getID() == cardID)
			return cardView;
	}

	return nullptr;
}


std::vector<GKCCardView *> GKCCardsOwnerView::getCardViews() const
{
	return m_cardViews;
}


std::vector<GKCCardView *> GKCCardsOwnerView::getSelectedCardViews() const
{
	return m_selectedCardViews;
}


std::vector<GKCCardView *> GKCCardsOwnerView::getSortedByHighestZOrderCardViews() const
{
	std::vector<GKCCardView *> cardViews = getCardViews();

	std::stable_sort(cardViews.begin(), cardViews.end(), [](const GKCCardView* lhs, const GKCCardView* rhs) {
		return lhs->getZOrder() > rhs->getZOrder();
	});

	return cardViews;
}


std::vector<GKCCardView *> GKCCardsOwnerView::getSortedByLowestZOrderCardViews() const
{
	std::vector<GKCCardView *> cardViews = getCardViews();

	std::stable_sort(cardViews.begin(), cardViews.end(), [](const GKCCardView* lhs, const GKCCardView* rhs) {
		return lhs->getZOrder() < rhs->getZOrder();
	});

	return cardViews;
}