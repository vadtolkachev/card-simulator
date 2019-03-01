#include "GKCOpacityAnimationHandler.hpp"


float GKCOpacityAnimationHandler::getNew() const
{
	return m_new;
}


void GKCOpacityAnimationHandler::setNew(float neww)
{
	if (m_new == neww)
		return;

	m_new = neww;
}