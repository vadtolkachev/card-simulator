#pragma once

class KCColor
{
public:
	//??
	KCColor();
    KCColor(float r, float g, float b, float o);
    KCColor(const KCColor& c);
    KCColor& operator=(const KCColor& c);
    
    void setRed(float red);
    void setGreen(float green);
    void setBlue(float blue);
    void setOpacity(float opacity);
    
    float getRed() const;
    float getGreen() const;
    float getBlue() const;
    float getOpacity() const;

	bool isEquals(const KCColor& color);
    
private:
    float                   m_red;
    float                   m_green;
    float                   m_blue;
    float                   m_opacity;
};
