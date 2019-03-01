#pragma once
#include "IKCAnimationHandler.hpp"
#include "KCRect.hpp"

class GKCFrameAnimationHandler : public IKCAnimationHandler
{
public:
	virtual void animateView(IKCView* view);

	KCRect getNew() const;
	void setNew(KCRect neww);
protected:
	KCRect m_new;
};