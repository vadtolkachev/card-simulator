#include "GKCFrameAnimationHandler.hpp"

KCRect GKCFrameAnimationHandler::getNew() const
{
	return m_new;
}


void GKCFrameAnimationHandler::setNew(KCRect neww)
{
	if (m_new.isEquals(neww))
		return;

	m_new = neww;
}