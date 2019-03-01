#pragma once
#include <vector>
#include "KCCard.hpp"
#include "KCIdentifiable.hpp"

class KCCardsOwner : public virtual IKCCompositionObserver, public virtual KCIdentifiable, public virtual IKCDriven
{
public:
	KCCardsOwner(std::string ID, IKCCompositionObserver* observer);
	virtual ~KCCardsOwner();

	std::vector<KCCard *> getCards() const;
	virtual IKCCompositionObserver* getObserver() const;
	bool containsCard(KCCard* card) const;

	void addCard(KCCard* card);
	void removeCard(KCCard* card);
	virtual void setObserver(IKCCompositionObserver* observer);

	void pushCard(KCCardsOwner* owner, KCCard *card); // отдаёт карту

protected:
	std::vector<KCCard *> m_cards;

private:
	KCCardsOwner();
	KCCardsOwner(const KCCardsOwner& o);

	IKCCompositionObserver* m_observer;
};