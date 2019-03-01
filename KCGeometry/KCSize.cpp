#include "KCSize.hpp"


KCSize::KCSize()
{
	this->m_width = 0;
	this->m_height = 0;
}


KCSize::KCSize(float width, float height)
{
	this->m_width = width;
	this->m_height = height;
}


KCSize& KCSize::operator= (const KCSize& V1)
{
	this->m_width = V1.getWidth();
	this->m_height = V1.getHeight();
	return *this;
}


float KCSize::getWidth() const
{
	return m_width;
}


float KCSize::getHeight() const
{
	return m_height;
}


void KCSize::setWidth(float width)
{
	if (m_width == width)
		return;

	m_width = width;
}


void KCSize::setHeight(float height)
{
	if (m_height == height)
		return;

	m_height = height;
}


bool KCSize::isEquals(const KCSize& V1) const
{
	return (this->getWidth() == V1.getWidth()) && (this->getHeight() == V1.getHeight());
}