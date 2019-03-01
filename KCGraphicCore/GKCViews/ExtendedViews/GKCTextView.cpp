#include "GKCTextView.hpp"

GKCTextView::GKCTextView(const std::string& text, const KCFont& font)
{
    m_text = text;
    m_font = font;
}

GKCTextView::~GKCTextView()
{
    
}

GKCTextView::GKCTextView(const std::string& text)
{
    m_text = text;
}

void GKCTextView::setFont(const KCFont& font)
{
    m_font = font;
}

KCFont GKCTextView::getFont() const
{
    return m_font;
}

void GKCTextView::setText(const std::string& text)
{
    m_text = text;
}

std::string GKCTextView::getText() const
{
    return m_text;
}
