#include "KCFont.hpp"

KCFont::KCFont()
{
	this->m_fontName = "";
	this->m_fontSize = 0;
};


KCFont::KCFont(const std::string& fName, long fSize)
{
	this->m_fontName = fName;
	this->m_fontSize = fSize;
};


long KCFont::getFontSize() const
{
	return m_fontSize;
}


std::string KCFont::getFontName() const
{
	return m_fontName;
}


void KCFont::setFontSize(long fontSize)
{
	if (m_fontSize == fontSize)
		return;

	m_fontSize = fontSize;
}


void KCFont::setFontName(std::string fontName)
{
	if (m_fontName == fontName)
		return;

	m_fontName = fontName;
}