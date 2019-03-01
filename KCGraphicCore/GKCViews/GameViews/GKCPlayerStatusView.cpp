#include "GKCPlayerStatusView.hpp"


GKCPlayerStatusView::GKCPlayerStatusView(std::string playerName)
{
	m_playerName = playerName;
}


std::string GKCPlayerStatusView::getPlayerName() const
{
	return m_playerName;
}

GKCImageView* GKCPlayerStatusView::getPlayerAvatar() const
{
	return m_playerAvatar;
}