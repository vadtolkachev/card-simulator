#pragma once
#include "IKCView.hpp"
#include "GKCImageView.hpp"
#include "GKCTextView.hpp"
#include "GKCButton.hpp"
#include "KCCard.hpp"


const static std::string BackCardImageID = "Back Blue 1";


class GKCCardView : public IKCView
{
public:
	GKCCardView(KCCard* card);
	virtual ~GKCCardView();

	//getters
	KCPoint							getMousePosition() const;
	KCCard*							getCard() const;
	GKCImageView*           		getImageView() const;
	std::string						getFrontImageName() const;
	GKCTextView*					getSelectTextView() const;

	//setters
	virtual void					setFrame(KCRect rect);
	void							setMousePosition(const KCPoint &mousePosition);
	virtual void					setZOrder(int zOrder);

	void							changeRotatedCardFrame();
	virtual void					topMost();
	virtual void					move(KCPoint point);
	virtual IKCView*				findViewAtPoint(KCPoint point);

private:
	KCCard*			m_card;
	GKCImageView*	m_imageView;
	std::string		m_frontImageName;
	KCPoint			m_mousePosition;
	GKCTextView*	m_zOrderTextView;
	GKCTextView*	m_selectTextView;
};
