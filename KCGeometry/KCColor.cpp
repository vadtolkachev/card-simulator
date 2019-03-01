#include "KCColor.hpp"

KCColor::KCColor() 
: m_red(0), m_green(0), m_blue(0), m_opacity(0)
{
}

KCColor::KCColor(float r, float g, float b, float o)
: m_red(r), m_green(g), m_blue(b), m_opacity(o)
{
}

KCColor::KCColor(const KCColor& c)
: m_red(c.getRed()), m_green(c.getGreen()), m_blue(c.getBlue()), m_opacity(c.getOpacity())
{
}

KCColor& KCColor::operator=(const KCColor& c)
{
    if(this == &c)
        return *this;
    
    m_red = c.getRed();
    m_green = c.getGreen();
    m_blue = c.getBlue();
    m_opacity = c.getOpacity();
    
    return *this;
}

void KCColor::setRed(float red)
{
    m_red = red;
}

void KCColor::setGreen(float green)
{
    m_green = green;
}

void KCColor::setBlue(float blue)
{
    m_blue = blue;
}

void KCColor::setOpacity(float opacity)
{
    m_opacity = opacity;
}


float KCColor::getRed() const
{
    return m_red;
}

float KCColor::getGreen() const
{
    return m_green;
}

float KCColor::getBlue() const
{
    return m_blue;
}

float KCColor::getOpacity() const
{
    return m_opacity;
}

bool KCColor::isEquals(const KCColor& color)
{
	return (this->getBlue() == color.getBlue()) && (this->getGreen() == color.getGreen())
		&& (this->getRed() == color.getRed()) && (this->getOpacity() == color.getOpacity());
}