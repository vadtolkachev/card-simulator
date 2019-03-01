#include "OGKCResourcesManager.hpp"
#include "oxygine-framework.h"

using namespace oxygine;

OGKCResourcesManager::OGKCResourcesManager()
{
	m_resources = new Resources;
}

OGKCResourcesManager::~OGKCResourcesManager()
{
	delete m_resources;
}

OGKCResourcesManager* OGKCResourcesManager::sharedManager()
{
	static OGKCResourcesManager manager;
	return &manager;
}

void OGKCResourcesManager::init() const
{
	m_resources->loadXML("res.xml");
}

void OGKCResourcesManager::free() const
{
	m_resources->free();
}

oxygine::Resources* OGKCResourcesManager::getResources() const
{
	return m_resources;
}