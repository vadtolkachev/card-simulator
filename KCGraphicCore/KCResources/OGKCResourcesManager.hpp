#pragma once
#include "GKCResourcesManager.hpp"

namespace oxygine
{
	class Resources;
}

class OGKCResourcesManager : public GKCResourcesManager
{
public:
	static OGKCResourcesManager* sharedManager();

	virtual ~OGKCResourcesManager();
	virtual void init() const;
	virtual void free() const;

	oxygine::Resources* getResources() const;

private:
	oxygine::Resources* m_resources;
	OGKCResourcesManager();
	OGKCResourcesManager(const OGKCResourcesManager& m);
	OGKCResourcesManager& operator=(const OGKCResourcesManager& m);
};