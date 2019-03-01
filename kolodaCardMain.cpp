#include "oxygine-framework.h"
#include "GKCViewsFactory.hpp"
#include "GKCGame.hpp"

using namespace oxygine;

GKCGame* game = new GKCGame();


void kolodaCard_preinit() {}


//called from main.cpp
void kolodaCard_init()
{
	game->newGame();
}

//called each frame from main.cpp
void kolodaCard_update()
{
}

//called each frame from main.cpp
void kolodaCard_destroy()
{
	GKCViewsFactory::sharedManager()->free();
}
