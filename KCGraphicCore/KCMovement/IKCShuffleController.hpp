#pragma once

#include <vector>

class GKCCardView;

class IKCShuffleController
{
public:
	virtual std::vector<GKCCardView*> shuffle(std::vector<GKCCardView*> cards) = 0;
};