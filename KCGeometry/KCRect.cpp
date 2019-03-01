#include "KCRect.hpp"
#include <cmath>
#include <algorithm> 
using namespace std;


KCRect::KCRect()
{
	this->m_size = KCSize();
	this->m_origin = KCPoint();
}


KCRect::KCRect(float x, float y, float width, float height)
{
	this->m_size = KCSize(width, height);
	this->m_origin = KCPoint(x, y);
}


bool KCRect::isEquals(const KCRect& V1) const
{
	return (this->getOrigin().isEquals(V1.getOrigin())) && (this->getSize().isEquals(V1.getSize()));
}


KCRect& KCRect::inset(float width, float height)
{
	m_size = KCSize(m_size.getWidth() - width, m_size.getHeight() - height );
	m_origin = KCPoint(m_origin.getX() + width, m_origin.getY() + height);
	return *this;
}


bool KCRect::isIntersects(const KCRect& other) const
{
	return ((abs(KCMidX(other) - KCMidX(*this)) < (this->getSize().getWidth() + other.getSize().getWidth())*.5f)
		&& (abs(KCMidY(other) - KCMidY(*this)) < (this->getSize().getHeight() + other.getSize().getHeight())*.5f));
}


bool KCRect::isContainsPoint(const KCPoint& point) const
{
	return (point.getX() > KCMinX(*this)) && (point.getY() > KCMinY(*this)) 
		&& (point.getX() < KCMaxX(*this)) && (point.getY() < KCMaxY(*this));
}


bool KCRect::isContainsRect(const KCRect& rect) const
{
	return 	(KCMinX(rect) > KCMinX(*this)) && (KCMinY(rect) > KCMinY(*this))
		&& (KCMaxX(rect) < KCMaxX(*this)) && (KCMaxY(rect) < KCMaxY(*this));
}


KCRect& KCRect::operator=(const KCRect& r)
{
	this->m_origin = r.getOrigin();
	this->m_size = r.getSize();
	return *this;
}


KCPoint KCRect::center() const
{
	return KCPoint(KCMidX(*this), KCMidY(*this));
}


KCRect& KCRect::unionRect(const KCRect& rect)
{
	this->getOrigin().setX(min(KCMinX(*this), KCMinX(rect)));
	this->getOrigin().setY(min(KCMinY(*this), KCMinY(rect)));
	this->getSize().setWidth(max(KCMaxX(*this), KCMaxX(rect)));
	this->getSize().setHeight(max(KCMaxY(*this), KCMaxY(rect)));
	return *this;
}


bool KCRect::isEmpty() const
{
	return (this->getSize().getHeight() != 0) && (this->getSize().getWidth() != 0);
}


KCPoint KCRect::getOrigin() const
{
	return m_origin;
}


KCSize KCRect::getSize() const
{
	return m_size;
}


void KCRect::setOrigin(KCPoint origin)
{
	if (m_origin.isEquals(origin))
		return;

	m_origin = origin;
}


void KCRect::setSize(KCSize size)
{
	if (m_size.isEquals(size))
		return;

	m_size = size;
}