#pragma once
#include "KCCardsOwner.hpp"

class KCTable : public KCCardsOwner
{
public:
	KCTable(std::string ID, IKCCompositionObserver* observer):KCCardsOwner(ID, observer), KCIdentifiable(ID) {};

	void putCards();
	virtual void propertyChanged(std::shared_ptr<KCCommand> command);

private:
	KCTable();
	KCTable(const KCTable& t);
};