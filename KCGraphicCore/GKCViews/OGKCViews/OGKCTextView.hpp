#pragma once
#include "GKCTextView.hpp"
#include "oxygine-framework.h"

namespace oxygine
{
	class OGKCTextView : public GKCTextView, public Actor
	{
	public:
		static OGKCTextView* textView(const std::string& text);
		static OGKCTextView* textView(const std::string& text, const KCFont& font);

		OGKCTextView(const std::string& text);
		OGKCTextView(const std::string& text, const KCFont& font);

		virtual void setFrame(KCRect rect);
		virtual void topMost();
		virtual void setZOrder(int zOrder);
		virtual void setText(const std::string& text);
		virtual void setParentView(IKCView* parent);

	private:
		spTextField m_text;
	};
}