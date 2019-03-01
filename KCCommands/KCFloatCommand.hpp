#pragma once
#include "KCCommand.hpp"

class KCFloatCommand : public KCCommand
{
public:
	KCFloatCommand(IKCDriven* driven, KCObserveProperty property, float oldValue, float newValue) : KCCommand(driven, property)
	{
		m_oldValue = oldValue;
		m_newValue = newValue;
	}

	float getOldValue() const
	{
		return m_oldValue;
	}

	float getNewValue() const
	{
		return m_newValue;
	}

private:
	KCFloatCommand();
	KCFloatCommand(const KCFloatCommand& c);

	float m_oldValue;
	float m_newValue;
};