#pragma once
#include "KCPoint.hpp"

class KCSize
{
public:
	KCSize();
	KCSize(float width, float height);

	KCSize& operator = (const KCSize& s);

	float getWidth() const;
	float getHeight() const;

	void setWidth(float width);
	void setHeight(float height);
    
    bool isEquals(const KCSize& V1) const;
    
private:
	float m_width;
	float m_height;
};
