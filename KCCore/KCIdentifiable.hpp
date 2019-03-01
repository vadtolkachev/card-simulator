#pragma once

#include <string>

class KCIdentifiable
{
public:
	KCIdentifiable(std::string ID)
	{
		m_ID = ID;
	}

	virtual ~KCIdentifiable() {};

	virtual std::string getID() const
	{
		return m_ID;
	}

	virtual void setID(std::string ID)
	{
		m_ID = ID;
	}

private:
	KCIdentifiable();
	KCIdentifiable(const KCIdentifiable& identifiable);
	std::string m_ID;
};