#pragma once

#include "KCRect.hpp"
#include "KCColor.hpp"

#include <vector>

enum GKCMouseButton
{
	GKCMouseButtonLeft,
	GKCMouseButtonRight,
	GKCMouseButtonMiddle
};

enum GKCModifierKeys
{
	GKCModifierKeyCommand,
	GKCModifierKeyControl,
	GKCModifierKeyAlt,
	GKCModifierKeyWin,
	GKCModifierKeyShift
};

enum GKCViewType
{
	GKCViewTypeRoom,
	GKCViewTypeCard,
	GKCViewTypeCardNone,
};

enum GKCViewAligment
{
	GKCViewAligmentVertical,
	GKCViewAligmentHorizontal
};

namespace GKCMouse
{
	static bool MousePressed;
	static int MousePressedID;
}

class IKCView
{
public:
    IKCView();
	virtual ~IKCView();
	
	//getters
	virtual KCPoint				getCenter() const;
	virtual KCRect				getFrame() const;
	virtual IKCView*			getParentView() const;
	virtual bool				isEnabled() const;
	virtual bool				isHidden() const;
	virtual float				getOpacity() const;
	virtual bool				isClipped() const;
	virtual KCColor				getBackgroundColor() const;
	virtual int					getZOrder() const;
	virtual GKCViewAligment		getViewAligment() const;

	//setters
	virtual void setFrame(KCRect rect);
	virtual void setParentView(IKCView* parent);
	virtual void addSubview(IKCView* view);
	virtual void removeSubView(IKCView* view);
	virtual void setEnabled(bool enable);
	virtual void setHidden(bool hidden);
	virtual void setOpacity(float opacity);
	virtual void setClipped(bool clipped);
	virtual void setBackgroundColor(const KCColor& color);
	virtual void setZOrder(int zOrder);
	virtual void setViewAligmnet(GKCViewAligment aligment);

	virtual void mouseEntered();
	virtual void mouseLongClick(GKCMouseButton button);
	virtual void mouseDown(GKCMouseButton button);
	virtual void mouseUp(GKCMouseButton button);
	virtual void mouseMoved(KCPoint newPosition);
	virtual void mouseExited();
	virtual void mouseClick(GKCMouseButton button, int clickCount);

	virtual void keyDown(GKCModifierKeys keyCode);
	virtual void keyUp(GKCModifierKeys keyCode);

	virtual void move(KCPoint point);
	virtual void topMost();
	virtual void removeFromParentView();
	virtual IKCView* findViewAtPoint(KCPoint point);

private:
	IKCView& operator=(const IKCView& v);
	IKCView(const IKCView& v);
	virtual bool	isContainsSubview(IKCView* subview) const;

	bool			m_topMost;
	bool			m_enabled;
	bool			m_hidden;
	bool			m_clipped;
	float			m_opacity;
	int				m_zOrder;

	KCRect					m_frameRect;
	IKCView*				m_parent;
	std::vector<IKCView*>	m_subviews;
	KCColor					m_backgroundColor;
	GKCViewAligment			m_aligment;
};
