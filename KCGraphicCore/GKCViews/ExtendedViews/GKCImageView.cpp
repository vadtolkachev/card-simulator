#include "GKCImageView.hpp"


GKCImageView::GKCImageView(const std::string& imageName)
{
    m_imageName = imageName;
}


GKCImageView::~GKCImageView()
{
    
}


std::string GKCImageView::getImageName() const
{
	return m_imageName;
}


void GKCImageView::setImage(const std::string& imageName)
{
    m_imageName = imageName;
}


void GKCImageView::rotate(float degrees){};