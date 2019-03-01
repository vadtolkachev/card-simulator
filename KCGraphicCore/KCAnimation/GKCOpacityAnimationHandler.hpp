#pragma once
#include "IKCAnimationHandler.hpp"

class GKCOpacityAnimationHandler: public IKCAnimationHandler
{
public:
	virtual void animateView(IKCView* view);

	float getNew() const;
	void setNew(float neww);
protected:
	float m_new;
};