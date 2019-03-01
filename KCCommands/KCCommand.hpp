#pragma once

#include "KCDefines.h"
#include "IKCDriven.hpp"

enum KCObserveProperty
{
	KCOP_CARD_HIDDEN,
	KCOP_CARD_ALIGMENT,
	KCOP_CARD_SELECTION,
	KCOP_CARD_PUSHING,
	KCOP_CARDS_PUT
};

class KCCommand
{
public:
	KCCommand(IKCDriven* driven, KCObserveProperty property)
	{
		if (driven == nullptr)
			ASSERT();
		m_driven = driven;
		m_property = property;
	}

	IKCDriven* getDriven() const
	{
		return m_driven;
	}

	void setDriven(IKCDriven* driven)
	{
		if (m_driven == driven)
			return;

		m_driven = driven;
	}

	KCObserveProperty getProperty() const
	{
		return m_property;
	}

	void setProperty(KCObserveProperty property)
	{
		if (m_property == property)
			return;

		m_property = property;
	}

protected:
	virtual ~KCCommand() {}

private:
	KCCommand();
	KCCommand(const KCCommand& c);

	IKCDriven* m_driven;
	KCObserveProperty m_property;
};