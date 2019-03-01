#pragma once

#include "IKCView.hpp"
#include "KCTable.hpp"
#include "GKCImageView.hpp"
#include "GKCCardView.hpp"
#include "GKCCardsOwnerView.hpp"

#include <vector>
#include <set>


class GKCRoomView;


class GKCTableView : public GKCCardsOwnerView
{
public:
	GKCTableView(KCTable* table);
	~GKCTableView();

	KCTable* getTable() const;
	std::vector<GKCCardView*> getIntersectingHigherCardViews(GKCCardView* selectedCardView) const;
	std::vector<GKCCardView*> getIntersectingLowerCardViews(GKCCardView* selectedCardView) const;

	virtual void setFrame(KCRect rect);
    void setTable(KCTable* table);
	void checkCollisions();
	void groupCardViews(GKCCardView* cardView);
	void checkForGroupingCardViews();
	void checkForSelection(const KCPoint& position);
	void setHighestZOrder(GKCCardView* cardView);
	void checkChangingOwner(GKCRoomView* roomView, const KCPoint& position);
	void updateZOrders();
	void checkForHideCard(const KCPoint& position);
	void checkForSetAligment(const KCPoint& position);
	void checkForMoving(const KCPoint& position);

private:
	KCTable* m_table;
	GKCImageView* m_imageView;
    std::set<GKCImageView *> m_backgroundImageSet;
};