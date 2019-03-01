#pragma once
#include <string>
#include "GKCImageView.hpp"
#include "oxygine-framework.h"
#include "KCCard.hpp"

namespace oxygine
{
	class OGKCImageView : public GKCImageView, public Actor
	{
	public:
		static OGKCImageView* imageView(const std::string& imageName);
		OGKCImageView(const std::string &imageName);

		spSprite getSprite() const;

		virtual void setFrame(KCRect rect);
		virtual void topMost();
		virtual void setZOrder(int zOrder);
		virtual void setImage(const std::string& imageName);
		virtual void rotate(float degrees);

	private:
		spSprite m_image;
	};
};