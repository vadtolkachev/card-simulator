#include "KCPoint.hpp"


KCPoint::KCPoint()
{
	this->m_x = 0;
	this->m_y = 0;
}


KCPoint::KCPoint(float x, float y)
{
	this->m_x = x;
	this->m_y = y;
}


KCPoint& KCPoint::operator= (const KCPoint& V1)
{
    this->m_x = V1.getX();
    this->m_y = V1.getY();
    return *this;
}


bool KCPoint::isEquals(const KCPoint& V1) const
{
	return (this->getX() == V1.getX()) && (this->getY() == V1.getY());
}


float KCPoint::getX() const
{
	return m_x;
}


float KCPoint::getY() const
{
	return m_y;
}


void KCPoint::setX(float x)
{
	if (m_x == x)
		return;

	m_x = x;
}


void KCPoint::setY(float y)
{
	if (m_y == y)
		return;

	m_y = y;
}
