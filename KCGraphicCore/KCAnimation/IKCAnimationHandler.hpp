#pragma once
#include "IKCView.hpp"

class IKCAnimationHandler
{
public:
	virtual void animateView(IKCView* view) = 0;
};