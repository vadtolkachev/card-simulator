#pragma once
#include "KCCommand.hpp"

class KCLongCommand : public KCCommand
{
public:
	KCLongCommand(IKCDriven* driven, KCObserveProperty property, long oldValue, long newValue) : KCCommand(driven, property)
	{
		m_oldValue = oldValue;
		m_newValue = newValue;
	}

	long getOldValue() const
	{
		return m_oldValue;
	}

	long getNewValue() const
	{
		return m_newValue;
	}

private:
	KCLongCommand();
	KCLongCommand(const KCLongCommand& c);

	long m_oldValue;
	long m_newValue;
};