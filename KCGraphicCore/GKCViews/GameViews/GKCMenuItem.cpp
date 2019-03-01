#include "GKCMenuItem.hpp"
#include "GKCTextView.hpp"
#include "GKCImageView.hpp"
#include "GKCButton.hpp"
#include "GKCViewsFactory.hpp"


GKCMenuItem::GKCMenuItem()
{
	m_imageView = GKCViewsFactory::makeImageView("button");
	m_textView = GKCViewsFactory::makeTextView("button");
	m_button = GKCViewsFactory::makeButton();

	onClicked = nullptr;

	m_button->onMouseClicked = [=](GKCMouseButton button, const KCPoint& position) mutable {
	
		if (onClicked != nullptr)
		{
			onClicked(button, position);
		}
	};
}


GKCMenuItem::~GKCMenuItem()
{
	delete m_imageView;
	delete m_textView;
	delete m_button;
}


GKCImageView* GKCMenuItem::getImageView() const
{
	return m_imageView;
}


GKCTextView* GKCMenuItem::getTextView() const
{
	return m_textView;
}


GKCButton* GKCMenuItem::getButton() const
{
	return m_button;
}


void GKCMenuItem::setImageView(GKCImageView* imageView)
{
	if (m_imageView == imageView)
		return;

	m_imageView = imageView;
}


void GKCMenuItem::setTextView(GKCTextView* textView)
{
	if (m_textView == textView)
		return;

	m_textView = textView;
}


void GKCMenuItem::setButton(GKCButton* button)
{
	if (m_button == button)
		return;

	m_button = button;
}


void GKCMenuItem::setFrame(KCRect rect)
{
	IKCView::setFrame(rect);
	m_imageView->setFrame(rect);
	m_textView->setFrame(rect);
	m_button->setFrame(rect);
}