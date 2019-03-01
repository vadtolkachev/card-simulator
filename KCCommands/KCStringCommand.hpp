#pragma once
#include "KCCommand.hpp"
#include <string>
using namespace std;

class KCStringCommand : public KCCommand
{
public:
	KCStringCommand(IKCDriven* driven, KCObserveProperty property, string oldValue, string newValue) : KCCommand(driven, property)
	{
		m_oldValue = oldValue;
		m_newValue = newValue;
	}

	string getOldValue() const
	{
		return m_oldValue;
	}

	string getNewValue() const
	{
		return m_newValue;
	}

private:
	KCStringCommand();
	KCStringCommand(const KCStringCommand& c);

	string m_oldValue;
	string m_newValue;
};