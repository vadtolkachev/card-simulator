#include "KCCardsOwner.hpp"
#include "KCStringCommand.hpp"


KCCardsOwner::KCCardsOwner(std::string ID, IKCCompositionObserver* observer) : KCIdentifiable(ID)
{
	m_observer = observer;
};


KCCardsOwner::~KCCardsOwner()
{
    for (KCCard* card : m_cards)
        delete card;
}


std::vector<KCCard *> KCCardsOwner::getCards() const
{
	return m_cards;
}


IKCCompositionObserver* KCCardsOwner::getObserver() const
{
	return m_observer;
}


bool KCCardsOwner::containsCard(KCCard* card) const
{
	for (int i = 0; i < (int)m_cards.size(); ++i)
		if (m_cards[i] == card)
			return true;
	return false;
}


void KCCardsOwner::addCard(KCCard* card)
{
	if (this->containsCard(card))
	{
		ASSERT();
		return;
	}
	card->setObserver(this);
	m_cards.push_back(card);
}


void KCCardsOwner::removeCard(KCCard* card)
{
	if (!this->containsCard(card))
	{
		ASSERT();
		return;
	}
	m_cards.erase(std::find(m_cards.begin(), m_cards.end(), card));
}


void KCCardsOwner::setObserver(IKCCompositionObserver* observer)
{
	if (observer == nullptr)
	{
		ASSERT();
		return;
	}

	if (m_observer == observer)
		return;

	m_observer = observer;
}


void KCCardsOwner::pushCard(KCCardsOwner* cardsOwner, KCCard* card) // отдаёт карту
{   
	if (cardsOwner->getID() == this->getID())
	{
		ASSERT();
		return;
	}

	std::string oldOwner;
	oldOwner = cardsOwner->getID();
	removeCard(card);
	cardsOwner->addCard(card);

	m_observer->propertyChanged(std::shared_ptr<KCCommand>(new KCStringCommand(this, KCOP_CARD_PUSHING, card->getID(), cardsOwner->getID())));
}