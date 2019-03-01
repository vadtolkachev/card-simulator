#pragma once
#include "IKCAnimationHandler.hpp"
#include <memory>
#include <functional>

class GKCAnimationController
{
	static void animateView(IKCView* view, float duration, std::shared_ptr<IKCAnimationHandler> handler, std::function <void()> completion);
};