#pragma once

#include "KCTable.hpp"
#include "KCPlayer.hpp"
#include <set>

class KCRoom : virtual public IKCCompositionObserver, virtual public IKCDriven
{
public:
	KCRoom(KCTable* table, KCPlayer* owner, IKCCompositionObserver* observer);
	~KCRoom();

	KCTable* getTable() const;
	KCPlayer* getOwner() const;
	std::set<KCPlayer*> getPlayers() const;
	virtual IKCCompositionObserver* getObserver() const;

	void addPlayer(KCPlayer* player);
	void removePlayer(KCPlayer* player);
	virtual void setObserver(IKCCompositionObserver* observer);

	virtual void propertyChanged(std::shared_ptr<KCCommand> command);

private:
	KCRoom();
	KCRoom(const KCRoom& c);

	KCTable* m_table;
	KCPlayer* m_owner;
	std::set<KCPlayer*> m_players;
	IKCCompositionObserver* m_observer;
};