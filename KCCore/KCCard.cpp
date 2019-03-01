#include "KCCard.hpp"


KCCard::KCCard(KCCardSuit suit, KCCardRank rank, IKCCompositionObserver* observer) : KCIdentifiable("")
{
	if (observer == nullptr)
		ASSERT();

	m_rank = rank;
	m_suit = suit;
	m_hidden = false;
	m_aligment = KCCardAligmentVertical;
	m_observer = observer;
}


KCCard::~KCCard()
{

}


//  Getters

bool KCCard::isHidden() const
{
	return m_hidden;
}


KCCardSuit KCCard::getSuit() const
{
	return m_suit;
}


KCCardRank KCCard::getRank() const
{
	return m_rank;
}


KCCardAligment KCCard::getAligment() const
{
	return m_aligment;
}


KCPoint KCCard::getPosition() const
{
	return m_position;
}


IKCCompositionObserver* KCCard::getObserver() const
{
	return m_observer;
}


std::string KCCard::getID() const
{
	return std::to_string(m_suit) + std::to_string(m_rank);
}


//  Setters

void KCCard::setHidden(bool hidden)
{
	if (hidden == m_hidden)
		return;

	bool oldHidden = m_hidden;

	m_hidden = hidden;
	m_observer->propertyChanged(std::shared_ptr<KCCommand>(new KCBoolCommand(this, KCOP_CARD_HIDDEN, oldHidden, m_hidden)));
}


void KCCard::setAligment(KCCardAligment aligment)
{
	if (aligment == m_aligment)
		return;

	KCCardAligment oldAligment = m_aligment;
	m_aligment = aligment;
	m_observer->propertyChanged(std::shared_ptr<KCCommand>(new KCLongCommand(this, KCOP_CARD_ALIGMENT, oldAligment, m_aligment)));
}


void KCCard::setPosition(const KCPoint& position)
{
	if (m_position.isEquals(position))
		return;

	m_position = position;
}


void KCCard::setObserver(IKCCompositionObserver* observer)
{
	if (observer == nullptr)
	{
		ASSERT();
		return;
	}

	if (observer == m_observer)
		return;

	m_observer = observer;
}


void KCCard::setID(std::string ID)
{
	ASSERT();
}