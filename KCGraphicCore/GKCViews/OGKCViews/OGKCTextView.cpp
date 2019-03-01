#include "OGKCTextView.hpp"
#include "GKCTextView.hpp"
#include "OGKCResourcesManager.hpp"
#include "GKCViewsFactory.hpp"
#include "OGKCImageView.hpp"


using namespace oxygine;


OGKCTextView* OGKCTextView::textView(const std::string& text)
{
    OGKCTextView* view = new OGKCTextView(text);
    view->setText(text);
	view->getFont().setFontName("main");

    return view;
}


OGKCTextView* OGKCTextView::textView(const std::string& text, const KCFont& font)
{
    OGKCTextView* view = new OGKCTextView(text, font);
    view->setText(text);
    view->setFont(font);

    return view;
}


OGKCTextView::OGKCTextView(const std::string& text) : GKCTextView(text)
{
	m_text = new TextField;
	GKCResourcesManager* commonManager = GKCViewsFactory::sharedManager();
	OGKCResourcesManager* manager = dynamic_cast<OGKCResourcesManager *>(commonManager);
	if (manager)
	{
		TextStyle style = TextStyle(manager->getResources()->getResFont("main")).alignMiddle();
		m_text->setText(text);
		m_text->setStyle(style);
		addChild(m_text);
		getStage()->addChild(this);
	}
	else ASSERT();
}


OGKCTextView::OGKCTextView(const std::string& text, const KCFont& font) : GKCTextView(text, font)
{
	m_text = new TextField;
	GKCResourcesManager* commonManager = GKCViewsFactory::sharedManager();
	OGKCResourcesManager* manager = dynamic_cast<OGKCResourcesManager *>(commonManager);
	if (manager)
	{
		m_text->setText(text);
		m_text->setFont(manager->getResources()->getResFont(font.getFontName()));
		addChild(m_text);
		getStage()->addChild(this);
	}
	else ASSERT();
}


void OGKCTextView::setFrame(KCRect rect)
{
	GKCTextView::setFrame(rect);
	m_text->setPosition({ KCMinX(rect) + KCWidth(rect) / 2 , KCMinY(rect) + KCHeight(rect) / 2 } );
}


void OGKCTextView::topMost()
{
	this->setPriority(90);
}


void OGKCTextView::setZOrder(int zOrder)
{
	IKCView::setZOrder(zOrder);
	setPriority(zOrder);
}


void OGKCTextView::setText(const std::string& text)
{
	m_text->setText(text);
}


void OGKCTextView::setParentView(IKCView* parent)
{
	IKCView::setParentView(parent);

	OGKCImageView* imageView = dynamic_cast<OGKCImageView *>(parent);
	m_text->attachTo(imageView->getSprite());
}