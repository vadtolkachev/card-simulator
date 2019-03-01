#pragma once

#include "IKCView.hpp"

#include <string>

class GKCImageView : public IKCView
{
public:
    GKCImageView(const std::string& imageName);
    virtual ~GKCImageView();

	std::string getImageName() const;

	virtual void setImage(const std::string& imageName);
	virtual void rotate(float degrees);

private:
    GKCImageView();
    GKCImageView(const GKCImageView& iv);
    GKCImageView& operator=(const GKCImageView& c);

	std::string m_imageName;
};