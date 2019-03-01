#pragma once
#include <algorithm>

#define KC_DEBUG

#ifdef KC_DEBUG
#define ASSERT() abort()
#else
#define ASSERT()
#endif

#define IMAGE_FORMAT ".png"

// graphic engine
#define GRAPHIC_ENGINE_OXYGINE


//Size constants
const float ScreenWidth = 920;
const float ScreenHeight = 640;

const float WScale = ScreenWidth / 1500;
const float HScale = ScreenHeight / 800;
//const float Scale = std::min(WScale, HScale);

const float CardWidth = HScale * 103;
const float CardHeight = HScale * 138;

const float BackgroundWidth = HScale * 966;
const float BackgroundHeight = HScale * 966;

const float MenuItemWidth = HScale * 100;
const float MenuItemHeight = HScale * 41;

const float TableRectX = 0;
const float TableRectY = 0;
const float TableRectWidth = ScreenWidth;
const float TableRectHeight = ScreenHeight * 0.75f;

const float PlayerRectX = WScale * 200;
const float PlayerRectY = ScreenHeight * 0.75f;
const float PlayerRectWidth = ScreenWidth - WScale * 400;
const float PlayerRectHeight = ScreenHeight * 0.25f;

//Distance constants
const float DistanceBetweenCardViews = 5;
const float DistanceBetweenCardsRowAndPlayerRectSide = WScale * 100;
const float TableRectSideWidth = 5;
const float PlayerRectSideWidth = 5;
const float CardGroupsOffset = 6;

//zOrder constants
const int BackgroundTableViewZOrder = 0;
const int PlayerDeckViewZOrder = 1;
const int MenuItemImageZOrder = 54;
const int MenuItemTextZOrder = 55;

const int MinCardsZOrder = 2;//max = min - 1 + 52 = 53

const int TableButtonZOrder = 1000;
const int PlayerButtonZOrder = 1000;
const int MenuItemButtonZOrder = 1001;


//other constants
const int CardPictureSet = 2;
const float RotationSpeed = 1;