#pragma once
#include <string>

class KCFont
{
public:
	KCFont();
	KCFont(const std::string& fName, long fSize);

	long getFontSize() const;
	void setFontSize(long fontSize);

	std::string getFontName() const;
	void setFontName(std::string fontName);

private:
	long m_fontSize;
	std::string m_fontName;
};