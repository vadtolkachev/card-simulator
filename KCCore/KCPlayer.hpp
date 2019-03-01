#pragma once

#include "KCCardsOwner.hpp"
#include <string>

class KCPlayer : public KCCardsOwner
{
public:
	KCPlayer(std::string ID, IKCCompositionObserver* observer);

	virtual void propertyChanged(std::shared_ptr<KCCommand> command);

private:
	KCPlayer();
	KCPlayer(const KCPlayer& c);
};