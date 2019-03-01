#pragma once
#include "GKCButton.hpp"
#include "oxygine-framework.h"
#include <thread>

namespace oxygine
{
	class OGKCButton : public GKCButton, public Actor
	{
	public:
		static OGKCButton* button();
		OGKCButton();
		virtual ~OGKCButton();
		virtual void setZOrder(int zOrder);
		virtual void setFrame(KCRect rect);
		
		bool didDragged() const;
		void setDidDragged(bool didDragged);

	private:
		bool m_didDragged;
		std::thread m_mouseHoldThread;
	};
}