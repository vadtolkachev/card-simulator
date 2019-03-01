#include "GKCViewsFactory.hpp"

#ifdef GRAPHIC_ENGINE_OXYGINE
#include "OGKCButton.hpp"
#include "OGKCTextView.hpp"
#include "OGKCImageView.hpp"
#include "OGKCResourcesManager.hpp"
#endif

GKCResourcesManager* GKCViewsFactory::sharedManager()
{
#ifdef GRAPHIC_ENGINE_OXYGINE
	return OGKCResourcesManager::sharedManager();
#endif
}

KCRect GKCViewsFactory::getScreenSize()
{
#ifdef GRAPHIC_ENGINE_OXYGINE
	return { 0,0,oxygine::getStage()->getSize().x, oxygine::getStage()->getSize().y };
#endif
		return { 0,0,0,0 };
}

// buttons factory
GKCButton* GKCViewsFactory::makeButton()
{
#ifdef GRAPHIC_ENGINE_OXYGINE
    return oxygine::OGKCButton::button();
#endif
}

// textViews factory
GKCTextView* GKCViewsFactory::makeTextView(const std::string& text)
{
#ifdef GRAPHIC_ENGINE_OXYGINE
    return oxygine::OGKCTextView::textView(text);
#endif
}

GKCTextView* GKCViewsFactory::makeTextView(const std::string& text, const KCFont& font)
{
#ifdef GRAPHIC_ENGINE_OXYGINE
    return oxygine::OGKCTextView::textView(text, font);
#endif
}

// imageViews factory
GKCImageView* GKCViewsFactory::makeImageView(const std::string& text)
{
#ifdef GRAPHIC_ENGINE_OXYGINE
    return oxygine::OGKCImageView::imageView(text);
#endif
}
