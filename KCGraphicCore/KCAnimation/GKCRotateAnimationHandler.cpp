#include "GKCRotateAnimationHandler.hpp"

float GKCRotateAnimationHandler::getNew() const
{
	return m_new;
}


void GKCRotateAnimationHandler::setNew(float neww)
{
	if (m_new == neww)
		return;

	m_new = neww;
}