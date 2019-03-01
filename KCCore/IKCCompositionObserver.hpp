#pragma once

#include <memory>
#include "KCCommand.hpp"

class IKCCompositionObserver
{
public:
	virtual void propertyChanged(std::shared_ptr<KCCommand> command) = 0;
};
