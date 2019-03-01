#pragma once
#include "KCDefines.h"

#include "GKCButton.hpp"
#include "GKCTextView.hpp"
#include "GKCImageView.hpp"
#include "GKCResourcesManager.hpp"

class GKCViewsFactory
{
public:
	static GKCResourcesManager* sharedManager();
	static KCRect getScreenSize();

    // buttons factory
    static GKCButton* makeButton();
    
    // textViews factory
    static GKCTextView* makeTextView(const std::string& text);
    static GKCTextView* makeTextView(const std::string& text, const KCFont& font);
    
    // imageViews factory
    static GKCImageView* makeImageView(const std::string& text);
    
private:
    GKCViewsFactory();
    GKCViewsFactory(const GKCViewsFactory& f);
    GKCViewsFactory& operator=(const GKCViewsFactory& f);
};
