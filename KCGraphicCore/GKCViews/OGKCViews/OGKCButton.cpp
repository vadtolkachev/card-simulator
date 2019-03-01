#include "OGKCButton.hpp"
#include "KCDefines.h"
#include <chrono>

using namespace oxygine;

OGKCButton* OGKCButton::button()
{
    OGKCButton* button = new OGKCButton();

    return button;
}

OGKCButton::OGKCButton() : GKCButton()
{
	m_didDragged = false;

	// перед вызовом функтора проверка его на nullptr
	addEventListener(TouchEvent::TOUCH_DOWN, [this](Event* e) {
		
		GKCMouse::MousePressed = true;
		setDidDragged(false);

		TouchEvent* touchEvent = (TouchEvent*)(e);
		if (onMouseDown != nullptr)
			onMouseDown(GKCMouseButtonLeft, { touchEvent->position.x, touchEvent->position.y });
/*		
		if (m_mouseHoldThread.joinable())
		{
			m_mouseHoldThread.join();
		}

		m_mouseHoldThread = std::thread([this, touchEvent]() mutable {

			int oldMousePressedID = GKCMouse::MousePressedID;
			std::chrono::milliseconds ms(1000);
			std::this_thread::sleep_for(ms);
			int newMousePressedID = GKCMouse::MousePressedID;
			if ((oldMousePressedID == newMousePressedID) && (m_didDragged == false) && (onMouseHold != nullptr))
			{
				onMouseHold(GKCMouseButtonLeft, { touchEvent->position.x, touchEvent->position.y });
			}
		});*/
	});

	addEventListener(TouchEvent::TOUCH_UP, [this](Event* e) {

		GKCMouse::MousePressed = false;
		
		if (GKCMouse::MousePressedID == 20)
		{
			GKCMouse::MousePressedID = 0;
		}

		GKCMouse::MousePressedID = GKCMouse::MousePressedID + 1;

		TouchEvent* touchEvent = (TouchEvent*)(e);
		if (didDragged())
		{
			if (onMouseUp != nullptr)
				onMouseUp(GKCMouseButtonLeft, { touchEvent->localPosition.x, touchEvent->localPosition.y }, 1);
		}
		else
		{
			if (onMouseClicked != nullptr)
				onMouseClicked(GKCMouseButtonLeft, { touchEvent->localPosition.x, touchEvent->localPosition.y });
		}
	});

	addEventListener(TouchEvent::MOVE, [this](Event* e) {

		TouchEvent* touchEvent = (TouchEvent*)(e);
		if (!GKCMouse::MousePressed)
		{
			if (onMouseMoved != nullptr)
				onMouseMoved({ touchEvent->position.x, touchEvent->position.y });

		}
		else
		{
			setDidDragged(true);
			if (onMouseDragged != nullptr)
				onMouseDragged(GKCMouseButtonLeft, { touchEvent->position.x, touchEvent->position.y });
		}
		});

	getStage()->addChild(this);
}

void OGKCButton::setZOrder(int zOrder)
{
	IKCView::setZOrder(zOrder);

	setPriority(zOrder);
}


void OGKCButton::setFrame(KCRect rect)
{
	setPosition(KCMinX(rect), KCMinY(rect));
	setSize(KCWidth(rect), KCHeight(rect));
}


OGKCButton::~OGKCButton()
{
	removeEventListeners(this);

	if (m_mouseHoldThread.joinable())
	{
		m_mouseHoldThread.join();
	}
}


bool OGKCButton::didDragged() const
{
	return m_didDragged;
}


void OGKCButton::setDidDragged(bool didDragged)
{
	if (m_didDragged == didDragged)
		return;

	m_didDragged = didDragged;
}