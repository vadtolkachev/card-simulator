#pragma once

class IKCCompositionObserver;

class IKCDriven
{
public:
	virtual void setObserver(IKCCompositionObserver* observer) = 0;
	virtual IKCCompositionObserver* getObserver() const = 0;
};