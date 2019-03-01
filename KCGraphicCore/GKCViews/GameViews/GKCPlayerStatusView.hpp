#pragma once

#include "GKCImageView.hpp"
#include <string>

class GKCPlayerStatusView
{
public:
	GKCPlayerStatusView(std::string playerName);

	std::string getPlayerName() const;
	GKCImageView* getPlayerAvatar() const;

private:
	std::string m_playerName;
	GKCImageView* m_playerAvatar;
};