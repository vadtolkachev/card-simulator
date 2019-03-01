#pragma once
#include "IKCView.hpp"
#include "GKCCardView.hpp"
#include "KCCardsOwner.hpp"

class GKCCardsOwnerView : public IKCView
{
public:
	GKCCardsOwnerView();
	virtual ~GKCCardsOwnerView();

	void pushCard(GKCCardsOwnerView* owner, GKCCardView *cardView); 
	void addCardView(GKCCardView* cardView);
	void removeCardView(GKCCardView* cardView);
	void addSelectedCardView(GKCCardView* selectedCardView);
	void removeSelectedCardView(GKCCardView* selectedCardView);
	void freeSelectedCardViews();

	KCCardsOwner* getCardsOwner() const;

	bool containsCardView(GKCCardView* cardView) const;
	bool containsSelectedCardView(GKCCardView* cardView) const;

	GKCCardView* getCardView(std::string cardID) const;

	std::vector<GKCCardView *> getCardViews() const;
	std::vector<GKCCardView *> getSelectedCardViews() const;
	std::vector<GKCCardView *> getSortedByHighestZOrderCardViews() const;
	std::vector<GKCCardView *> getSortedByLowestZOrderCardViews() const;

private:
	KCCardsOwner* m_cardsOwner;
	std::vector<GKCCardView*> m_cardViews;
	std::vector<GKCCardView *> m_selectedCardViews;
};