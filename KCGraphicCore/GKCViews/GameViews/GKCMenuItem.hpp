#pragma once

#include "IKCView.hpp"
#include "GKCTextView.hpp"

#include <functional>

class GKCImageView;
//class GKCTextView;
class GKCButton;

class GKCMenuItem : public IKCView
{
public:
	GKCMenuItem();
	~GKCMenuItem();

	std::function<void(GKCMouseButton button, const KCPoint& poisition)> onClicked;

	GKCImageView* getImageView() const;
	GKCTextView* getTextView() const;
	GKCButton* getButton() const;

	void setImageView(GKCImageView* imageView);
	void setTextView(GKCTextView* textView);
	void setButton(GKCButton* button);
	virtual void setFrame(KCRect rect);

private:
	GKCImageView* m_imageView;
	GKCTextView* m_textView;
	GKCButton* m_button;
};