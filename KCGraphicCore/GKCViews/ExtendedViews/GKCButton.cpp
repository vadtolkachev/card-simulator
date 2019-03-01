#include "GKCButton.hpp"

GKCButton::GKCButton()
{
	onMouseDown = nullptr;
	onMouseUp = nullptr;
	onMouseMoved = nullptr;
	onMouseDragged = nullptr;
	onMouseHold = nullptr;
	onMouseHoldUp = nullptr;
}

GKCButton::~GKCButton()
{
    
}
