#include "KCRoom.hpp"


KCRoom::KCRoom(KCTable* table, KCPlayer* owner, IKCCompositionObserver* observer)
{
	m_observer = observer;
	m_table = table;
	m_table->setObserver(this);
	m_owner = owner;
	m_owner->setObserver(this);
}


KCRoom::~KCRoom()
{
	delete m_table;
	delete m_owner;

	while (m_players.size())
	{
		delete *m_players.begin();
		m_players.erase(m_players.begin());
	}
}


KCTable* KCRoom::getTable() const
{
	return m_table;
}


KCPlayer* KCRoom::getOwner() const
{
	return m_owner;
}


std::set<KCPlayer*> KCRoom::getPlayers() const
{
	return m_players;
}


IKCCompositionObserver* KCRoom::getObserver() const
{
	return m_observer;
}


void KCRoom::addPlayer(KCPlayer* player)
{
	if (m_players.find(player) != m_players.end())
	{
		ASSERT();
		return;
	}
	m_players.insert(player);
	player->setObserver(this);
}


void KCRoom::removePlayer(KCPlayer* player)
{
	if (m_players.find(player) == m_players.end())
	{
		ASSERT();
		return;
	}


	while(player->getCards().size())
	player->pushCard(m_table,*player->getCards().begin());

	m_players.erase(player);
	delete player;
}


void KCRoom::setObserver(IKCCompositionObserver* observer)
{
	if (observer == nullptr)
		ASSERT();

	if (m_observer == observer)
		return;

	m_observer = observer;
}


void KCRoom::propertyChanged(std::shared_ptr<KCCommand> command)
{
	m_observer->propertyChanged(command);
}