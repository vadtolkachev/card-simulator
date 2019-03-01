#pragma once

class GKCResourcesManager
{
public:
	virtual void init() const = 0;
	virtual void free() const = 0;
};
