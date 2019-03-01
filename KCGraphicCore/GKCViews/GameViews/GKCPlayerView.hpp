#pragma once

#include "GKCCardsOwnerView.hpp"
#include "KCPlayer.hpp"

#include <string>

class GKCRoomView;
class GKCPlayerStatusView;

enum GKCPlayerAct
{
	GKCTopMost,
	GKCGroupCards,
	GKCChangeHidden,
	GKCChangeAligment
};

class GKCPlayerView : public GKCCardsOwnerView
{
public:
	GKCPlayerView(KCPlayer* player);
    ~GKCPlayerView();

	//getters
	KCPlayer* getPlayer() const;
	std::vector<GKCCardView *> getSortedByXPosCardViews() const;
	GKCPlayerStatusView* getPlayerStatusView() const;

	//setters
	void setPlayer(KCPlayer* player);

	void placeCardViews();
	void updateCardViewsZOrders();
	void checkForSelection(const KCPoint& position);
	void checkChangingOwner(GKCRoomView* roomView, const KCPoint& position);
	void checkForHideCard(const KCPoint& position);
	void checkForMoving(const KCPoint& position);

private:
	GKCPlayerView();
	GKCPlayerView(const GKCPlayerView& c);

	KCPlayer* m_player;
    GKCImageView* m_playerDeckView;
	GKCPlayerStatusView* m_playerStatusView;
};