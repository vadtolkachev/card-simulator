#include "OGKCImageView.hpp"
#include "GKCViewsFactory.hpp"
#include "OGKCResourcesManager.hpp"
#include "oxygine-framework.h"

using namespace oxygine;


OGKCImageView* OGKCImageView::imageView(const std::string& imageName)
{
    OGKCImageView* view = new OGKCImageView(imageName);
    
    return view;
}


OGKCImageView::OGKCImageView(const std::string &imageName) : GKCImageView(imageName)
{
	m_image = new Sprite;
	setImage(imageName);
	addChild(m_image);
	getStage()->addChild(this);
}


spSprite OGKCImageView::getSprite() const
{
	return m_image;
}


void OGKCImageView::setFrame(KCRect rect) 
{
	GKCImageView::setFrame(rect);

	if (getViewAligment() == GKCViewAligmentHorizontal)
	{
		float x = KCMinX(rect);
		float y = KCMinY(rect);
		float w = KCWidth(rect);
		float h = KCHeight(rect);
		rect.setOrigin({ x - (h - w) / 2, y - (w - h) / 2 });
		rect.setSize({h,w});
	}

	m_image->setPosition(KCMidX(rect), KCMidY(rect));
	m_image->setSize(KCWidth(rect), KCHeight(rect));
}


void OGKCImageView::topMost()
{
    this->setPriority(90);
}


void OGKCImageView::setZOrder(int zOrder)
{
	IKCView::setZOrder(zOrder);
	setPriority(zOrder);
}


void OGKCImageView::setImage(const std::string& imageName)
{
	std::string newName = imageName;
	if (newName.find(IMAGE_FORMAT) == std::string::npos)
	{
		newName += IMAGE_FORMAT;
	}

	GKCImageView::setImage(newName);

	GKCResourcesManager* commonManager = GKCViewsFactory::sharedManager();
	OGKCResourcesManager* manager = dynamic_cast<OGKCResourcesManager *>(commonManager);
	if (manager)
	{
		m_image->setResAnim(manager->getResources()->getResAnim(imageName));
		m_image->setAnchor(0.5f,0.5f);
	}
	else ASSERT();
}


void OGKCImageView::rotate(float degrees)
{
	m_image->setRotationDegrees(degrees);
}