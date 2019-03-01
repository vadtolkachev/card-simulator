#pragma once
#include "KCSize.hpp"

class KCRect
{
public:
	KCRect();
	KCRect(float x, float y, float width, float height);

	KCRect& operator = (const KCRect& r);

	bool isIntersects(const KCRect& other) const;
	bool isContainsPoint(const KCPoint& point) const;
	bool isContainsRect(const KCRect &rect) const;
	bool isEmpty() const;
	bool isEquals(const KCRect& V1) const;
	KCPoint center() const;

	KCPoint getOrigin() const;
	KCSize getSize() const;

	void setOrigin(KCPoint origin);
	void setSize(KCSize size);

	KCRect& inset(float width, float height);
	KCRect& unionRect(const KCRect &rect);

private:
	KCPoint m_origin;
	KCSize m_size;
};

inline float KCMaxX(KCRect aRect) { return aRect.getOrigin().getX() + aRect.getSize().getWidth(); }

inline float KCMaxY(KCRect aRect) { return aRect.getOrigin().getY() + aRect.getSize().getHeight(); }

inline float KCMidX(KCRect aRect) { return (aRect.getOrigin().getX() + aRect.getSize().getWidth()*.5f);}

inline float KCMidY(KCRect aRect) { return (aRect.getOrigin().getY() + aRect.getSize().getHeight()*.5f);}

inline float KCMinX(KCRect aRect) { return aRect.getOrigin().getX();}

inline float KCMinY(KCRect aRect) { return aRect.getOrigin().getY();}

inline float KCWidth(KCRect aRect) { return aRect.getSize().getWidth();}

inline float KCHeight(KCRect aRect) { return aRect.getSize().getHeight();}
