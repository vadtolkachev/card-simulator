#pragma once

class KCPoint
{
public:
	KCPoint();
	KCPoint(float x, float y);

	KCPoint& operator= (const KCPoint& V1);

	float getX() const;
	void setX(float x);

	float getY() const;
	void setY(float y);

    bool isEquals(const KCPoint& V1) const;
    
private:
	float m_x;
	float m_y;
};