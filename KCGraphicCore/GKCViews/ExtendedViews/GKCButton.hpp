#pragma once
#include "IKCView.hpp"

#include <functional>

class GKCButton : public IKCView
{
public:
    GKCButton();
    virtual ~GKCButton();
    
    // mouse down event
    std::function<void(GKCMouseButton button, const KCPoint& poisition)> onMouseDown;
    
    // mouse moved event
    std::function<void(const KCPoint& poisition)> onMouseMoved;
    
     // mouse up event
    std::function<void(GKCMouseButton button, const KCPoint& poisition, int clickCount)> onMouseUp;
    
     // mouse hold event
    std::function<void(GKCMouseButton button, const KCPoint& poisition)> onMouseHold;
    
     // mouse up after holding event
    std::function<void(GKCMouseButton button, const KCPoint& poisition)> onMouseHoldUp;

	std::function<void(GKCMouseButton button, const KCPoint& position)> onMouseDragged;

	std::function<void(GKCMouseButton button, const KCPoint& poisition)> onMouseClicked;

private:
    GKCButton(const GKCButton& b);
    GKCButton& operator=(const GKCButton& c);
};
