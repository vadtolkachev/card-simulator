#include "IKCView.hpp"
#include "KCDefines.h"


IKCView::IKCView()
{
}


IKCView::~IKCView() 
{
}


KCPoint IKCView::getCenter() const
{
	return KCPoint(KCMidX(m_frameRect), KCMidY(m_frameRect));
}


KCRect IKCView::getFrame() const
{
	return m_frameRect;
}


IKCView* IKCView::getParentView() const
{
	return m_parent;
}


bool IKCView::isEnabled() const
{
	return m_enabled;
}


bool IKCView::isHidden() const
{
	return m_hidden;
}


float IKCView::getOpacity() const
{
	return m_opacity;
}


bool IKCView::isClipped() const
{
	return m_clipped;
}


KCColor IKCView::getBackgroundColor() const
{
	return m_backgroundColor;
}


int IKCView::getZOrder() const
{
	return m_zOrder;
}


GKCViewAligment	IKCView::getViewAligment() const
{
	return m_aligment;
}


void IKCView::setFrame(KCRect rect)
{
	if (m_frameRect.isEquals(rect))
		return;

	m_frameRect = rect;
}


void IKCView::setParentView(IKCView* parent)
{
	if (m_parent == parent)
		return;

	m_parent = parent;
}


void IKCView::addSubview(IKCView* subview)
{
	if (this->isContainsSubview(subview))
	{
		ASSERT();
		return;
	}
	m_subviews.push_back(subview);
}


void IKCView::removeSubView(IKCView* subview)
{
	if (!this->isContainsSubview(subview))
	{
		ASSERT();
		return;
	}
	m_subviews.erase(std::find(m_subviews.begin(), m_subviews.end(), subview));
}


void IKCView::setEnabled(bool enabled)
{
	if (m_enabled == enabled)
		return;

	m_enabled = enabled;
}


void IKCView::setHidden(bool hidden)
{
	if (m_hidden == hidden)
		return;

	m_hidden = hidden;
}


void IKCView::setOpacity(float opacity)
{
	if (m_opacity == opacity)
		return;

	m_opacity = opacity;
}


void IKCView::setClipped(bool clipped)
{
	if (m_clipped == clipped)
		return;
}


void IKCView::setBackgroundColor(const KCColor& color)
{
	if (m_backgroundColor.isEquals(color))
		return;

	m_backgroundColor = color;
}


void IKCView::setZOrder(int zOrder)
{
	if (m_zOrder == zOrder)
	{
		return;
	}

	m_zOrder = zOrder;
}


void IKCView::setViewAligmnet(GKCViewAligment aligment)
{
	if (m_aligment == aligment)
		return;

	m_aligment = aligment;
}


void IKCView::mouseEntered()
{
	if (m_parent != nullptr)
		m_parent->mouseEntered();
}


void IKCView::mouseLongClick(GKCMouseButton button)
{
	if (m_parent != nullptr)
		m_parent->mouseLongClick(button);
}


void IKCView::mouseDown(GKCMouseButton button)
{
	if (m_parent != nullptr)
		m_parent->mouseDown(button);
}


void IKCView::mouseUp(GKCMouseButton button)
{
	if (m_parent != nullptr)
		m_parent->mouseUp(button);
}


void IKCView::mouseMoved(KCPoint newPosition)
{
	if (m_parent != nullptr)
		m_parent->mouseMoved(newPosition);
}


void IKCView::mouseExited()
{
	if (m_parent != nullptr)
		m_parent->mouseExited();
}


void IKCView::mouseClick(GKCMouseButton button, int clickCount)
{
	if (m_parent != nullptr)
		m_parent->mouseClick(button,clickCount);
}


void IKCView::keyDown(GKCModifierKeys keyCode)
{
	if(m_parent != nullptr)
		m_parent->keyDown(keyCode);
}


void IKCView::keyUp(GKCModifierKeys keyCode)
{
	if (m_parent != nullptr)
		m_parent->keyUp(keyCode);
}


void IKCView::move(KCPoint point){}


void IKCView::topMost()
{
	m_topMost = true;
}


void IKCView::removeFromParentView()
{
	if(m_parent != nullptr)
		m_parent->removeSubView(this);
}


IKCView* IKCView::findViewAtPoint(KCPoint point)
{
	return nullptr;
}


bool IKCView::isContainsSubview(IKCView* subview) const
{
	for (int i = 0; i < (int)m_subviews.size(); ++i)
		if (m_subviews[i] == subview)
			return true;
	return false;
}