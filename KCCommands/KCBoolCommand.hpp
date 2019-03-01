#pragma once
#include "KCCommand.hpp"

class KCBoolCommand : public KCCommand
{
public:
	KCBoolCommand(IKCDriven* driven, KCObserveProperty property, bool oldValue, bool newValue) : KCCommand(driven, property)
	{
		m_oldValue = oldValue;
		m_newValue = newValue;
	}

	bool getOldValue() const
	{
		return m_oldValue;
	}

	bool getNewValue() const
	{
		return m_newValue;
	}

private:
	KCBoolCommand();
	KCBoolCommand(const KCBoolCommand& b);

	bool m_oldValue;
	bool m_newValue;
};