#include "KCTable.hpp"


void KCTable::putCards()
{
	for (int r = 2; r < 15; ++r)
	{
		for (int s = 0; s < 4; ++s)
		{
			KCCard* card = new KCCard((KCCardSuit)s, (KCCardRank)r, this);
			m_cards.push_back(card);
		}
	}
	getObserver()->propertyChanged(std::shared_ptr<KCCommand>(new KCStringCommand(this, KCOP_CARDS_PUT, "", "")));
}


void KCTable::propertyChanged(std::shared_ptr<KCCommand> command)
{
	getObserver()->propertyChanged(command);
}