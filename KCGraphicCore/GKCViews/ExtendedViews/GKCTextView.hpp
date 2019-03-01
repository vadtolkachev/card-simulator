#pragma once

#include "IKCView.hpp"
#include "KCFont.hpp"

#include <string>

class GKCTextView : public IKCView
{
public:
    GKCTextView(const std::string& text, const KCFont& font);
    GKCTextView(const std::string& text);
    virtual ~GKCTextView();

	KCFont				getFont() const;
	std::string			getText() const;

    void				setFont(const KCFont& font);
    virtual void		setText(const std::string& text);

private:
    GKCTextView();
    GKCTextView(const GKCTextView& tv);
    GKCTextView& operator=(const GKCTextView& c);

	std::string m_text;
	KCFont m_font;
};